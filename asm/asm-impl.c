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
      :[s]"+r"(s), [i]"+c"(i)
      :[x]"r"(x)
      : "%rax"
      );
  return s;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  /* return memcpy(dest, src, n); */
  size_t i = 0;
  asm volatile (
      ".MEMCPY_BEGIN:\n\t"
      "cmpq %[n], %[i]\n\t"
      "jge .MEMCPY_END\n\t"
      "movb (%[src],%[i],1), %%al\n\t"
      "movb %%al, (%[dest],%[i],1)\n\t"
      "incq %[i]\n\t"
      "jmp .MEMCPY_BEGIN\n\t"
      ".MEMCPY_END:\n\t"
      :[i]"+r"(i)
      :[src]"r"(src), [n]"r"(n), [dest]"r"(dest)
      :"rax", "memory"
      );
  return dest;
  /* for (; i < n; i++) */ 
  /*   ((char *)dest)[i] =  ((char *)src)[i]; */
  /* return dest; */
}

int asm_setjmp(asm_jmp_buf env) {
  return setjmp(env);
  /* asm volatile( */
  /*     "movq %%rbx, (%[env])\n\t" */
  /*     "movq %%rbp, 0x8(%[env])\n\t" */
  /*     "movq %%r12, 0x10(%[env])\n\t" */
  /*     "movq %%r13, 0x18(%[env])\n\t" */
  /*     "movq %%r14, 0x20(%[env])\n\t" */
  /*     "movq %%r15, 0x28(%[env])\n\t" */
  /*     "lea 8(%%rsp), %%rdx\n\t" */
  /*     "movq %%rdx, 0x30(%[env])\n\t" */
  /*     "movq (%%rsp), %%rdx\n\t" */
  /*     "movq %%rdx, 0x38(%[env])\n\t" */
  /*     : */
  /*     :[env]"r"(env) */
  /*     :"rdx", "memory" */
  /*     ); */
  /* return 0; */
}

void asm_longjmp(asm_jmp_buf env, int val) {
  longjmp(env, val);
  /* asm volatile( */
  /*     "movq (%[env]), %%rbx\n\t" */
  /*     "movq 0x8(%[env]), %%rbp\n\t" */
  /*     "movq 0x10(%[env]), %%r12\n\t" */
  /*     "movq 0x18(%[env]), %%r13\n\t" */
  /*     "movq 0x20(%[env]), %%r14\n\t" */
  /*     "movq 0x28(%[env]), %%r15\n\t" */
  /*     "movq 0x30(%[env]), %%rsp\n\t" */
  /*     "movq 0x38(%[env]), %%rdx\n\t" */
  /*     "movl %[val], %%eax\n\t" */
  /*     "testl %%eax, %%eax\n\t" */
  /*     "jne .LONGJMP_RET\n\t" */
  /*     "movl $1, %%eax\n\t" */
  /*     ".LONGJMP_RET:\n\t" */
  /*     "jmp *%%rdx" */
  /*     : */
  /*     :[env]"r"(env), [val]"r"(val) */
  /*     :"rax", "rbp", "rbx", "r12", "r13", "r14", "r15", "rdx", "rsp" */
  /*     ); */
}
