/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    //ensure proper resize input is provided
    int newsize = atoi(argv[1]);
    
    if (newsize > 100 || newsize < 1)
    {
        printf("Invalid size, n == 1 - 100\n");
        return 1;
    }

    // remember filenames
    char* infile  = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, old_bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // preserve original dimensions
    old_bi.biHeight = bi.biHeight;
    old_bi.biWidth  = bi.biWidth;
    
    // assign new diminsions
    bi.biHeight *= newsize;
    bi.biWidth  *= newsize;
    
    
    // determine padding, if any
    int padding     = (4 - (old_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // total size info for header files
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof(RGBTRIPLE)) + new_padding);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Allocate memory for new image storage
    RGBTRIPLE* new_triple = malloc(sizeof(RGBTRIPLE) * bi.biWidth);
    if (new_triple == NULL)
    {
        printf("Memory Allocation Error \n");
        return 1;
    }
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_bi.biHeight); i < biHeight; i++)
    {
        int pixcount = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < old_bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // assign pixels to output storage variable
            for(int k = 0; k < newsize; k++)
            {
                *(new_triple + (pixcount)) = triple;
                pixcount++;
            }
        }
        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
        
         // write new image to outfile
        for (int m = 0; m < newsize; m++)
        {
            fwrite(new_triple, sizeof(RGBTRIPLE), bi.biWidth, outptr);
        
            // add padding to resized image, if needed
            for (int k = 0; k < new_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    // free memory
    free(new_triple);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
