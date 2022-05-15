#include <errno.h>
#include <linux/bpf.h>
#include <stdio.h>
#include <string.h>
#include <bpf/bpf_helper_defs.h>
#include <bpf/bpf.h>

static const char *file_path = "/sys/fs/bpf/my_array";

int main(int argc, char **argv) {
  int key, value, fd, added, pinned;

  // 创建 BPF_MAP_TYPE_ARRAY 类型的字典
  fd = bpf_create_map(BPF_MAP_TYPE_ARRAY, sizeof(int), sizeof(int), 100, 0);
  if (fd < 0) {
    printf("Failed to create map: %d (%s)\n", fd, strerror(errno));
    return -1;
  }

  // 写入数据
  key = 1, value = 1234;
  added = bpf_map_update_elem(fd, &key, &value, BPF_ANY);
  if (added < 0) {
    printf("Failed to update map: %d (%s)\n", added, strerror(errno));
    return -1;
  }

  // 绑定到指定路径，提供给用户空间程序查询
  pinned = bpf_obj_pin(fd, file_path);
  if (pinned < 0) {
    printf("Failed to pin map to the file system: %d (%s)\n", pinned,
           strerror(errno));
    return -1;
  }

  return 0;
}
