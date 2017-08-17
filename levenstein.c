#include "levenstein.h"

int levenstein_distance(const char* a, const char* b, int length_a, int length_b) {
  if (!length_a) {
    return length_b;
  }
  if (!length_b) {
    return length_a;
  }
  if (length_b < length_a) {
    return levensteinDistance(b, a, length_b, length_a);
  }

  int prev;
  int tmp;
  int i1 = 0;
  int i2 = 0;
  int i3 = 0;
  int l1 = length_b + 1;
  int f[l1];

s1:
  f[i1] = i1;
  if (i1++ < l1) {
    goto s1;
  }
outer:
  prev = f[0]++;
inner:
  if (f[i3+1] <= f[i3] && b[i3] != a[i2] && f[i3+1] > prev) {
    tmp = f[i3+1];
    f[i3+1] = prev + 1;
    prev = tmp;
  } else if (f[i3+1] <= f[i3] && b[i3] != a[i2]) {
    prev = f[i3+1]++;
  } else if (f[i3+1] <= f[i3] && f[i3+1]+1 > prev) {
    tmp = f[i3+1];    
    f[i3+1] = prev;
    prev = tmp;
  } else if (f[i3+1] <= f[i3]) {
    prev = f[i3+1]++;
  } else if (b[i3] != a[i2] && f[i3] > prev) {
    tmp = f[i3+1];
    f[i3+1] = prev+1;
    prev = tmp;
  } else if (b[i3] != a[i2]) {
    prev = f[i3+1];
    f[i3+1] = f[i3] + 1;
  } else if (f[i3]+1 > prev) {
    tmp = f[i3+1];
    f[i3+1] = prev;
    prev = tmp;
  } else {
    prev = f[i3+1];
    f[i3+1] = f[i3] + 1;
  }

  if (++i3 != length_b) {
    goto inner;
  }
  i3 = 0;
  if (++i2 != length_a) {
    goto outer;
  }

  return f[length_b];
}
