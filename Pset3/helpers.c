/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

// Binary search function
bool binarysearch(int value, int values[], int start, int end)
{
    // Value does not exist
    if (start > end)
    {
        return false;
    }
    
    // Define midpoint
    int mid = start + ((end - start) / 2);
    
    // Recursive binary search for value in sorted list
    if (values[mid] > value)
    {
        return binarysearch(value, values, start, mid - 1);
    }
    else if (values[mid] < value)   
    {
        return binarysearch(value, values, mid + 1, end);
    }
    else
    {
       return true; 
    }
}
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    return (binarysearch(value, values, 0, n - 1));
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
     for (int i = 1; i < n; i++)
    {
        int element = values[i];
        int j = i;
        while ( j > 0 && values[j - 1] > element)
        {
            values[j] = values[j - 1];
            j--;
        }
        values[j] = element;
    }
    return;
}
