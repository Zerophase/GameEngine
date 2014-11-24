#include "LinearAllocator.h"


LinearAllocator::LinearAllocator(u32 sizeBytes, void *start)
	: Allocator(sizeBytes, start), currentPosition(start)
{
	ASSERT(size > 0);
}

LinearAllocator::~LinearAllocator()
{
	currentPosition = nullptr;
}

void *LinearAllocator::Allocate(u32 size, u8 alignment)
{
	ASSERT(size != 0);

	u8 adjustment = PointerMath::alignForwardAdjustment(currentPosition, alignment);

	if (usedMemory + adjustment + size > this->size)
		return nullptr;

	uptr alignedAddress = (uptr) currentPosition + adjustment;

	currentPosition = (void *) (alignedAddress + size);

	usedMemory += size + adjustment;
	numAllocations++;

	return (void*) alignedAddress;
}

void LinearAllocator::Deallocate(void *p)
{
	ASSERT(false && "Use Clear() instead");
}

void LinearAllocator::Clear()
{
	numAllocations = 0;
	usedMemory = 0;

	currentPosition = start;
}