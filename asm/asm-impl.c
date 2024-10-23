#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  /* return a + b; */
  asm(
      "addq %[b], %[a];"
      /* "addq %[m], %[t];" */
      :[a] "+r"(a)
      :[b] "r"(b)
      );
  return a;
}

int asm_popcnt(uint64_t x) {
  /* int s = 0; */
  /* for (int i = 0; i < 64; i++) { */
  /*   if ((x >> i) & 1) s++; */
  /* } */
  /* return s; */
  int s = 0;
  int i = 0;
  asm(
      ".POPCNT_BEGIN:;"
      "cmpl $64, %[i];"
      "jge .POPCNT_RET;"
      "movl %[i], %%ecx;"
      "shrq %%cl, %[x];"
      "movq %[x], %%rax;"
      "andq $1, %%rax;"
      "testq %%rax, %%rax;"
      "je .POPCNT_INCR;"
      "incl %[s];"
      ".POPCNT_INCR:;"
      "incl %[i];"
      "jmp .POPCNT_BEGIN;"
      ".POPCNT_RET:;"
      :[s] "+r"(s), [i] "+r"(i)
      :[x] "r"(x)
      : "%eax", "%ecx"
      );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  return memcpy(dest, src, n);
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
