#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

void printPermissions(mode_t perm);

int main() {
  int status;
  struct stat * fileinfo = malloc(sizeof(struct stat));
  status = stat("crinkel", fileinfo);

  //for purpose of testing printPermissions
  int op = open("test",O_CREAT,0644); //for some reason O_RDWR gave permission denied
  if (op == -1) printf("Errno %d: %s\n", errno, strerror(errno));
  int st2;
  struct stat * fi2 = malloc(sizeof(struct stat));
  st2 = stat("test", fi2);
  close(op);

  //only look at last 9 bytes (3 octal digits) of st_mode
  fileinfo->st_mode = fileinfo->st_mode % 01000;

  if (status==-1) printf("Errno %d: %s\n", status, strerror(status));

  printf("File: crinkel\n");
  printf("File size: %ld bytes\n", fileinfo->st_size);
  printf("File permissions in octal: %o\n", fileinfo->st_mode);
  printf("File permissions in ls -l form: ");
  printPermissions(fileinfo->st_mode);
  printf("Time of last access: %s", ctime(&(fileinfo->st_atime)));
  printf("Time of last modification: %s", ctime(&(fileinfo->st_mtime)));

  printf("\nTesting printPermissions function:\n");
  printf("permissions of test file: ");
  printPermissions(fi2->st_mode % 01000);
  //i'm not sure why printpermissions doesn't work here...

  free(fileinfo);
  free(fi2);

  return 0;
}

void printPermissions(mode_t perm) {
  //modify perm directly b/c not a pointer
  int i;
  //for each of 9 bits
  for (i=0;i<9;i++) {
    //if last bit is 0
    if (perm / 2^(i-1) == 1) {
      if (i==0 | i==3 | i==6) printf("r");
      else if (i==1 | i==4 | i==7) printf("w");
      else printf("x");
    }
    else printf("-");
    //remove first digit
    perm = perm % (perm / 2^(i-1));
  }
  printf("\n");
}
