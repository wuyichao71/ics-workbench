#include "asm.h"
#include <assert.h>
#include <stdio.h>

int main() {
  asm_jmp_buf buf;
  int r = asm_setjmp(buf);
  if (r == 0) {
    assert(asm_add(1234, 5678) == 6912);
    /* printf("%d\n", asm_popcnt(0x0123456789abcdefULL)); */
    assert(asm_popcnt(0x0123456789abcdefULL) == 32);
    // TODO: add more tests here.
    char dest[1024];
    char src[1024] = "1234";
    asm_memcpy(dest, src, 4);
    for (int i = 0; i < 4; i++)
      assert(dest[i] == src[i]);
    asm_longjmp(buf, 123);
  } else {
    assert(r == 123);
    printf("PASSED.\n");
  }
}
