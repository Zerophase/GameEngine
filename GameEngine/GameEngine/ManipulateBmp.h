#ifndef MANIPULATE_BMP_H
#define MANIPULATE_BMP_H

#include "BMP.h"
#include "MemoryManager.h"
#include "StateMachine.h"

#include <iostream>

using namespace std;
using namespace Utilities;
using namespace allocator;

class ManipulateBmp
{
private:
	StateMachine<ManipulateBmp> *stateMachine;

	int numColors, pixelsPerByte;

	MemoryManager memoryManager;

	FILE *originFile;
	FILE *writeToFile;

	void openFile(char *fileName, FILE *&file, const char *mode);
	void readFile(void *&object, size_t objectSize, size_t count, FILE *&file);

	void colorCount(BMP *bmp);
	void rearangeImage(BMP *bmp);

public:
	ManipulateBmp();
	~ManipulateBmp();

	void LoadBMP(char *fileName, BMP *bmp);
	void WriteBMP(BMP *bmp);

};

#endif // !MANIPULATE_BMP_H



