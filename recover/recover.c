

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

    


    return 0;

 } 