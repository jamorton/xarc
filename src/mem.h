
#ifndef __MEM_H__
#define __MEM_H__

// screw standards, the alternatives are terrible.
#define mem_ptr_size(ptr) (malloc_usable_size(ptr))

#define mem_new(type) ((type *)mem_calloc(1, sizeof(type)))
#define mem_del(obj)  (mem_free(obj))

#define mem_zero(ptr, n) (memset(ptr, 0, n));

#define mem_create(type, count) ((type *)mem_calloc(count, sizeof(type)))

void * mem_alloc(size_t sz);
void * mem_calloc(size_t n, size_t sz);
void * mem_realloc(void * ptr, size_t sz);
void   mem_free(void * ptr);

size_t mem_usage();

#endif
