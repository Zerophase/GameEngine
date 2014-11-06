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

	void *alloc(std::uint32_t sizeBytes);

	Marker GetMarker();

	void FreeToMarker(Marker marker);

	void Clear();
	Marker *TopOfStack() { return topOfStack; }
	Marker *BottomOfStack() { return bottomOfStack; }

private:
	Marker *topOfStack;
	Marker *bottomOfStack;

	Marker currentTop;
};

#endif // !STACK_ALLOCATOR_H