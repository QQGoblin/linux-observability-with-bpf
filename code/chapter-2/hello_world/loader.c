#include "bpf_load.h"
#include <stdio.h>
#include "trace_helpers.h"

int main(int argc, char **argv) {

  // load_bpf_file 函数定义在 bpf_load.h 中， 5.10 以上版本的内核移除了上述文件。我们可以将该 bpf_load.h/bpf_loader.c 复制到当前目录。
  if (load_bpf_file("bpf_program.o") != 0) {
    printf("The kernel didn't load the BPF program\n");
    return -1;
  }



  read_trace_pipe();

  return 0;
}
