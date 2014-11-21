#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include "Allocator.h"

class StackAllocator : public Allocator
{
public:
	StackAllocator(u32 sizeBytes, void *start);
	~StackAllocator();

	void *Allocate(u32 size, u8 alignment) override;
	void Deallocate(void *p) override;

private:
	StackAllocator(const StackAllocator&);
	StackAllocator &operator=(const StackAllocator&);

	struct  AllocationHeader
	{
		#if _DEBUG
		void *prev_address;
		#endif // _DEBUG
		u8 adjustment;
	};

	#if _DEBUG
	void *_prev_position;
	#endif // _DEBUG
	
	void *currentPosition;
};

#endif // !STACK_ALLOCATOR_H