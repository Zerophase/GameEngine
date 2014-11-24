#include "StackAllocator.h"

#include <stdlib.h>
StackAllocator::StackAllocator(u32 sizeBytes, void *start)
	:Allocator(sizeBytes, start), currentPosition(start)
{
	ASSERT(sizeBytes > 0);

	#if _DEBUG
	_prev_position = nullptr;
	#endif
}

StackAllocator::~StackAllocator()
{
	#if _DEBUG
	_prev_position = nullptr;
	#endif // _DEBUG

	currentPosition = nullptr;
}

void *StackAllocator::Allocate(u32 sizeBytes, u8 alignment)
{
	ASSERT(sizeBytes != 0);

	u8 adjustment = PointerMath::alignForwardAdjustmentWithHeader(currentPosition,
		alignment, sizeof(AllocationHeader));

	if (usedMemory + adjustment + sizeBytes > size)
		return nullptr;

	void *alignedAddress = PointerMath::Add(currentPosition, adjustment);

	AllocationHeader *header = (AllocationHeader*) 
		(PointerMath::Subtract(alignedAddress, sizeof(AllocationHeader)));

	header->adjustment = adjustment;

	#if _DEBUG
	header->prev_address = _prev_position;
	_prev_position = alignedAddress;
	#endif // _DEBUG

	currentPosition = PointerMath::Add(alignedAddress, sizeBytes);

	usedMemory += sizeBytes + adjustment;
	numAllocations++;

	return alignedAddress;
}

void StackAllocator::Deallocate(void *p)
{
	ASSERT(p == _prev_position);

	// Access the AllocationHeader in the bytes before p
	AllocationHeader *header = (AllocationHeader*)
		(PointerMath::Subtract(p, sizeof(AllocationHeader)));

	usedMemory -= (uptr) currentPosition - (uptr) p + header->adjustment;

	currentPosition = PointerMath::Subtract(p, header->adjustment);

	#if _DEBUG
	_prev_position = header->prev_address;
	#endif // _DEBUG

	numAllocations--;
}