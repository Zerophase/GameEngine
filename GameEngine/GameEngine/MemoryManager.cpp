#include "MemoryManager.h"

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
}

void Utilities::MemoryManager::ShutDown()
{
	delete memoryManager;
}

Utilities::MemoryManager *Utilities::MemoryManager::Get()
{
	return memoryManager;
}