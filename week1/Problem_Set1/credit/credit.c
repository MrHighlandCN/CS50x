#include <cs50.h>
#include <stdio.h>

int Count(long long int n)
{
    int count = 0;
    while (n != 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

bool isValid(long long int n)
{
    int sumMul2 = 0;
    int sum = 0;
    while (n != 0)
    {
        sum += n % 10;
        n /= 10;
        if (n % 10 * 2 >= 10)
        {
            sumMul2 += (n % 10 * 2) % 10 + (n % 10 * 2) / 10;
        }
        else
            sumMul2 += n % 10 * 2;
        n /= 10;
    }
    int res = sum + sumMul2;
    if (res % 10 == 0)
        return true;
    else
        return false;
}

int main(void)
{
    long long int n;
    do
    {
        n = get_long("Number: ");
    }
    while (n <= 0);

    int cnt = Count(n);
    if (cnt != 13 && cnt != 15 && cnt != 16)
    {
        printf("INVALID\n");
    }
    else
    {
        if (isValid(n))
        {
            while (n >= 100)
            {
                n /= 10;
            }
            if ((n == 37 || n == 34) && cnt == 15)
            {
                printf("AMEX\n");
            }
            else if (n >= 51 && n <= 55 && cnt == 16)
            {
                printf("MASTERCARD\n");
            }
            else if (n / 10 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
}