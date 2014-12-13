#include "MemoryManager.h"
#include "AllocationSchemas.h"
#include "TestObject.h"

#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <string.h>
#include <iostream>
#include <vector>

using namespace Utilities;
using namespace allocator;
using namespace std;

MemoryManager memoryManager;

typedef struct tagBMP
{
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	RGBQUAD*			colorTable;
	BYTE*				bmpBits;
}BMP;

int numColors, pixelsPerByte;

void LoadBMP(char *fileName, BMP *bmp)
{
	FILE *fp;
	numColors = 0;
	pixelsPerByte = 0;

	fopen_s(&fp, fileName, "rb");
	

	fread(&bmp->bmfh, sizeof(bmp->bmfh), 1, fp);

	if (bmp->bmfh.bfType != 'MB')
	{
		cout << fileName << " is not a valid bitmap file" << endl;
		exit(1);
	}

	fread(&bmp->bmih, sizeof(bmp->bmih), 1, fp);

	switch (bmp->bmih.biBitCount)
	{
	case 1:
		numColors = 1;
		pixelsPerByte = 8;
		break;
	case 4:
		numColors = 16;
		pixelsPerByte = 2;
		break;
	case 8:
		numColors = 256;
		pixelsPerByte = 1;
		break;
	}

	if ((bmp->colorTable = newArrayAllocate<RGBQUAD>(memoryManager.Get()->GetFreeListAllocator(), numColors * 4)) == NULL)
	{
		fclose(fp);
		cout << "ERROR: unable to create color table" << endl;
		exit(1);
	}

	for (int i = 0; i < numColors; i++)
	{
		fread(&bmp->colorTable[i], 4, 1, fp);
	}

	
	if ((bmp->bmpBits = newArrayAllocate<BYTE>(memoryManager.Get()->GetFreeListAllocator(), 
		bmp->bmih.biHeight * bmp->bmih.biWidth)) == NULL)
	{
		fclose(fp);
		cout << "ERROR: could not read file" << endl;

		delete [] bmp->colorTable;
		exit(1);
	}

	for (int y = 0; y < bmp->bmih.biHeight; y++)
	{
		for (int x = 0; x < bmp->bmih.biWidth; x++)
		{
			fread(&bmp->bmpBits[y * bmp->bmih.biWidth + x], 1, 1, fp);
		}
	}

	deleteArrayDeallocate<BYTE>(memoryManager.Get()->GetFreeListAllocator(), bmp->bmpBits);
	deleteArrayDeallocate<RGBQUAD>(memoryManager.Get()->GetFreeListAllocator(), bmp->colorTable);
	fclose(fp);
}

void WriteBMP(BMP *bmp)
{
	FILE *fp;

	BMP bmp2 = *bmp;

	bmp2.bmih.biHeight *= 2;
	bmp2.bmih.biWidth *= 2;

	bmp2.bmpBits = newArrayAllocate<BYTE>(memoryManager.Get()->GetFreeListAllocator(), bmp2.bmih.biWidth * bmp2.bmih.biHeight);
	bmp2.bmfh.bfSize = sizeof(bmp2.bmfh) +
		sizeof(bmp2.bmih) + (sizeof(bmp2.colorTable) * 256) +
		sizeof(bmp2.bmpBits) * (bmp2.bmih.biHeight * bmp2.bmih.biWidth);

	fopen_s(&fp, "flip.bmp", "wb");

	fwrite(&bmp2.bmfh, sizeof(bmp2.bmfh), 1, fp);
	fwrite(&bmp2.bmih, sizeof(bmp2.bmih), 1, fp);

	for (int i = 0; i < 256; i++)
	{
		fwrite(&bmp2.colorTable[i], 4, 1, fp);
	}

	for (int i = 0; i < 2; i++)
	{
		for (int y = 0; y < bmp->bmih.biHeight; y++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int x = 0; x < bmp->bmih.biWidth; x++)
				{
					if (j == 0)
						fwrite(&bmp->bmpBits[y * bmp->bmih.biWidth + x], 1, 1, fp);
					else
						fwrite(&bmp->bmpBits[bmp->bmih.biWidth * bmp->bmih.biHeight -
						(y * bmp->bmih.biWidth + x)], 1, 1, fp);
				}
			}
		}
	}

	fclose(fp);
	deleteArrayDeallocate<BYTE>(memoryManager.Get()->GetFreeListAllocator(), bmp2.bmpBits);
}

int main()
{
	memoryManager.StartUp();

	BMP bmp;
	LoadBMP("C:\\Users\\Zerophase\\Desktop\\GameEngine\\GameEngine\\Debug\\punkmonkey.bmp", &bmp);
	WriteBMP(&bmp);

	memoryManager.ShutDown();

	std::cin.get();
	return 0;
}