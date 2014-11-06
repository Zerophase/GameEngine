#include "StackAllocator.h"

#include <stdlib.h>

StackAllocator::StackAllocator(std::uint32_t stackSizeBytes)
{
	currentTop = stackSizeBytes;
	bottomOfStack = &stackSizeBytes;
	topOfStack = &stackSizeBytes;
	malloc(stackSizeBytes);
}

void *StackAllocator::alloc(std::uint32_t sizeBytes)
{
	bottomOfStack = &sizeBytes;
	return alloc(*bottomOfStack);
}

StackAllocator::Marker StackAllocator::GetMarker()
{
	return currentTop;
}

void StackAllocator::FreeToMarker(StackAllocator::Marker marker)
{
	*bottomOfStack = marker;
}

void StackAllocator::Clear()
{
	delete topOfStack;
	delete bottomOfStack;
}

//void *StackAllocator::operator new(size_t size)
//{
//	return malloc(size);
//}
//
//void *StackAllocator::operator new[](size_t size)
//{
//	return malloc(size);
//}
//
//void StackAllocator::operator delete(void *mem)
//{
//	free(mem);
//}
//
//void StackAllocator::operator delete[](void *mem)
//{
//	free(mem);
//}