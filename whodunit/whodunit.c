/*
  this file is whodunit.c
*/
#include <stdio.h>

#include <stdlib.h>
#include "bmp.h"



int main(int argc, char* argv[])

{

    // ensuring  proper usage of arg

    if (argc != 2)

    {

        printf("whodunit file must contain exactly two arguments \n");

        return 1;

    }



    // open input file 

    FILE* dikuptr = fopen(argv[1], "r");

    if (dikuptr == NULL)

    {

        printf("unable to open %s.\n", argv[1]);

        return 2;

    }



    // open output file

    FILE* dinkyptr = fopen("solution.bmp", "w");

    if (dinkyptr == NULL)

    {

        fclose(dikuptr);

        fprintf(stderr, "unable to create %s\n", "solution.bmp");

        return 3;

    }



    // read infile's BITMAPFILEHEADER

    BITMAPFILEHEADER bf;

    fread(&bf, sizeof(BITMAPFILEHEADER), 1, dikuptr);



    // read infile's BITMAPINFOHEADER

    BITMAPINFOHEADER bi;

    fread(&bi, sizeof(BITMAPINFOHEADER), 1, dikuptr);



    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 

        bi.biBitCount != 24 || bi.biCompression != 0)

    {

        fclose(dinkyptr);

        fclose(dikuptr);

        fprintf(stderr, "Unsupported file format.\n");

        return 4;

    }



    // write outfile's BITMAPFILEHEADER

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, dinkyptr);



    // write outfile's BITMAPINFOHEADER

    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, dinkyptr);



    // determine padding for scanlines

    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;



    // iterate over infile's scanlines

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)

    {

        // iterate over pixels in scanline

        for (int j = 0; j < bi.biWidth; j++)

        {

            // temporary storage

            RGBTRIPLE triple;



            // read RGB triple from infile

            fread(&triple, sizeof(RGBTRIPLE), 1, dikuptr);



            // write RGB triple to outfile

            if(triple.rgbtRed == 255)

            {

		triple.rgbtRed = 0;

  		triple.rgbtBlue = 100;

		triple.rgbtGreen = 60;

            } 

            fwrite(&triple, sizeof(RGBTRIPLE), 1, dinkyptr);

	    

	    

        }



        // skiping all over padding, if any is present

        fseek(dikuptr, padding, SEEK_CUR);



        // then add it back (to demonstrate how)

        for (int k = 0; k < padding; k++)

            fputc(0x00, dinkyptr);

    }



    // closure of infile

    fclose(dikuptr);



    // closing outfile now

    fclose(dinkyptr);



    // that's all set done

    return 0;

}