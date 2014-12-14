#include "ManipulateBmp.h"
#include "FlipUpAndDown.h"

ManipulateBmp::ManipulateBmp()
{
	stateMachine = newAllocate<StateMachine<ManipulateBmp>>(
		memoryManager.Get()->GetFreeListAllocator(), this);
	stateMachine->SetCurrentState(FlipUpAndDown::Instance());
}


ManipulateBmp::~ManipulateBmp()
{
	deleteDeallocate<StateMachine<ManipulateBmp>>(
		memoryManager.Get()->GetFreeListAllocator(), *stateMachine);
}

void ManipulateBmp::openFile(char *fileName, FILE *&file, const char *mode)
{
	fopen_s(&file, fileName, mode);
}

void ManipulateBmp::readFile(void *&object, size_t objectSize, size_t count, FILE *&file)
{
	fread(&object, objectSize, count, file);
}

void ManipulateBmp::colorCount(BMP *bmp)
{
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
}

void ManipulateBmp::LoadBMP(char *fileName, BMP *bmp)
{
	numColors = 0;
	pixelsPerByte = 0;

	openFile(fileName, originFile, "rb");

	readFile((void*&)bmp->bmfh, sizeof(bmp->bmfh), 1, originFile);

	if (bmp->bmfh.bfType != 'MB')
	{
		cout << fileName << " is not a valid bitmap file" << endl;
		exit(1);
	}

	readFile((void*&) bmp->bmih, sizeof(bmp->bmih), 1, originFile);

	colorCount(bmp);

	if ((bmp->colorTable = newArrayAllocate<RGBQUAD>(memoryManager.Get()->GetFreeListAllocator(), numColors * 4)) == NULL)
	{
		fclose(originFile);
		cout << "ERROR: unable to create color table" << endl;
		exit(1);
	}

	for (int i = 0; i < numColors; i++)
	{
		readFile((void*&) bmp->colorTable[i], 4, 1, originFile);
	}


	if ((bmp->bmpBits = newArrayAllocate<BYTE>(memoryManager.Get()->GetFreeListAllocator(),
		bmp->bmih.biHeight * bmp->bmih.biWidth)) == NULL)
	{
		fclose(originFile);
		cout << "ERROR: could not read file" << endl;

		deleteArrayDeallocate<RGBQUAD>(memoryManager.Get()->GetFreeListAllocator(), bmp->colorTable);
		exit(1);
	}

	for (int y = 0; y < bmp->bmih.biHeight; y++)
	{
		for (int x = 0; x < bmp->bmih.biWidth; x++)
		{
			readFile((void*&)bmp->bmpBits[y * bmp->bmih.biWidth + x], 1, 1, originFile);
		}
	}

	deleteArrayDeallocate<BYTE>(memoryManager.Get()->GetFreeListAllocator(), bmp->bmpBits);
	deleteArrayDeallocate<RGBQUAD>(memoryManager.Get()->GetFreeListAllocator(), bmp->colorTable);
	fclose(originFile);
}

void ManipulateBmp::WriteBMP(BMP *bmp)
{
	BMP bmp2 = *bmp;

	bmp2.bmih.biHeight *= 2;
	bmp2.bmih.biWidth *= 2;

	bmp2.bmpBits = newArrayAllocate<BYTE>(memoryManager.Get()->GetFreeListAllocator(), bmp2.bmih.biWidth * bmp2.bmih.biHeight);
	bmp2.bmfh.bfSize = sizeof(bmp2.bmfh) +
		sizeof(bmp2.bmih) + (sizeof(bmp2.colorTable) * 256) +
		sizeof(bmp2.bmpBits) * (bmp2.bmih.biHeight * bmp2.bmih.biWidth);

	openFile("flip.bmp", writeToFile, "wb");

	fwrite(&bmp2.bmfh, sizeof(bmp2.bmfh), 1, writeToFile);
	fwrite(&bmp2.bmih, sizeof(bmp2.bmih), 1, writeToFile);

	for (int i = 0; i < 256; i++)
	{
		fwrite(&bmp2.colorTable[i], 4, 1, writeToFile);
	}

	rearangeImage(*&bmp);

	fclose(writeToFile);
	deleteArrayDeallocate<BYTE>(memoryManager.Get()->GetFreeListAllocator(), bmp2.bmpBits);
}

void ManipulateBmp::rearangeImage(BMP *bmp)
{
	for (int i = 0; i < 2; i++)
	{
		for (int y = 0; y < bmp->bmih.biHeight; y++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int x = 0; x < bmp->bmih.biWidth; x++)
				{
					if (j == 0)
						fwrite(&bmp->bmpBits[y * bmp->bmih.biWidth + x], 1, 1, writeToFile);
					else
						fwrite(&bmp->bmpBits[bmp->bmih.biWidth * bmp->bmih.biHeight -
						(y * bmp->bmih.biWidth + x)], 1, 1, writeToFile);
				}
			}
		}
	}
}
