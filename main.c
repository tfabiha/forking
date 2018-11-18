#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
  int info;
  int child;
  int fd = open("/dev/random", O_RDONLY);

  //print initial statement
  printf("Parent pid: %d\n\n", getpid());

  //create two child processes
  int f = fork();
  if (f)
    f = fork();

  if (f)
    child = wait(&info);
  else
  {
    unsigned int rand_num;
    int read_bytes = read(fd, &rand_num, sizeof(int));
    close(fd);

    printf("Child pid: %d\n", getpid());

    int sleeptime = rand_num % 16 + 5;
    sleep(sleeptime);
    printf("I %d have slept for %d\n", getpid(), sleeptime);
    return sleeptime;
  }

  if (f)
  {
    int slept = WEXITSTATUS(info);
    printf("\nMy child was: %d Slept: %d seconds\n", child, slept);
  }

  return 0;
}
