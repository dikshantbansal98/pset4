

 #include <stdio.h>

 #include <stdint.h>

 

 const int BLOCK_SIZE = 512;

 

 int main(int argc, char *agrv[])

 {

    FILE *f;

    

    if ((f = fopen("card.raw", "r")) == NULL)

    {

        printf("unable to open the file sorry");

        return 1;

    }

    

    uint8_t buf[512];

    

    int amount = 0;

    FILE *diku = NULL;

    

    // Iterate over file contents

    while (fread(buf, BLOCK_SIZE, 1, f))

    {

       

        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff

            && (buf[3] == 0xe0 || buf[3] == 0xe1))

        {

            // Closing all the opened file

            if (diku != NULL)

                fclose(diku);

            

            char filename[8];

            sprintf(filename, "%03d.jpg", amount);

                

            // Open a new JPEG file for writing

            diku = fopen(filename, "w");

            

            amount++;

        }

        

        if (diku != NULL)

            fwrite(buf, BLOCK_SIZE, 1, diku);

    }

    

    if (diku != NULL)

        fclose(diku);

    

    fclose(f);

 

    return 0;

 } 