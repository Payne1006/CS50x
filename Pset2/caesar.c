/**
 * Create a caesar cipher using 
 * command line arguements
 */

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
// Verify command line argument is valid
    if (argc != 2)
    {
        printf("Unexpected Data Entry: ./caesar <key> \n");
        return 1;
    }
//Ensure key is integer
    int key = atoi(argv[1]);
    if (key == 0)
    {
        printf("Invalid Key Value \n");
        return 1;
    }
//Recieve plaintext, convert to cipher, return encrypted
    string ptxt = GetString();
    
    for (int i = 0, n = strlen(ptxt); i < n; i++)
    {
        switch (ptxt[i])
        {
            case 'a'...'z':
                printf("%c", (char) ((ptxt[i] + key) - 97) % 26 + 97);
                break;
            
            case 'A'...'Z':
                printf("%c", (char) ((ptxt[i] + key) - 65) % 26 + 65);
                break;
                
            default:
                printf("%c", (char) ptxt[i]);
        }
    }
    printf("\n");
    return 0;
}
