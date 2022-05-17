#include <stdio.h>
#include <bpf/libbpf.h>
#include <unistd.h>
#include <trace_helpers.h>


int main(int argc, char *argv[])
{

	if (argc !=3 ){
		fprintf(stderr, "ERROR: args error\n");
		return -1 ;
	}

	struct bpf_link *link = NULL;
	struct bpf_program *prog;
	struct bpf_object *obj;

	char* bpf_obj_filename = argv[1];
	char* prog_name = argv[2];

    // 加载bpf文件
	obj = bpf_object__open_file(bpf_obj_filename, NULL);
	if (libbpf_get_error(obj)) {
		fprintf(stderr, "ERROR: opening BPF object file failed\n");
		return 0;
	}

    // 检查文件是否包含 bpf 程序
	prog = bpf_object__find_program_by_name(obj, prog_name);
	if (!prog) {
		fprintf(stderr, "ERROR: finding a prog in obj file failed\n");
		goto cleanup;
	}

	/* load BPF program */
	if (bpf_object__load(obj)) {
		fprintf(stderr, "ERROR: loading BPF object file failed\n");
		goto cleanup;
	}

	link = bpf_program__attach(prog);
	if (libbpf_get_error(link)) {
		fprintf(stderr, "ERROR: bpf_program__attach failed\n");
		link = NULL;
		goto cleanup;
	}

	read_trace_pipe();

cleanup:
	bpf_link__destroy(link);
	bpf_object__close(obj);
	return 0;
}