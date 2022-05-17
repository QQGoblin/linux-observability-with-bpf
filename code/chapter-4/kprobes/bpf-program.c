#include <linux/bpf.h>
# include<bpf/bpf_helper_defs.h>
# define SEC(NAME) __attribute__((section(NAME), used))

/**
 * 关于 tracepoint 的概念：
 * 
 */

SEC("tracepoint/syscalls/sys_enter_execve")
int do_sys_execve(struct pt_regs *ctx)
{
    char comm[16];
    bpf_get_current_comm(&comm,sizeof(comm));
    const char msg[]= "executing program: %s";
    bpf_trace_printk(msg,sizeof(msg),comm);
    return 0;
}

char _license[] SEC("license") = "GPL";