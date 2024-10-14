#include <stdint.h>
#include <stdio.h>

int get_sign(uint64_t a, int i)
{
  return (a >> i) & 1;
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t result = 0;
  for (int i = 0; i < 64; ++i)
  {
    printf("%d\n", get_sign(a, i));
  }
  return result;
  /* return (a * b) % m; // buggy */
}
