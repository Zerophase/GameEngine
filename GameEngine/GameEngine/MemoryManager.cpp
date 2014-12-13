#include "MemoryManager.h"

#include <iostream>

Utilities::MemoryManager *Utilities::MemoryManager::memoryManager = nullptr;

Utilities::MemoryManager::MemoryManager()
{
	
}


Utilities::MemoryManager::~MemoryManager()
{
	
}

void Utilities::MemoryManager::StartUp()
{
	memoryManager = new MemoryManager();

	memoryManager->memoryFreeListAllocator = malloc(MEM_SIZE);
	memoryManager->memoryLinearAllocator = malloc(MEM_SIZE);
	memoryManager->memoryPoolAllocator = malloc(MEM_SIZE_POOL);
	memoryManager->memoryStackAllocator = malloc(MEM_SIZE);

	memoryManager->CreateFreeListAllocator();
	memoryManager->CreateLinearAllocator();
	memoryManager->CreatePoolAllocator();
	memoryManager->CreateStackAllocator();
}

void Utilities::MemoryManager::ShutDown()
{
	memoryManager->DestroyFreeListAllocator();
	memoryManager->DestroyLinearAllocator();
	memoryManager->DestroyPoolAllocator();
	memoryManager->DestroyStackAllocator();

	delete memoryManager;
}

Utilities::MemoryManager *Utilities::MemoryManager::Get()
{
	return memoryManager;
}

#pragma region Linear Allocator 
LinearAllocator &Utilities::MemoryManager::GetLinearAllocator()
{
	return *linearAllocator;
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

void Utilities::MemoryManager::ClearLinearAllocator()
{
	linearAllocator->Clear();
}
#pragma endregion Schema for allocating linearly

#pragma region Free List Allocator
FreeListAllocator & Utilities::MemoryManager::GetFreeListAllocator()
{
	return *freeListAllocator;
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

void *Utilities::MemoryManager::AllocateFreeListAllocator(u32 sizeBytes, u8 alignment)
{
	return freeListAllocator->Allocate(sizeBytes, alignment);
}

void Utilities::MemoryManager::DeallocateFreeListAllocator(void *p)
{
	freeListAllocator->Deallocate(p);
}
#pragma endregion Schema for allocating to a list of free blocks of memory

#pragma region Stack Allocator
StackAllocator &Utilities::MemoryManager::GetStackAllocator()
{
	return *stackAllocator;
}

void Utilities::MemoryManager::CreateStackAllocator()
{
	stackAllocator = new StackAllocator(MEM_SIZE, memoryStackAllocator);
}

void Utilities::MemoryManager::DestroyStackAllocator()
{
	delete stackAllocator;
}

void *Utilities::MemoryManager::AllocateStackAllocator(u32 sizeBytes, u8 alignment)
{
	return stackAllocator->Allocate(sizeBytes, alignment);
}

void Utilities::MemoryManager::DeallocateStackAllocator(void *p)
{
	stackAllocator->Deallocate(p);
}
#pragma endregion Allocate memory in a stack

#pragma region Pool Allocator
PoolAllocator & Utilities::MemoryManager::GetPoolAllocator()
{
	return *poolAllocator;
}

void Utilities::MemoryManager::CreatePoolAllocator()
{
	poolAllocator = new PoolAllocator(32, 8, MEM_SIZE_POOL, memoryPoolAllocator);
}

void Utilities::MemoryManager::DestroyPoolAllocator()
{
	delete poolAllocator;
}

void * Utilities::MemoryManager::AllocatePoolAllocator(u32 sizeBytes, u8 alignment)
{
	return poolAllocator->Allocate(sizeBytes, alignment);
}

void Utilities::MemoryManager::DeallocatePoolAllocator(void *p)
{
	poolAllocator->Deallocate(p);
}
#pragma endregion Pools Memory

