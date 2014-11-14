#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include <cstdint>

class StackAllocator
{
public:
	/*void *operator new(size_t size);
	void operator delete (void *mem);
	void *operator new[] (size_t size);
	void operator delete[] (void *mem);*/

	typedef std::uint32_t Marker;

	explicit StackAllocator(std::uint32_t stackSizeBytes);
	virtual ~StackAllocator();

	void *alloc(std::uint32_t sizeBytes);

	Marker GetMarker();

	void FreeToMarker(Marker marker);

	void Clear();
	Marker *TopOfStack() { return topOfStack; }
	Marker *BottomOfStack() { return bottomOfStack; }

private:
	std::uint32_t *topOfStack;
	std::uint32_t *bottomOfStack;

	Marker currentTop;

	//Use for size if different sized memory is used
	//size_t size;

	std::uint32_t usedMemory;
	std::uint32_t numAllocations;
	
};

#endif // !STACK_ALLOCATOR_H