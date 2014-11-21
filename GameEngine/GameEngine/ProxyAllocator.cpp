#include "ProxyAllocator.h"

ProxyAllocator::ProxyAllocator(Allocator &allocator)
	: Allocator(allocator.GetSize(), allocator.GetStart()), allocator(allocator)
{

}


ProxyAllocator::~ProxyAllocator()
{
}

void * ProxyAllocator::Allocate(u32 size, u8 alignment)
{
	ASSERT(size != 0);
	numAllocations++;

	size_t mem = allocator.GetUsedMemory();

	void *p = allocator.Allocate(size, alignment);

	usedMemory += allocator.GetUsedMemory() - mem;

	return p;
}

void ProxyAllocator::Deallocate(void *p)
{
	numAllocations--;

	size_t mem = allocator.GetUsedMemory();

	allocator.Deallocate(p);

	usedMemory -= mem - allocator.GetUsedMemory();
}
