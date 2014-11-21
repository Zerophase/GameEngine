#include "PoolAllocator.h"

PoolAllocator::PoolAllocator(size_t objectSize, u8 objectAlignment, u32 size, void *mem)
	:Allocator(size, mem), objectSize(objectSize), objectAlignment(objectAlignment)
{
	ASSERT(objectSize >= sizeof(void*));

	// Calculate adjustment needed to keep object correctly aligned
	u8 adjustment = PointerMath::alignForwardAdjustment(mem, objectAlignment);

	freeList = (void **) PointerMath::Add(mem, adjustment);

	size_t numObjects = (size - adjustment) / objectSize;

	void **p = freeList;

	// Intialize free blocks list
	for (size_t i = 0; i < numObjects - 1; i++)
	{
		*p = PointerMath::Add(p, objectSize);
		p = (void **) *p;
	}

	*p = nullptr;
}


PoolAllocator::~PoolAllocator()
{
	freeList = nullptr;
}

void * PoolAllocator::Allocate(u32 size, u8 alignment)
{
	ASSERT(size == objectSize && alignment == objectAlignment);

	if (freeList == nullptr)
		return nullptr;

	void *p = freeList;

	freeList = (void **) (*freeList);

	usedMemory += size;
	numAllocations++;

	return p;
}

void PoolAllocator::Deallocate(void *p)
{
	*((void**) p) = freeList;

	freeList = (void **) p;

	usedMemory -= objectSize;
	numAllocations--;
}
