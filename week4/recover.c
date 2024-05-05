#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *memory_card = fopen(argv[1], "r");
    if (memory_card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    BYTE buffer[512];
    FILE *jpeg;
    int jpeg_found = 0;
    int jpeg_cnt = 0;
    while (fread(buffer, 1, 512, memory_card) == 512)
    {
        // if JPEG header found
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if alredy found a JPEG
            if (jpeg_found)
            {
                // close the file
                fclose(jpeg);
            }
            else
            {
                jpeg_found = 1;
            }
            // create a new file
            char filename[10];
            sprintf(filename, "%03i.jpg", jpeg_cnt);
            jpeg = fopen(filename, "w");
            fwrite(buffer, 512, 1, jpeg);
            jpeg_cnt++;
        }
        else
        {
            // if alredy found a JPEG
            if (jpeg_found)
            {
                // write to file
                fwrite(buffer, 512, 1, jpeg);
            }
        }
    }
    fclose(memory_card);
    fclose(jpeg);
    return 0;
}
