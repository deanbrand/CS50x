#include <stdio.h>
#include <stdlib.h>

// Open memory card
// Repeat until end of card:
//     Read 512 bytes into a buffer
//     If start of new JPEG
//         If first JPEG
//         ...
//         Else
//         ...
//     Else
//         If already found JPEG
//         ...
// Close any remaining files
 
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }
    
    char *infile = argv[1];
    
    // Size of the block that will be read and written
    const int BLOCK_SIZE = 512;
    
    // Open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    unsigned char buffer[BLOCK_SIZE];
    
    // Pointer to outfile
    FILE *outptr = NULL;
    
    // Make space for jpg file name
    char image[7];
    
    // Number of image files created
    int n = 0;

    // Search until jpg is found
    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        // Find the beginning of an jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            // Close image file if one has been created
            if (n > 0)
            {
                fclose(outptr);
            }
            // Make name for nth image
            sprintf(image, "%03d.jpg", n);
            
            // Open nth image file
            outptr = fopen(image, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", image);
                return 3;
            }
            
            // Increment number of image files created
            n++;
        }
        
        // Write to image file only if one exists 
        if (outptr != NULL)
        {
            // Write to image file
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }
    
    // Close last image file
    fclose(outptr);
    
    // Close card.raw
    fclose(inptr);
    
    return 0;
}