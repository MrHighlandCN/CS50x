#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int size;
    do
    {
        size = get_int("Enter the start size: ");
    }
    while (size < 9);
    // TODO: Prompt for end size
    int endSize;
    do
    {
        endSize = get_int("Enter the end size: ");
    }
    while (endSize < size);
    // TODO: Calculate number of years until we reach threshold
    int numOfYears = 0;

    while (size < endSize)
    {
        size = size + size / 3 - size / 4;
        numOfYears++;
    }
    // TODO: Print number of years
    printf("Years: %i", numOfYears);
}
