#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "Singleton.h"
#include "LinearAllocator.h"
#include "StackAllocator.h"
#include "FreeListAllocator.h"
#include "PoolAllocator.h"
#include "AllocationSchemas.h"

namespace Utilities
{
#define MEM_SIZE 1048576000
#define MEM_SIZE_POOL 52428800
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

		LinearAllocator &GetLinearAllocator();
		void CreateLinearAllocator();
		void DestroyLinearAllocator();
		void *AllocateLinearAllocator(u32 sizeBytes, u8 alignment);
		void ClearLinearAllocator();

		FreeListAllocator &GetFreeListAllocator();
		void CreateFreeListAllocator();
		void DestroyFreeListAllocator();
		void *AllocateFreeListAllocator(u32 sizeBytes, u8 alignment);
		void DeallocateFreeListAllocator(void *p);
		
		StackAllocator &GetStackAllocator();
		void CreateStackAllocator();
		void DestroyStackAllocator();
		void *AllocateStackAllocator(u32 sizeBytes, u8 alignment);
		void DeallocateStackAllocator(void *p);

		PoolAllocator &GetPoolAllocator();
		void CreatePoolAllocator();
		void DestroyPoolAllocator();
		void *AllocatePoolAllocator(u32 sizeBytes, u8 alignment);
		void DeallocatePoolAllocator(void *p);

		virtual void StartUp();
		virtual void ShutDown();

		virtual MemoryManager *Get();
	};
}

#endif // !MEMORY_MANAGER_H