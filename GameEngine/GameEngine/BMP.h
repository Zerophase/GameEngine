#ifndef BMP_H
#define BMP_H

#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <string.h>

typedef struct tagBMP
{
	BITMAPFILEHEADER	bmfh;
	BITMAPINFOHEADER	bmih;
	RGBQUAD*			colorTable;
	BYTE*				bmpBits;
}BMP;

#endif // !BMP_H
