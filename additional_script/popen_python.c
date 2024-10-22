#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <assert.h>

#define U64 "%" PRIu64

int main()
{
  uint64_t a, b, m;
  char cmd[1024];
  char buf[1024];
  FILE *fp = fopen("input", "r");
  while (fscanf(fp, U64 U64 U64, &a, &b, &m) == 3)
  {
    sprintf(cmd, "python3 -c 'a = "U64"; b = "U64"; m = "U64"; print(f\"{a} * {b} mod {m} = {(a * b) %% m}\")'", a, b, m);
    /* printf("%s\n", cmd); */
    /* continue; */
    FILE *fp_out = popen(cmd, "r");
    assert(fp_out);
    fgets(buf, 1024, fp_out);
    printf("%s", buf);
  }
  return 0;
}
