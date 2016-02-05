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
