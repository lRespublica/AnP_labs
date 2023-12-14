#include "string.h"
#include "stdio.h"
#include "unistd.h"

void* mcalloc (size_t count, size_t eltsize, unsigned char value)
{
  void* ptr = (void*)sbrk (count * eltsize);
  if (value != 0)
    memset (ptr, value, count * eltsize);
  return ptr;
}

int main()
{
    char* str = mcalloc(10, sizeof(char), 'G');

    for(int i = 0; i < 10; i++)
        printf("%d\n", str[i]);
}
