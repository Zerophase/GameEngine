#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstdint>

class Allocator
{
public:
	Allocator(std::uint32_t sizeBytes, void *start);
	virtual ~Allocator();

	virtual void *Allocate(std::uint32_t size, std::uint8_t alignment = 4) = 0;
	virtual void Deallocate(void *p) = 0;

	void *GetStart() const;
	std::uint32_t GetSize() const;
	std::uint32_t GetUsedMemory() const;
	std::uint32_t GetNumAllocations() const;

protected:
	void *start;
	std::uint32_t size;

	std::uint32_t usedMemory;
	std::uint32_t numAllocations;
};

#endif // !ALLOCATOR_H



