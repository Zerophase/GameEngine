#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "Singleton.h"
#include "StackAllocator.h"

namespace Utilities
{
	class MemoryManager : private Singleton<MemoryManager>
	{
	private:
		static MemoryManager *memoryManager;

		

	public:
		MemoryManager();
		~MemoryManager();

		StackAllocator *stackAllocator;

		virtual void StartUp();
		virtual void ShutDown();

		virtual MemoryManager *Get();
	};
}

#endif // !MEMORY_MANAGER_H