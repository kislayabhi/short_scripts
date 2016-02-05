/*

What the program does:

   This program is called forkfun.c. When M is started, it checks its own process
id number. If the process id number is even, then M creates two child processes
(called a1 and b1). If the process id number is odd, then M creates three child
processes (called a1, b1, and c1).

 In either case, the child processes created
should behave as follows: if the process id number of the child process is even,
it should exec the fork2.c program, else it should exec the fork3.c program.
Process M should do some form of wait to see which of its child proceses
terminates first, report a message to this effect, and so on, until it finds
that its last child process has terminated, at which point it reports a message
to this effect. Process M then says "Goodbye!" and exits.

How to use it

    1.compile gcc -o forkfun forkfun.c
    2.type forkfun following the command prompt
*/

#include<stdio.h>  // standard i/o
#include<unistd.h> // for exec family
#include<sys/wait.h>
int main()
{
    int current_pid = getpid();
    printf("Main PID: %d \n", current_pid);
    // If the current process id is even, we create 2 child processes.
    if(current_pid%2==0)
    {
        int a1 = fork();
        if(a1==0) // Child a1 only allowed.
        {
            // exec fork2 if getpid() is even else exec fork3.
            printf("The child a1_even is here! \n");

            ((getpid()%2)==0)
                ?execl("fork2", "fork2", (char*)0)
                :execl("fork1", "fork1", (char*)0);
        }

        if(a1>0) // Parent only!
        {
            printf("a1: %d \n",a1);
            int b1 = fork();
            // exec fork2 if getpid() is even else exec fork3.
            if(b1==0) // Child b1 only allowed.
            {
                // exec fork2 if getpid() is even else exec fork3.
                printf("The child b1_even is here! \n");
                ((getpid()%2)==0)
                    ?execl("fork2", "fork2", (char*)0)
                    :execl("fork1", "fork1", (char*)0);
            }
            else
            {
                printf("b1: %d \n",b1);
                // The parent should wait now.
                pid_t latest_exit;
                int count=2;
                while(1)
                {
                    latest_exit=wait(NULL);
                    if(latest_exit>0)
                    {
                        printf("\n EXIT: %d \n",latest_exit);
                        count--;
                        if(count==0){printf("GOODBYE");    break;}
                    }
                }
            }
        }
    }
    else
    {
      int a1 = fork();
      if(a1==0) // Child a1 only allowed.
      {
          // exec fork2 if getpid() is even else exec fork3.
          printf("The child a1_odd is here! \n");
          ((getpid()%2)==0)
              ?execl("fork2", "fork2", (char*)0)
              :execl("fork1", "fork1", (char*)0);
      }

      if(a1>0) // Parent only!
      {
          int b1 = fork();
          // exec fork2 if getpid() is even else exec fork3.
          if(b1==0) // Child b1 only allowed.
          {
              // exec fork2 if getpid() is even else exec fork3.
              printf("The child b1_odd is here! \n");
              ((getpid()%2)==0)
                  ?execl("fork2", "fork2", (char*)0)
                  :execl("fork1", "fork1", (char*)0);
          }

          if(b1>0) // Parent only!
          {
              int c1 = fork();
              // exec fork2 if getpid() is even else exec fork3.
              if(c1==0) // Child c1 only allowed.
              {
                  // exec fork2 if getpid() is even else exec fork3.
                  printf("The child c1_odd is here! \n");
                  ((getpid()%2)==0)
                      ?execl("fork2", "fork2", (char*)0)
                      :execl("fork1", "fork1", (char*)0);
              }

              if(c1>0)
              {
                 // The parent should wait now.
                 pid_t  latest_exit;
                 int count=3;
                 while(1)
                 {
                     latest_exit=wait(NULL);
                     if(latest_exit>0)
                     {
                         printf("EXIT: %d \n",latest_exit);
                         count--;
                         if(count==0){printf("GOODBYE");    break;}
                     }
                 }
             }
          }
      }
    }
}
