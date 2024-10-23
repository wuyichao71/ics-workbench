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
      "movq %[x], %%rax;"
      "shrq %%cl, %%rax;"
      "andl $1, %%eax;"
      "testq %%rax, %%rax;"
      "je .POPCNT_INCR;"
      "incl %[s];"
      ".POPCNT_INCR:;"
      "incl %[i];"
      "jmp .POPCNT_BEGIN;"
      ".POPCNT_RET:;"
      :[s] "+r"(s), [i] "+r"(i), [x]"+r"(x)
      :
      : "%rax", "%rcx"
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
