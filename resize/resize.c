#include <stdio.h>

#include <stdlib.h>



#include "bmp.h"



int main(int argc, char* argv[])

{

		// ensuring proper usage

		if (argc != 4)

		{

				printf("enter arguments not valid\n");

				return 1;

		}




		int f = atoi(argv[1]);

		if(f < 0 || f > 100)

		{

				printf("f is either nonpositive or greater than 100\n");

				return 1;

		}



		// creating  pointer pointing to character as variables

		char* dikuin = argv[2];

		char* dikuout = argv[3];



		// open input file 

		FILE* diku1 = fopen(dikuin, "r");

		if (diku1 == NULL)

		{

				printf("unable to open file %s.\n", dikuin);

				return 1;

		}



		// open output file

		FILE* diku2 = fopen(dikuout, "w");

		if (diku2 == NULL)

		{

				fclose(diku1);

				fprintf(stderr, "Could not create the file %s.\n", dikuout);

				return 1;

		}



		// reading inputfiles BITMAPFILEHEADER

		BITMAPFILEHEADER bf;

		fread(&bf, sizeof(BITMAPFILEHEADER), 1, diku1);



		// working on input file BITMAPINFOHEADER

		BITMAPINFOHEADER bi;

		fread(&bi, sizeof(BITMAPINFOHEADER), 1, diku1);



		// checking if input file is valid

		if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 

						bi.biBitCount != 24 || bi.biCompression != 0)

		{

				fclose(diku2);

				fclose(diku1);

				fprintf(stderr, "Unsupported file format.\n");

				return 4;

		}



		// construct bitmap headers for the dikuout

		BITMAPFILEHEADER output_bfh;

		BITMAPINFOHEADER output_bi;	

		output_bfh = bf;

		output_bi = bi;

		output_bi.biWidth = bi.biWidth * f;

		output_bi.biHeight = bi.biHeight * f;



		// determining padding spacing

	
		int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

		int out_padding =  (4 - (output_bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;



	

		output_bfh.bfSize = 54 + output_bi.biWidth * abs(output_bi.biHeight) * 3 + abs(output_bi.biHeight) *  out_padding;

		output_bi.biSizeImage = ((((output_bi.biWidth * output_bi.biBitCount) + 31) & ~31) / 8) * abs(output_bi.biHeight);



		// write output file's BITMAPFILEHEADER

		fwrite(&output_bfh, sizeof(BITMAPFILEHEADER), 1, diku2);



		// write dikuout's BITMAPINFOHEADER

		fwrite(&output_bi, sizeof(BITMAPINFOHEADER), 1, diku2);



		for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)

		{
                // displaying factor number of-times
                for(int n=0;n<f;n++)

                 {
                    
                 // iterate over pixels in scanline

                 for (int j = 0; j < bi.biWidth; j++)

                 {

                 // temporary storage

                 RGBTRIPLE triple;



// read RGB triple from dikuin

                 fread(&triple, sizeof(RGBTRIPLE), 1, diku1);



                
                 
                 }



                 // padding skipping in diku input file

                 fseek(diku1, in_padding, SEEK_CUR);



                 // then add it to diku output file

                 for (int k = 0; k <out_padding; k++)

                 fputc(0x00, diku2);



                 fseek(diku1, -(bi.biWidth * 3 + in_padding ), SEEK_CUR);



                 }

                 fseek(diku1, bi.biWidth*3+in_padding, SEEK_CUR);

		}
                fclose(diku1);
                fclose(diku2);

                // everything got completed and working well !!!!

                return 0;

}