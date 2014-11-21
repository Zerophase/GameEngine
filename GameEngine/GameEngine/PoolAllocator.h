#ifndef POOL_ALLOCATOR_H
#define POOL_ALLOCATOR_H

#include "Allocator.h"

class PoolAllocator : public Allocator
{
public:
	PoolAllocator(size_t objectSize, u8 objectAlignment, u32 size, void *mem);
	~PoolAllocator();

	void *Allocate(u32 size, u8 alignment) override;
	void Deallocate(void *p) override;

private:
	PoolAllocator(const PoolAllocator&);
	PoolAllocator &operator=(const PoolAllocator&);

	u32 objectSize;
	u8 objectAlignment;

	void **freeList;
};

#endif // !POOL_ALLOCATOR_H