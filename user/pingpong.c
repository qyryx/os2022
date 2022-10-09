#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    fprintf(2, "pingpong usage: pingpong\n");
    exit(1);
  }

  int to_child[2];
  int to_parent[2];

  pipe(to_child);
  pipe(to_parent);

  int pid = fork();

  if (pid == 0) {
    // child
    char received;
    read(to_child[0], &received, 1);
    printf("%d: received ping\n", getpid());
    write(to_parent[1], "x", 1);
  } else if (pid > 0) {
    // parent
    write(to_child[1], "x", 1);
    char received;
    read(to_parent[0], &received, 1);
    printf("%d: received ping\n", getpid());
  }
  exit(0);
}