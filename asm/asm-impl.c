#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  /* return a + b; */
  asm(
      "addq %[b], %[a]"
      /* "addq %[m], %[t];" */
      :[a] "+a"(a)
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
      ".POPCNT_BEGIN:\n\t"
      "cmpl $64, %[i]\n\t"
      "jge .POPCNT_RET\n\t"
      "movl %[i], %%ecx\n\t"
      "movq %[x], %%rax\n\t"
      "shrq %%cl, %%rax\n\t"
      "andl $1, %%eax\n\t"
      "testq %%rax, %%rax\n\t"
      "je .POPCNT_INCR\n\t"
      "incl %[s]\n\t"
      ".POPCNT_INCR:\n\t"
      "incl %[i]\n\t"
      "jmp .POPCNT_BEGIN\n\t"
      ".POPCNT_RET:\n\t"
      :[s] "+r"(s)
      :[i]"r"(i), [x]"r"(x)
      : "%rax", "%ecx"
      );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  /* return memcpy(dest, src, n); */
  size_t i = 0;
  asm(
      ".MEMCPY_BEGIN:;"
      "cmpq %[n], %[i];"
      "jge .MEMCPY_END;"
      "movb (%[src],%[i],1), %%al;"
      "movb %%al, (%[dest],%[i],1);"
      "incq %[i];"
      "jmp .MEMCPY_BEGIN;"
      ".MEMCPY_END:;"
      :[dest]"+r"(dest)
      :[i]"r"(i), [src]"r"(src), [n]"r"(n)
      :"rax"
      );
  return dest;
  /* for (; i < n; i++) */ 
  /*   ((char *)dest)[i] =  ((char *)src)[i]; */
  /* return dest; */
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
}
