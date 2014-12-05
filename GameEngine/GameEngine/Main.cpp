#include "MemoryManager.h"
#include "LinearAllocator.h"
#include "StackAllocator.h"
#include "FreeListAllocator.h"
#include "PoolAllocator.h"

#include <iostream>

using namespace Utilities;

MemoryManager memoryManager;

#define MEM_SIZE 1048576000 //1GB

#define MAX_NUM_ALLOCS 100000

// In real instance create seperate mem for each allocator
void *mem;

void GetLinearAllocator()
{
	memoryManager.Get()->CreateLinearAllocator();

	int *number[MAX_NUM_ALLOCS];
	for (uint i = 1; i < 34; i++)
	{
		// Still need to pass in size of the object
		number[i - 1] = (int*)memoryManager.Get()->AllocateLinearAllocator(32, 8);
		*number[i - 1] = i;
	}

	for (int i = 0; i < 33; i++)
	{
		std::cout << "Number Address: " << number[i] <<
			"Number Value: " << *number[i] << std::endl;
	}

	memoryManager.Get()->ClearLinearAllocator();
}

void GetStackAllocator()
{
	//void *mem = malloc(MEM_SIZE);
	StackAllocator *stackAllocator = new StackAllocator(MEM_SIZE, mem);

	int *number[MAX_NUM_ALLOCS];
	for (uint i = 1; i < 34; i++)
	{
		number[i - 1] = (int*) stackAllocator->Allocate(32, 8);
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

void GetFreeListAllocator()
{
	memoryManager.Get()->CreateFreeListAllocator();

	int *number[MAX_NUM_ALLOCS];
	for (uint i = 0; i < 34; i++)
	{
		number[i] = (int*)memoryManager.Get()->AllocateFreeListAllocator(32, 8);
		*number[i] = i + 1;
	}

	for (int i = 0; i < 34; i++)
	{
		std::cout << "Number Address: " << number[i] <<
			"Number Value: " << *number[i] << std::endl;
	}

	for (int i = 0; i < 34; i++)
	{
		memoryManager.Get()->DeallocateFreeListAllocator(number);
	}
}

void GetPoolAllocator()
{
	PoolAllocator * poolAllocator = new PoolAllocator(32, 8, MEM_SIZE, mem);

	int *numbers[MAX_NUM_ALLOCS];
	for (int i = 0; i < 34; i++)
	{
		numbers[i] = (int*)poolAllocator->Allocate(32, 8);
		*numbers[i] = i;
	}

	for (int i = 0; i < 34; i++)
	{
		std::cout << "Number Address: " << numbers[i] <<
			"Number Value: " << *numbers[i] << std::endl;
	}

	for (int i = 0; i < 34; i++)
	{
		poolAllocator->Deallocate(numbers[i]);
	}

	delete poolAllocator;
}

int main()
{
	std::cout << memoryManager.Get();
	std::cout << std::endl;

	memoryManager.StartUp();
	mem = malloc(MEM_SIZE);

	std::cout << "Linear Allocator" << std::endl;
	//GetLinearAllocator();
	memoryManager.Get()->CreateLinearAllocator();

	int *numberOne[MAX_NUM_ALLOCS];
	for (uint i = 1; i < 34; i++)
	{
		// Still need to pass in size of the object
		numberOne[i - 1] = (int*)memoryManager.Get()->AllocateLinearAllocator(32, 8);
		*numberOne[i - 1] = i * 2;
	}

	for (int i = 0; i < 33; i++)
	{
		std::cout << "Number Address: " << numberOne[i] <<
			"Number Value: " << *numberOne[i] << std::endl;
	}

	//memoryManager.Get()->ClearLinearAllocator();

	std::cout << std::endl;

	/*std::cout << "Stack Allocator" << std::endl;
	GetStackAllocator();*/

	std::cout << std::endl;

	std::cout << "Free List Allocator" << std::endl;
	//GetFreeListAllocator();
	memoryManager.Get()->CreateFreeListAllocator();

	int *numberTwo[MAX_NUM_ALLOCS];
	for (uint i = 0; i < 34; i++)
	{
		numberTwo[i] = (int*)memoryManager.Get()->AllocateFreeListAllocator(32, 8);
		*numberTwo[i] = i + 1;
	}

	for (int i = 0; i < 34; i++)
	{
		std::cout << "Number Address: " << numberTwo[i] <<
			"Number Value: " << *numberTwo[i] << std::endl;
	}

	std::cout << std::endl;

	std::cout << "Linear Allocator Values" << std::endl;

	for (int i = 0; i < 33; i++)
	{
		std::cout << "Number Address: " << numberOne[i] <<
			"Number Value: " << *numberOne[i] << std::endl;
	}

	memoryManager.Get()->ClearLinearAllocator();

	for (int i = 0; i < 34; i++)
	{
		memoryManager.Get()->DeallocateFreeListAllocator(numberTwo[i]);
	}

	std::cout << std::endl;

	/*std::cout << "Pool Allocator" << std::endl;
	GetPoolAllocator();*/

	memoryManager.Get()->DestroyFreeListAllocator();
	memoryManager.Get()->DestroyLinearAllocator();
	memoryManager.ShutDown();

	std::cin.get();
	return 0;
}