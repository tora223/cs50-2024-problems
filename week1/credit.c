#include <cs50.h>
#include <stdio.h>

int check_Luhn(long number);
int get_digits(long number);
int digit_sum(int x);
int get_start_number(long number, int digits_want);

int main(void)
{
    int valid = 0;
    long card_number = get_long("Number: ");
    if (card_number > 0 && check_Luhn(card_number))
    {
        valid = 1;
    }
    else
    {
        valid = 0;
    }

    if (valid)
    {
        int digits = get_digits(card_number);
        if (digits == 15 && 
            (get_start_number(card_number, 2) == 34 || get_start_number(card_number, 2) == 37))
        {
            printf("AMEX\n");
        }
        else if (digits == 16 && 
                 (51 <= get_start_number(card_number, 2) && get_start_number(card_number, 2) <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((digits == 13 || digits == 16) && get_start_number(card_number, 1) == 4)
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

    return 0;
}

int digit_sum(int x)
{
    int ret = 0;
    while (x > 0)
    {
        ret += x % 10;
        x /= 10;
    }

    return ret;
}

int check_Luhn(long number)
{
    int check_sum = 0;

    long tmp = number / 10;
    while (tmp > 0)
    {
        check_sum += digit_sum((tmp % 10) * 2);
        tmp /= 100;
    }

    tmp = number;
    while (tmp > 0)
    {
        check_sum += (tmp % 10);
        tmp /= 100;
    }

    return ((check_sum % 10) == 0);
}

int get_digits(long number)
{
    int ret = 0;
    while (number > 0)
    {
        number /= 10;
        ret++;
    }

    return ret;
}

int get_start_number(long number, int digits_want)
{
    while (number > 0)
    {
        if (get_digits(number) == digits_want)
        {
            return number;
        }
        number /= 10;
    }
    return number;
}