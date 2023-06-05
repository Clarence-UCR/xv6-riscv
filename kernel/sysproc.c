#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

int sys_count = 0;

uint64
sys_increase_syscall_count()
{
  sys_count++;
  return sys_count;
}

uint64
sys_sched_statistics()
{	
  sched_statistics();
  return 0;
}

uint64
sys_sched_tickets(void)
{
  int tickets;
  argint(0, &tickets);
  sched_tickets(tickets);
  return 0; 
}

uint64
sys_clone(void) 
{
  int pid;
  void *stack;
  argaddr(0, (void*)&stack);
  pid = clone(stack);
  printf("sysproc returning %d \n", pid);
  return pid;
}

uint64
sys_info(void)
{
  int n;
  int result;
  argint(0, &n);
  if (n == 1) 
  {
    result = sys_count;
  } else {
    result = info(n);
  }
  return result;
}

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
