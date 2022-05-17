.PHONY: bpf

bpf:
	clang -O2 -target bpf -c bpf-program.c  -o bpf-program.o

loader:
	clang -lelf -lbpf \
	-I /kernel-src/tools/testing/selftests/bpf \
	-L /usr/local/lib64 \
	/kernel-src/tools/testing/selftests/bpf/trace_helpers.c loader.c \
	-o bpf-loader 


