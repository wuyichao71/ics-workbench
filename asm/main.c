#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
  asm_jmp_buf buf;
  int r = asm_setjmp(buf);
  if (r == 0) {
    assert(asm_add(1234, 5678) == 6912);
    assert(asm_popcnt(0x0123456789abcdefULL) == 32);
    // TODO: add more tests here.
    printf("Begin check of 'asm_popcnt'\n");
    assert(asm_popcnt(0b0) == 0);
    assert(asm_popcnt(0b01) == 1);
    printf("Finish check of 'asm_popcnt'\n");
    printf("Begin check of 'asm_memcpy'\n");
    char dest[1024];
    char src[1024] = "1234";
    asm_memcpy(dest, src, 4);
    for (int i = 0; i < 4; i++)
      assert(dest[i] == src[i]);
    printf("Finish check of 'asm_memcpy'\n");
    asm_longjmp(buf, 123);
    /* asm_longjmp(buf, 0); */
    /* printf("%d\n", __WORDSIZE); */
  } else {
    assert(r == 123);
    /* assert(r == 1); */
    printf("PASSED.\n");
  }
}
