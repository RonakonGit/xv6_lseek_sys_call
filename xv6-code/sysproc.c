#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int int1;

  if(argint(0, &int1) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(int1) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int int1;
  uint ticks0;

  if(argint(0, &int1) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < int1){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int lseek(int fd,unit offset, int base) {
	char *char1;
	char *char2;
	int bufffer_new;
	int int1;
	int looper1;
	struct file *f;
	argfd(0, &fd, &f);
	argint(1, &offset);
	argint(2, &whence);
// char 
	if( base == SEEK_SET) {
		bufffer_new = offset;
	}
	if (base == SEEK_CUR){
		bufffer_new = f->off + offset;
	}
	if (base == SEEK_END){
		bufffer_new = f->ip->size + offset;
	}
	if (bufffer_new < f->ip->size) {
		return -1;
	}
	
	if (bufffer_new > f->ip->size){
		int1 = newoff - f->ip->size;
		char1 = kalloc();
		char2 = char1;
		
		for (looper1 = 0; looper1 < 4096; looper1++) {
			*char2++ = 0;
			}
		while (int1 > 0){
			filewrite(f, char1, int1);
			int1-= 4096;
		}
		kfree(char1);
	}
	f->off = bufffer_new;
	return 0;
}
