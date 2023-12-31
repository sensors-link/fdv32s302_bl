/* See LICENSE of license details. */

#include "stub.h"

void *_sbrk(ptrdiff_t incr)
{
	extern char	 _end[];
	extern char	 _heap_end[];
	static char *curbrk = _end;

	if ((curbrk + incr < _end) || (curbrk + incr > _heap_end)) // cppcheck-suppress comparePointers
		return NULL - 1;

	curbrk += incr;
	return curbrk - incr;
}
