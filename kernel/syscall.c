/*
 * contains the implementation of all syscalls.
 */

#include <stdint.h>
#include <errno.h>

#include "util/types.h"
#include "syscall.h"
#include "string.h"
#include "process.h"
#include "util/functions.h"

#include "spike_interface/spike_utils.h"

//
// implement the SYS_user_print syscall
//
ssize_t sys_user_print(const char* buf, size_t n) {
  sprint(buf);
  return 0;
}

//
// implement the SYS_user_exit syscall
//
ssize_t sys_user_exit(uint64 code) {
  sprint("User exit with code:%d.\n", code);
  // in lab1, PKE considers only one app (one process). 
  // therefore, shutdown the system when the app calls exit()
  shutdown(code);
}

//
// implement the SYS_user_backtrace syscall
// lab1_challenge1
//
ssize_t sys_user_backtrace(uint64 n){
  // sprint("hey look here\nra:%lx sp:%lx fp:%lx epc:%lx thing_in_stack:%lx %lx %lx\ntf things are above.\n",current->trapframe->regs.ra,current->trapframe->regs.sp,current->trapframe->regs.s0,current->trapframe->epc,*(uint64*)(current->trapframe->regs.s0-8),*(uint64*)(current->trapframe->regs.s0+8),*(uint64*)(current->trapframe->regs.s0+16));

  // for(int i=0;i<20;i++){
  //   //从print_backtrace的stack开始打印20个8byte看看
  //   sprint("%d: addr=%lx val=%lx\n",i,current->trapframe->regs.sp+i*8,*(uint64*)(current->trapframe->regs.sp+i*8));
  // }

  trapframe* tf = current->trapframe;
  uint64 ra,fp=*(uint64*)(tf->regs.s0-8);//初始化 fp为调用do_user_call的函数（lab1_challenge1中为print_backtrace）的栈底指针
  
  //回溯调用栈
  do{
    //first we get the ra 
    ra = *(uint64*) (fp-8);

    //print the info we need
    sprint("NO.%d: ra%lx\n",n,ra);

    //check. if the func is main func, we stop
    if(0) break;

    //update fp
    fp = *(uint64*) (fp-16);

  }while(--n);

  return 0;
}

//
// [a0]: the syscall number; [a1] ... [a7]: arguments to the syscalls.
// returns the code of success, (e.g., 0 means success, fail for otherwise)
//
long do_syscall(long a0, long a1, long a2, long a3, long a4, long a5, long a6, long a7) {
  switch (a0) {
    case SYS_user_print:
      return sys_user_print((const char*)a1, a2);
    case SYS_user_exit:
      return sys_user_exit(a1);
    case SYS_user_backtrace:
      return sys_user_backtrace(a1);
    default:
      panic("Unknown syscall %ld \n", a0);
  }
}
