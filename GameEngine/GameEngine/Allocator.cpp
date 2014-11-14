#include "Allocator.h"

#include <assert.h>

Allocator::Allocator(std::uint32_t sizeBytes, void *start)
{
	this->start = start;
	this->size = size;

	usedMemory = 0;
	numAllocations = 0;
}


Allocator::~Allocator()
{
	assert(numAllocations == 0 && usedMemory == 0);

	start = nullptr;
	size = 0;
}

void *Allocator::GetStart() const
{
	return start;
}

std::uint32_t Allocator::GetSize() const
{
	return size;
}

std::uint32_t Allocator::GetUsedMemory() const
{
	return usedMemory;
}

std::uint32_t Allocator::GetNumAllocations() const
{
	return numAllocations;
}
