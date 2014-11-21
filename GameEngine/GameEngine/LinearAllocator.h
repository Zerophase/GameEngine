#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include "Allocator.h"

// Simplest and fastest allocator
class LinearAllocator : public Allocator
{
public:
	LinearAllocator(u32 sizeBytes, void *start);
	~LinearAllocator();

	void *Allocate(u32 size, u8 alignment) override;
	void Deallocate(void *p) override;

	void Clear();

private:
	LinearAllocator(const LinearAllocator&);
	LinearAllocator &operator= (const LinearAllocator);

	void *currentPosition;
};

#endif // !LINEAR_ALLOCATOR_H



