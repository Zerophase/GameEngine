#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "Singleton.h"
#include "LinearAllocator.h"
#include "StackAllocator.h"
#include "FreeListAllocator.h"
#include "PoolAllocator.h"

namespace Utilities
{
	#define MEM_SIZE 51200

	class MemoryManager : private Singleton<MemoryManager>
	{
	private:
		static MemoryManager *memoryManager;

		void *memoryStackAllocator;
		void *memoryFreeListAllocator;
		void *memoryLinearAllocator;
		void *memoryPoolAllocator;

		LinearAllocator *linearAllocator;
		FreeListAllocator *freeListAllocator;
		StackAllocator *stackAllocator;
		PoolAllocator *poolAllocator;

	public:
		MemoryManager();
		~MemoryManager();

		void CreateLinearAllocator();
		void CreateFreeListAllocator();

		void DestroyLinearAllocator();
		void DestroyFreeListAllocator();

		void *AllocateLinearAllocator(u32 sizeBytes, u8 alignment);
		void ClearLinearAllocator();

		void *AllocateFreeListAllocator(u32 sizeBytes, u8 alignment);
		void DeallocateFreeListAllocator(void *p);

		virtual void StartUp();
		virtual void ShutDown();

		virtual MemoryManager *Get();
	};
}

#endif // !MEMORY_MANAGER_H