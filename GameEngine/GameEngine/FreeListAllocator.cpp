#include "FreeListAllocator.h"


FreeListAllocator::FreeListAllocator(u32 sizeBytes, void *start)
	:Allocator(sizeBytes, start), freeBlocks((FreeBlock*)start)
{ 
	ASSERT(sizeBytes > sizeof(FreeBlock));

	freeBlocks->size = sizeBytes;
	freeBlocks->next = nullptr;
}


FreeListAllocator::~FreeListAllocator()
{
	freeBlocks = nullptr;
}

void * FreeListAllocator::Allocate(u32 size, u8 alignment)
{
	ASSERT(size != 0 && alignment != 0);

	FreeBlock *previousFreeBlock = nullptr;
	FreeBlock *freeBlock = freeBlocks;

	while (freeBlock != nullptr)
	{
		// Calculate adjustment needed to keep object aligned
		u8 adjustment = PointerMath::alignForwardAdjustmentWithHeader(
			freeBlock, alignment, sizeof(AllocationHeader));
		
		size_t totalSize = size + adjustment;

		//If allocation doesn't fit in the freeblock, try the next
		if (freeBlock->size < totalSize)
		{
			previousFreeBlock = freeBlock;
			freeBlock = freeBlock->next;
			continue;
		}

		static_assert(sizeof(AllocationHeader) >= sizeof(FreeBlock), 
			"sizeof(AllocationHeader) < sizeof(FreeBlock)");

		// If allocations in the remaining memory will be impossible
		if (freeBlock->size - totalSize <= sizeof(AllocationHeader))
		{
			// Increase allocation size instead of creating a freeblock
			totalSize = freeBlock->size;

			if (previousFreeBlock != nullptr)
				previousFreeBlock->next = freeBlock->next;
			else
				freeBlocks = freeBlock->next;
		}
		else
		{
			// Else create a new FreeBlock containing remaining memory
			FreeBlock *nextBlock = (FreeBlock*) (PointerMath::Add(freeBlock, totalSize));
			nextBlock->size = freeBlock->size - totalSize;
			nextBlock->next = freeBlock->next;

			if (previousFreeBlock != nullptr)
				previousFreeBlock->next = nextBlock;
			else
				freeBlocks = nextBlock;
		}

		uptr alignedAddress = (uptr) freeBlock + adjustment;

		AllocationHeader *header = (AllocationHeader*) 
			(alignedAddress - sizeof(AllocationHeader));
		header->size = totalSize;
		header->adjustment = adjustment;

		usedMemory += totalSize;
		numAllocations++;

		ASSERT(PointerMath::alignForwardAdjustment(
			(void*) alignedAddress, alignment) == 0);

		return (void *) alignedAddress;
	}

	// ASSERT(false && "Couldn't find free block large enough!")
	return nullptr;
}

void FreeListAllocator::Deallocate(void *p)
{
	ASSERT(p != nullptr);

	AllocationHeader *header = (AllocationHeader*) 
		PointerMath::Subtract(p, sizeof(AllocationHeader));

	uptr blockStart = reinterpret_cast<uptr>(p) -header->adjustment;
	size_t blockSize = header->size;
	uptr blockEnd = blockStart + blockSize;

	FreeBlock *previousFreeBlock = nullptr;
	FreeBlock *freeBlock = freeBlocks;

	while (freeBlock != nullptr)
	{
		if ((uptr)freeBlock >= blockEnd)
			break;

		previousFreeBlock = freeBlock;
		freeBlock = freeBlock->next;
	}

	if (previousFreeBlock == nullptr)
	{
		previousFreeBlock = (FreeBlock *) blockStart;
		previousFreeBlock->size = blockSize;
		previousFreeBlock->next = freeBlocks;

		freeBlocks = previousFreeBlock;
	}
	else if ((uptr) previousFreeBlock + previousFreeBlock->size == blockStart)
		previousFreeBlock->size += blockSize;
	else
	{
		FreeBlock *temp = (FreeBlock*) blockStart;
		temp->size = blockSize;
		temp->next = previousFreeBlock->next;
		previousFreeBlock->next = temp;

		previousFreeBlock = temp;
	}

	if (freeBlock != nullptr && (uptr) freeBlock == blockEnd)
	{
		previousFreeBlock->size += freeBlock->size;
		previousFreeBlock->next = freeBlock->next;
	}

	numAllocations--;
	usedMemory -= blockSize;
}