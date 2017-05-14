

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

    

    

   

    return 0;

 } 