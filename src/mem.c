
#include <stdlib.h>
#include <stdio.h>
#include "mem.h"

static void _oom()
{
	fprintf(stderr, "out of memory!\n");
	abort();
}

static size_t _memUsed = 0;

size_t mem_usage()
{
	return _memUsed;
}

void * mem_alloc(size_t sz)
{
	void * ptr = malloc(sz);

	if (!ptr)
		_oom();

	_memUsed += mem_ptr_size(ptr);
	return ptr;
}

void * mem_calloc(size_t n, size_t sz)
{
	void * ptr = calloc(n, sz);

	if (!ptr)
		_oom();

	_memUsed += mem_ptr_size(ptr);
	return ptr;
}

void * mem_realloc(void * ptr, size_t sz)
{
	_memUsed -= mem_ptr_size(ptr);

	void * new = realloc(ptr, sz);

	if (!new)
		_oom();

	_memUsed += mem_ptr_size(new);
	return new;
}

void * mem_free(void * ptr)
{
	_memUsed -= mem_ptr_size(ptr);
	free(ptr);
}
