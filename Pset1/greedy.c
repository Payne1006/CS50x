/**
 * Determine the minimum number 
 * of coins needed for any given
 * amount of currency.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{

float change; 

    do
    {
        printf("How much change: ");
        change = GetFloat();
    }
    while (change <= 0.00);
    
int cents = round(change * 100);

int quarters    = cents / 25;
int minusQ      = cents % 25;

int dimes       = minusQ / 10;
int minusD      = minusQ % 10;

int nickels     = minusD / 5;
int minusN      = minusD % 5;

int pennys      = minusN / 1;

int total = quarters + dimes + nickels + pennys;

printf("%i\n", total); 
}
