#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "Types.h"
#include "Debug.h"
#include "PointerMath.h"

class Allocator
{
public:
	Allocator(u32 sizeBytes, void *start);
	virtual ~Allocator();

	virtual void *Allocate(u32 size, u8 alignment = 4) = 0;
	virtual void Deallocate(void *p) = 0;

	void *GetStart() const;
	u32 GetSize() const;
	u32 GetUsedMemory() const;
	u32 GetNumAllocations() const;

protected:
	void *start;
	u32 size;

	u32 usedMemory;
	u32 numAllocations;
};

#endif // !ALLOCATOR_H



