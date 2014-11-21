#ifndef ALLOCATION_SCHEMAS_H
#define ALLOCATION_SCHEMAS_H

#include "Types.h"
#include "Debug.h"

#include "Allocator.h"


namespace allocator
{
	template<class T> T *newAllocate(Allocator &allocator)
	{
		return new (allocator.Allocate(sizeof(T), __alignof(T))) T;
	}

	template<class T> T *newAllocate(Allocator &allocator, const T &t)
	{
		return new (allocator.Allocate(sizeof(T), __alignof(T))) T(t);
	}

	template<class T> void deleteDeallocate(Allocator &allocator, T &object)
	{
		object.~T();
		allocator.Deallocate(&object);
	}

	template<class T> T *newArrayAllocate(Allocator &allocator, size_t length)
	{
		ASSERT(length != 0);

		u8 headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		T *p = ((T*)allocator.Allocate(sizeof(T) * (length + headerSize), __alignof(T)) + headerSize;
		*(((size_t*)p - 1) = length;

		for (size_t i = 0; i < length; i++)
			new (&p[i]) T;

		return p;
	}

	template<class T> void deleteArrayDeallocate(Allocator &allocator, T *arrayType)
	{
		ASSERT(arrayType != nullptr);

		size_t length = *(((size_t*)arrayType) - 1);

		for (size_t i = 0; i < length; i++)
			arrayType[i].~T();

		u8 headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0)
			headerSize += 1;

		allocator.Deallocate(arrayType - headerSize);
	}
};

#endif // !ALLOCATION_SCHEMAS_H
