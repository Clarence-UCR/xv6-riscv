#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_PROC 10

struct pinfo {
    int ppid;
    int syscall_count;
    int page_usage;
};

void print_sysinfo(void) {
    int n_active_proc, n_syscalls, n_free_pages;
    n_active_proc = info(0);
    n_syscalls = info(1);
    n_free_pages = info(2);
    printf("[sysinfo] active proc: %d, syscalls: %d, free pages: %d\n",
           n_active_proc, n_syscalls, n_free_pages);
}

int main(int argc, char *argv[]) {
    int mem, n_proc;
    if (argc < 3) {
        printf("Usage: %s [MEM] [N_PROC]\n", argv[0]);
        exit(-1);
    }

    print_sysinfo();

    mem = atoi(argv[1]);
    printf("[User operation] use %d bytes memory \n", mem);
    malloc(mem);
    n_proc = atoi(argv[2]);

    if (n_proc > MAX_PROC) {
        printf("Cannot test with more than %d processes\n", MAX_PROC);
        exit(-1);
    }

    print_sysinfo();

    printf("[User operation] activating process\n");

    for (int i = 0; i < n_proc; i++) {
      sleep(1);
      int pid;

      pid = fork();
      //printf("pid %d \n", pid);

      if (pid == 0) {
        //printf("Child process\n");
        malloc(mem);
        while(1);
      } else if (pid > 0) {
        //printf("Parent process\n");
      } else {
        printf("Fork error\n");
      }

    }

    sleep(1);
    print_sysinfo();

    exit(0);
}
