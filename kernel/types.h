typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int  uint32;
typedef unsigned long uint64;

typedef uint64 pde_t;
struct pinfo {
  int ppid;                // parent process ID
  int syscall_count;       // number of syscalls made by this process
  int page_usage;          // number of memory pages used by this process
};

struct lock_t {
  uint locked; 
};
