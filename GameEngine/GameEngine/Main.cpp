#include "MemoryManager.h"
#include <iostream>

using namespace Utilities;

MemoryManager memoryManager;

int main()
{
	std::cout << memoryManager.Get();
	std::cout << std::endl;

	memoryManager.StartUp();

	memoryManager.Get()->stackAllocator->alloc(32);
	std::cout << memoryManager.Get()->stackAllocator->TopOfStack();
	std::cout << memoryManager.Get()->stackAllocator->BottomOfStack();

	memoryManager.ShutDown();

	return 0;
}