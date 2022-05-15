#include <linux/bpf.h>
#define SEC(NAME) __attribute__((section(NAME), used))

/**
 * BPF_FUNC_trace_printk/BPF_FUNC_get_current_pid_tgid 是 linux/bpf.h 中，通过宏定义的 bpf 辅助函数 ID
 * 
 * 展开后，bpf_trace_printk的定义等价于：
 * 
 *    static long (*bpf_trace_printk)(const char *fmt, __u32 fmt_size, ...) = (void *) 6;  # void * 表示无类型指针
 * 
 * 在 bpf_helper_defs.h 中包含所有 bpf 辅助函数的定义，可以直接引用这个头文件从而省略这些定义。
 * 
 * 辅助函数的文档说明，可以参考：https://man7.org/linux/man-pages/man7/bpf-helpers.7.html
 * 
 */
static long (*bpf_trace_printk)(const char *fmt, int fmt_size,...) = (void *)BPF_FUNC_trace_printk;
static __u64 (*bpf_get_current_pid_tgid)(void) = (void *)BPF_FUNC_get_current_pid_tgid;


SEC("tracepoint/syscalls/sys_enter_execve")
int bpf_prog_hello_world(void *ctx) {

  int pid = bpf_get_current_pid_tgid() >> 32;
  const char msg[] = "Hello, BPF World! My PID is %d\n";
  // 该函数将输出打印到 /sys/kernel/debug/tracing/trace_pipe 
  bpf_trace_printk(msg, sizeof(msg),pid);
  return 0;

}

char _license[] SEC("license") = "GPL";
