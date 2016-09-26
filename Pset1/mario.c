#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
     do
    {
        printf("Enter pyramid Height: ");
        height = GetInt();
    }
    while (height < 0 || height > 23);
    
    int row, space, hash; 
    int sideRight = 2;
    int sideLeft  = height - 2;

    for(row = 0; row < height; row++)
    {
      for(space = 0; space <= sideLeft; space++)
      {
         printf(" ");
      }
      for(hash = 0; hash < sideRight; hash++)
      {
         printf("#");
      }
    sideLeft--;
    sideRight++;
    printf("\n");
    }
}
