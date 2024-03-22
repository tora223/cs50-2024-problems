#include <cs50.h>
#include <stdio.h>

void create_pyramid(int height);
void print_hash(int num);
void print_space(int num);

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || 8 < height);

    create_pyramid(height);
}

void print_hash(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("#");
    }
}

void print_space(int num)
{
    for (int i = 0; i < num; i++)
    {
        printf(" ");
    }
}

void create_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        print_space(height - i - 1);
        print_hash(i + 1);
        print_space(2);
        print_hash(i + 1);
        printf("\n");
    }
}
