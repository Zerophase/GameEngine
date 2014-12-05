#include "MemoryManager.h"

#include <iostream>

Utilities::MemoryManager *Utilities::MemoryManager::memoryManager = nullptr;

Utilities::MemoryManager::MemoryManager()
{
	memoryFreeListAllocator = malloc(MEM_SIZE);
	memoryLinearAllocator = malloc(MEM_SIZE);
}


Utilities::MemoryManager::~MemoryManager()
{
}

void Utilities::MemoryManager::StartUp()
{
	memoryManager = new MemoryManager();
}

void Utilities::MemoryManager::ShutDown()
{
	delete memoryManager;
}

Utilities::MemoryManager *Utilities::MemoryManager::Get()
{
	return memoryManager;
}

void Utilities::MemoryManager::CreateFreeListAllocator()
{
	freeListAllocator = new FreeListAllocator(MEM_SIZE,
		memoryFreeListAllocator);
}

void Utilities::MemoryManager::DestroyFreeListAllocator()
{
	delete freeListAllocator;
}

void Utilities::MemoryManager::CreateLinearAllocator()
{
	linearAllocator = new LinearAllocator(MEM_SIZE,
		memoryLinearAllocator);
}

void Utilities::MemoryManager::DestroyLinearAllocator()
{
	delete linearAllocator;
}

void *Utilities::MemoryManager::AllocateLinearAllocator(u32 sizeBytes, u8 alignment)
{
	return linearAllocator->Allocate(sizeBytes, alignment);
}

void *Utilities::MemoryManager::AllocateFreeListAllocator(u32 sizeBytes, u8 alignment)
{
	return freeListAllocator->Allocate(sizeBytes, alignment);
}

void Utilities::MemoryManager::ClearLinearAllocator()
{
	linearAllocator->Clear();
}

void Utilities::MemoryManager::DeallocateFreeListAllocator(void *p)
{
	/*int numAllocations = freeListAllocator->GetNumAllocations();
	for (int i = 0; i < numAllocations; i++)
	{*/
		freeListAllocator->Deallocate(p);
	//}
}

