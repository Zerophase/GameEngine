#include "MemoryManager.h"
#include "LinearAllocator.h"
#include "StackAllocator.h"

#include <iostream>

using namespace Utilities;

MemoryManager memoryManager;

#define MEM_SIZE 1048576000 //1GB

#define MAX_NUM_ALLOCS 100000

void *mem;

void GetLinearAllocator()
{
	
	LinearAllocator *linearAllocator = new LinearAllocator(MEM_SIZE, mem);

	int *number[MAX_NUM_ALLOCS];
	for (uint i = 1; i < 34; i++)
	{
		number[i - 1] = (int*) linearAllocator->Allocate(i, 8);
		*number[i - 1] = i;
	}

	for (int i = 0; i < 33; i++)
	{
		std::cout << "Number Address: " << number[i] <<
			"Number Value: " << *number[i] << std::endl;
	}

	linearAllocator->Clear();
	delete linearAllocator;
}

void GetStackAllocator()
{
	//void *mem = malloc(MEM_SIZE);
	StackAllocator *stackAllocator = new StackAllocator(MEM_SIZE, mem);

	int *number[MAX_NUM_ALLOCS];
	for (uint i = 1; i < 34; i++)
	{
		number[i - 1] = (int*) stackAllocator->Allocate(i, 8);
		*number[i - 1] = i;
	}

	for (int i = 0; i < 33; i++)
	{
		std::cout << "Number Address: " << number[i] <<
			"Number Value: " << *number[i] << std::endl;
	}

	for (int i = 32; i >= 0; i--)
	{
		stackAllocator->Deallocate(number[i]);
	}

	delete stackAllocator;
}

int main()
{
	std::cout << memoryManager.Get();
	std::cout << std::endl;

	memoryManager.StartUp();
	mem = malloc(MEM_SIZE);

	std::cout << "Linear Allocator" << std::endl;
	GetLinearAllocator();

	std::cout << "Stack Allocator" << std::endl;
	GetStackAllocator();

	memoryManager.ShutDown();

	std::cin.get();
	return 0;
}