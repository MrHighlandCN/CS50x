#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }
    BYTE buffer[512];
    int count = 0;
    char filename[8];
    sprintf(filename, "%03i.jpg", 0);
    FILE *img = fopen(filename, "w");
    while (fread(buffer, 1, 512, file) == 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (count == 0)
            {
                fwrite(buffer, 1, 512, img);
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
            }
            count++;
        }
        else if (count != 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    fclose(img);
    fclose(file);
    return 0;
}