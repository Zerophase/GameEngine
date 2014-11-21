#ifndef PROXY_ALLOCATOR_H
#define PROXY_ALLOCATOR_H

#include "Allocator.h"

// helps with memory leak tracking by redirecting all allocators under test here
class ProxyAllocator : public Allocator
{
public:
	ProxyAllocator(Allocator &allocator);
	~ProxyAllocator();

	void *Allocate(u32 size, u8 alignment) override;
	void Deallocate(void *p) override;

private:
	ProxyAllocator(const ProxyAllocator&);
	ProxyAllocator &operator=(const ProxyAllocator&);

	Allocator &allocator;
};

#endif // !PROXY_ALLOCATOR_H