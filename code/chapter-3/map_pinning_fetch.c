#include <errno.h>
#include <linux/bpf.h>
#include <stdio.h>
#include <string.h>
#include <bpf/bpf.h>

static const char *file_path = "/sys/fs/bpf/my_array";

int main(int argc, char **argv) {
  int fd, key, value, result;

  // 读取字典的文件句柄
  fd = bpf_obj_get(file_path);
  if (fd < 0) {
    printf("Failed to fetch the map: %d (%s)\n", fd, strerror(errno));
    return -1;
  }

  // 查询
  key = 1;
  result = bpf_map_lookup_elem(fd, &key, &value);
  if (result < 0) {
    printf("Failed to read value from the map: %d (%s)\n", result,
           strerror(errno));
    return -1;
  }

  printf("Value read from the map: '%d'\n", value);
  return 0;
}
