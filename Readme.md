There is another implementation here: http://homepage.usask.ca/~xil358/fork-fun.c
I just wrote my own! :)

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
