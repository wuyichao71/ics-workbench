#include <stdint.h>
#include <stdio.h>

uint64_t add_mod(uint64_t x, uint64_t y, uint64_t m);

int get_sign(uint64_t a, int i)
{
  return (a >> i) & 1;
}

int get_valid(uint64_t m)
{
  int valid = 0;
  for (; m > 0; valid++)
    m >>= 1;
  return valid;
}

uint64_t mod(uint64_t t, uint64_t m)
{
  int rest = 64 - get_valid(m);
  m = m << rest;
  for (int i = rest; i >= 0; i--)
  {
    if (t >= m)
      t -= m;
    m >>= 1;
  }
  return t;
}

uint64_t add_mod(uint64_t x, uint64_t y, uint64_t m)
{
  uint64_t t = x + y;
  if (t < x || t < y)
    return mod(mod(t, m) + mod(~m + 1, m), m);
    /* return mod(mod(t+1, m) + mod(-1ULL, m), m); */
  else
    return mod(t, m);
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) {
  uint64_t result = 0;
  int sign;
  uint64_t next_power = b;
  /* printf("--------------------\n"); */
  for (int i = 0; i < 64; ++i)
  {
    sign = get_sign(a, i);
    if (sign)
    {
      result = add_mod(result, next_power, m);
    }
    next_power = add_mod(next_power, next_power, m);
    /* printf("%d\n", get_sign(a, i)); */
  }
  /* printf("--------------------\n"); */
  return result;
  /* return (a * b) % m; // buggy */
}
