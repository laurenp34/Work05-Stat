#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


int main() {
  int status;
  struct stat * fileinfo = malloc(sizeof(struct stat));
  status = stat("crinkel", fileinfo);

  if (status==-1) printf("Errno %d: %s\n", status, strerror(status));

  printf("File: crinkel\n");
  printf("File size: %ld bytes\n", fileinfo->st_size);
  printf("File permissions: %o\n", fileinfo->st_mode);
  printf("Time of last access: %s", ctime(&(fileinfo->st_atime)));
  printf("Time of last modification: %s", ctime(&(fileinfo->st_mtime)));

  return 0;
}
