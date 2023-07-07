#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // read one all bytes of block at the time until the end and process them
    uint8_t bytes[BLOCK_SIZE];
    char name[8];
    int num = 0;
    FILE *output = NULL;

    while (fread(bytes, sizeof(uint8_t), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // check is block start new jpeg
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] >> 4) == 14)
        {
            // close previous opened file if exist
            if (output != NULL)
            {
                fclose(output);
            }

            // create name for new file
            sprintf(name, "%03d.jpg", num);

            // open output new file
            output = fopen(name, "w");
            if (output == NULL)
            {
                printf("Could not open %s.\n", argv[1]);
                return 1;
            }

            num++;
        }

        if (output != NULL)
        {
            // write block into file
            fwrite(bytes, sizeof(uint8_t), BLOCK_SIZE, output);
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}