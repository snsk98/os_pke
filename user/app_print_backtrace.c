/*
 * Below is the given application for lab1_challenge1_backtrace.
 * This app prints all functions before calling print_backtrace().
 */

#include "user_lib.h"
#include "util/types.h"

void f8() { print_backtrace(7); }
void f7() { f8(); }
void f6() { f7(); }
void f5() { f6(); }
void f4() { f5(); }
void f3() { f4(); }
void f2() { f3(); }
void f1() { f2(); }

void fff(int * a) { *a=1+2; }
void ff() { int a=0; fff(&a); }

int main(void) {
  printu("back trace the user app in the following:\n");
  // ff();
  f1();
  exit(0);
  return 0;
}
