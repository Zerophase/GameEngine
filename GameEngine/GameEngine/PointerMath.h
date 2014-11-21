#ifndef POINTER_MATH_H
#define POINTER_MATH_H

#include "Types.h"

namespace PointerMath
{
	inline void *alignForward(void *address, u8 alignment)
	{
		return (void*) ((reinterpret_cast<uptr>(address) +static_cast<uptr>(alignment - 1)) & static_cast<uptr>(~(alignment - 1)));
	}

	inline u8 alignForwardAdjustment(const void *address, u8 alignment)
	{
		u8 adjustment = alignment - (reinterpret_cast<uptr>(address) & static_cast<uptr>(alignment - 1));

		if (adjustment == alignment)
			return 0; // already aligned

		return adjustment;
	}

	inline u8 alignForwardAdjustmentWithHeader(const void *address, u8 alignment, u8 headerSize)
	{
		u8 adjustment = alignForwardAdjustment(address, alignment);

		u8 neededSpace = headerSize;

		if (adjustment < neededSpace)
		{
			neededSpace -= adjustment;

			// increase adjustment to fit header
			adjustment += alignment * (neededSpace / alignment);

			if (neededSpace % alignment > 0)
				adjustment += alignment;
		}

		return adjustment;
	}

	inline void *Add(void *p, size_t x)
	{
		return (void *) (reinterpret_cast<uptr>(p) +x);
	}

	inline const void *Add(const void *p, size_t x)
	{
		return (const void *) (reinterpret_cast<uptr>(p) + x);
	}

	inline void *Subtract(void *p, size_t x)
	{
		return (void*) (reinterpret_cast<uptr>(p) -x);
	}

	inline const void *Subtract(const void *p, size_t x)
	{
		return (const void*) (reinterpret_cast<uptr>(p) -x);
	}
}

#endif