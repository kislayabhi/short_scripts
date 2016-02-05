#include<stdio.h>
int main()
{
  // pid stores the process id of the child
  int pid=fork();

  if(pid>0)
    printf("Parent Process PID: %d  \n", getpid());
  else if(pid==0)
    printf("Child Process PID: %d \n", getpid());
  else
    printf("fork() couldn't be done");
}
