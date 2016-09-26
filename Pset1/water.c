#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("How long was your shower?: ");
    
    int a = GetInt();
    int bottle = a *12;
    
    printf("minutes: %i \n", a);
    printf("bottles: %i \n", bottle);
    
}
