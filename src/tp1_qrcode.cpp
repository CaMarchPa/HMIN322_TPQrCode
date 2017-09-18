#include "ImageBase.h"
#include <stdio.h>


ImageBase binarisationClassique(ImageBase img, int threshold);

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char imgName[250];
	
	if (argc != 2) 
	{
		printf("Usage: ImageIn.pgm \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",imgName) ;
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(imgName);

	int pixMin = imIn[0][0];
	int pixMax = imIn[0][0];
	
	
	printf("Troubles");
	// Get pixel min and pixel max
	for(int j = 0; j < imIn.getHeight(); j++)
		for(int i = 0; i < imIn.getWidth(); i++)
		{
			if (imIn[j*3][i*3] < pixMin) 
				pixMin = imIn[j*3][i*3];
			if (imIn[j*3][i*3] > pixMax)
				pixMax = imIn[j*3][i*3];
		}
	int threshold = (pixMax - pixMin) / 2 + 0.5;
	
	printf(" The threshold value : %d ", threshold);
	
	ImageBase imOut = binarisationClassique(imIn, threshold);
	imOut.save("binarizedImage.pbm");
	
	return 0;
}

ImageBase binarisationClassique(ImageBase img, int threshold) {
	int height = img.getHeight();
	int width = img.getWidth();
	
	ImageBase imOut(width, height, true);
	
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++) {
			if (img[j*3][i*3] <= threshold)
				imOut[j][i] = 0;
			else
				imOut[j][i] = 255;
		}
		
	return imOut;
}


/* Lecture d'un fichier */
//unsigned char * lBuffer;
//FILE* lFile;
//int lSize[3];

//lSize[0] = nombre de colonnes (x);
//lSize[1] = nombre de lignes (y);
//lSize[2] = nombre de cannaux;

//lBuffer = new unsigned char [lSize[0]*lSize[1]*lSize[2]];
//lFile = fopen(nom du fichier, "rb");
//fread(lBuffer, sizeof(unsigned char), lSize[0]*lSize[0]*lSize[0], lFile);
//fclose(lFile);

// L = 0.3 * R + 0.59 * G + 0.11 * B;

//unsigned char lMin;
//unsigned char lMax;
//for(i=0; < i<lsize[0]*lSize[1]*lSize[2]; i+=lSize[2])
//if (lBuffer[i] < lMin) lMin = lBuffer[i]
