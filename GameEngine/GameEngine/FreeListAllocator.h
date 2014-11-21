#ifndef FREE_LIST_ALLOCATOR_H
#define FREE_LIST_ALLOCATOR_H

#include "Allocator.h"

class FreeListAllocator : public Allocator
{
public:
	FreeListAllocator(u32 sizeBytes, void *start);
	~FreeListAllocator();

	void *Allocate(u32 size, u8 alignment) override;
	void Deallocate(void *p) override;

private:

	struct AllocationHeader
	{
		size_t size;
		u8 adjustment;
	};

	struct FreeBlock
	{
		size_t size;
		FreeBlock *next;
	};

	FreeListAllocator(const FreeListAllocator&);
	FreeListAllocator &operator=(const FreeListAllocator&);

	FreeBlock *freeBlocks;
};

#endif // !FREE_LIST_ALLOCATOR_H