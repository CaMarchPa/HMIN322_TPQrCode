#include "ImageBase.h"
#include <stdio.h>
#include <iostream>


int getLuminance(int R, int G, int B);
ImageBase binarisationClassique(ImageBase img, int threshold);
// ImageBase binarisationVote(ImageBase img, int bloc_size);

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

	//ImageBase imIn;
	ImageBase imIn;
	imIn.load(imgName);

	int pixMin = 255;
	int pixMax = 0;

	int totalsize = imIn.getTotalSize();
	std::cout << "La taille totale = " << totalsize << ", height = " << imIn.getHeight() << ", width = " << imIn.getWidth() <<std::endl;

	for(int j = 0; j < imIn.getHeight(); j++)
		for(int i = 0; i < imIn.getWidth(); i++) {
			int l = getLuminance(imIn[j][i*3], imIn[j][i*3+1], imIn[j][i*3+2]);
			if (l < pixMin)
				pixMin = l;
			if (l > pixMax)
				pixMax = l;
		}

	int threshold = (pixMax - pixMin) / 2 + 0.5;
	std::cout << "The threshold value : " << threshold << ", min value : " << pixMin << ", max value : " << pixMax << std::endl;

	ImageBase imOut = binarisationClassique(imIn, threshold);
	// get one of three plans R, G or B
	ImageBase* img = imOut.getPlan(imOut.PLAN_R);
	img->save("../result/binarizedImage.pbm");

	return 0;
}

int getLuminance(int R, int G, int B) {
	return 0.3 * R + 0.59 * G + 0.11 * B;
}

ImageBase binarisationClassique(ImageBase img, int threshold) {
	int height = img.getHeight();
	int width = img.getWidth();

	ImageBase imOut(width, height, img.getColor());

	for (int j = 0; j < height*3; j++)
		for (int i = 0; i < width; i++) {
			int l = getLuminance(img[j][i*3], img[j][i*3+1], img[j][i*3+2]);
			if (l < threshold){
				imOut[j][i*3+0] = 0;
				imOut[j][i*3+1] = 0;
				imOut[j][i*3+2] = 0;
			} else {
				imOut[j][i*3+0] = 255;
				imOut[j][i*3+1] = 255;
				imOut[j][i*3+2] = 255;
			}
		}

	return imOut;
}

// ImageBase binarisationVote(ImageBase img, int bloc_size) {
// 	int height = img.getHeight();
// 	int width = img.getWidth();
// 	for (int j = 0; j < height; j+=bloc_size) {
// 		for (int i = 0; i < width; i+=bloc_size) {
// 			for (size_t y = j; y < j+bloc_size; y++) {
// 				for (size_t x = i; x < i+bloc_size; x++) {
// 					if (y < height && x < width) {
//
// 					}
// 				}
// 			}
// 		}
// 	}
// }

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
