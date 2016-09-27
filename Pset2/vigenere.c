// Create a vigenere cipher

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    // Verify command line argument is valid
    if (argc != 2) 
    {
        printf("Unexpected Data Entry: ./vigenere <key> \n");
        return 1;
    }
    
    // Verify keyword is valid
    string keyword  = argv[1];
    int keylen      = strlen(keyword);
    
    for (int i = 0; i < keylen; i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("Invalid Key Entry, alphabetical characters required. \n");
            return 1;
        }
    }
    
    // Receive plaintext, run 'for loop' to convert to ciphertext  
    string ptxt = GetString();
    int txtlen  = strlen(ptxt);
    
    for (int j = 0, ii = 0; j < txtlen; j++, ii++)
    {   
        // Repeat keyword for length of plaintext
        ii = (ii == keylen) ? ii - ii : ii;
        
        // Ensure non-alphabetical char is not converted, keep keyword intact
        if (!isalpha(ptxt[j]))
        {
            --ii;
            printf("%c", ptxt[j]);
        }
        else
        {
            switch (ptxt[j])
            {
                // Lowercase text conversion 
                case 'a'...'z':
                    ptxt[j] -= 97;
                    if (isupper(keyword[ii]))
                    {
                        ptxt[j] = (ptxt[j] + (keyword[ii] - 65)) % 26;
                        ptxt[j] += 97; 
                        printf ("%c", ptxt[j]);
                        break;
                    }
                    else
                    {
                        ptxt[j] = (ptxt[j] + (keyword[ii] - 97)) % 26;
                        ptxt[j] += 97; 
                        printf ("%c", ptxt[j]);
                        break;
                    }
                // Uppercase text conversion
                case 'A'...'Z':
                    if (isupper(keyword[ii]))
                    {
                        ptxt[j] = ptxt[j] + (keyword[ii] - 65);
                        ptxt[j] = (ptxt[j] > 90) ? (ptxt[j] - 65) % 26 + 65 : ptxt[j];
                        printf ("%c", ptxt[j]);
                        break;
                    }
                    else
                    {
                        ptxt[j] = ptxt[j] + (keyword[ii] - 97);
                        ptxt[j] = (ptxt[j] > 90) ? (ptxt[j] - 65) % 26 + 65 : ptxt[j];
                        printf ("%c", ptxt[j]);
                        break;
                    }
            }
        }
    }
    printf("\n");
    return 0;
}
