#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "util.h"

#define TARGET 1
#define COMMAND 2


maketree make406;

void generate_parsingtree(target_t *node, pid_t*);
//This function will parse makefile input from user or default makeFile.
int parse(char * lpszFileName)
{
	int nLine=0;
	char szLine[1024];
	char * lpszLine;
	FILE * fp = file_open(lpszFileName);

	if(fp == NULL)
	{
		return -1;
	}

	/* This is not a simple initializer but an executable code */
	make406.current_id = 0;

	while(file_getline(szLine, fp) != NULL)
	{
		nLine++;
		// this loop will go through the given file, one line at a time
		// this is where you need to do the work of interpreting
		// each line of the file to be able to deal with it later

		//Remove newline character at end if there is one
		lpszLine = strtok(szLine, "\n");

		//Skip if blank or comment.
		if(szLine[0] == '#' || szLine[0] == '\n')
			continue;

		char **argvadr;
	       	int ntokens = makeargv(lpszLine, " ", &argvadr);
		//Remove leading whitespace.
		//Skip if whitespace-only.
		if(ntokens <= 0)
			continue;

		int curr = -1; /* Indicates the current line status */
		if(argvadr[0][strlen(argvadr[0]) - 1] != ':')  {
			fprintf(stderr, "%d line should be target", nLine);
			return -1;
		}
		curr = TARGET; /* We are right now in a target line */

		/* Initialize a node in the MakeTree*/
		target_t *node = malloc(sizeof(target_t));
		make406.nodelist[make406.current_id++] = node;

		/* TODO: push this node's target field. */
		strncpy(node->szTarget, argvadr[0], strlen(argvadr[0])-1);
		node->nDependencyCount = ntokens-1;
		int i;
		for(i=0; i<ntokens-1; ++i)
			strcpy(node->szDependencies[i], argvadr[i+1]);

		if(file_getline(szLine, fp) == NULL)  {
			fprintf(stderr, "%d line is missing", nLine);
			return -1;
		}
		nLine++;
		lpszLine = strtok(szLine, "\n");
		if((lpszLine[0] != '\t'))  {
			fprintf(stderr, "%d line should be command", nLine);
			return -1;
		}
		curr = COMMAND; /* We are currently in a command line */
		strcpy(node->szCommand, lpszLine);

		for(i = 0; i < ntokens; ++i)  {
			printf("\t%d\t%d\t%d\t%s\n", nLine, curr, ntokens, argvadr[i]);
		}

		//Only single command is allowed.
		//If you found any syntax error, stop parsing.
	}

	// Close the makefile.
	fclose(fp);

	// Printing out the nodes here.
	int i,j;
	i = 0;
	for( ; i<make406.current_id; ++i)  {
		printf("%s\n", make406.nodelist[i]->szTarget);
		j = 0;
		printf("no_dependencies: %d\n", make406.nodelist[i]->nDependencyCount);
		for( ; j < make406.nodelist[i]->nDependencyCount; ++j)
			printf("\t%s\n", make406.nodelist[i]->szDependencies[j]);
	}
	pid_t main_child_pid;
	int status = 0;
	generate_parsingtree(make406.nodelist[0], &main_child_pid);
	main_child_pid = waitpid(main_child_pid, &status, 0);
	return 0;
}

target_t *find_target(char *tarname)  {
	int i = 0;
	for( ; i < make406.current_id; ++i)
		if(strcmp(make406.nodelist[i]->szTarget, tarname) == 0)
			return make406.nodelist[i];
	return NULL;
}

void generate_parsingtree(target_t *node, pid_t *child_pid)
{
	if(node == NULL)
		return;
	int ndep = 0;
	pid_t cpid[node->nDependencyCount];
	int status[node->nDependencyCount];
	memset(status, 0, node->nDependencyCount);

	while(ndep < node->nDependencyCount)  {
		generate_parsingtree(find_target(node->szDependencies[ndep]), cpid+ndep);
		ndep++;
	}
	// Wait for all the children to execute
	ndep=0;
	while(ndep < node->nDependencyCount)  {
		cpid[ndep] = waitpid( cpid[ndep], status+ndep, 0);
		ndep++;
	}

	// Execute the code if the dependencies are modified;
	ndep=0; int virginity = 1;
	while(ndep < node->nDependencyCount)  {
		int temp = compare_modification_time(node->szTarget, node->szDependencies[ndep]);
		if(temp!=1)
			virginity = -1;
		ndep++;
	}
	if(virginity ==-1)  { /* virginity is lost.  */
		*child_pid = fork();
		if(*child_pid==0)  {
			system(node->szCommand);
			printf("\n%s\t%d", node->szCommand, getpid());
			exit(0);
		}	
	}
	else  { /* virginity is maintained.  */
		printf("\n no need of %s", node->szCommand);
	}
}

void show_error_message(char * lpszFileName)
{
	fprintf(stderr, "Usage: %s [options] [target] : only single target is allowed.\n", lpszFileName);
	fprintf(stderr, "-f FILE\t\tRead FILE as a maumfile.\n");
	fprintf(stderr, "-h\t\tPrint this message and exit.\n");
	fprintf(stderr, "-n\t\tDon't actually execute commands, just print them.\n");
	fprintf(stderr, "-B\t\tDon't check files timestamps.\n");
	fprintf(stderr, "-m FILE\t\tRedirect the output to the file specified .\n");
	exit(0);
}

int main(int argc, char **argv)  {
	parse(argv[1]);
}

int mains(int argc, char **argv)
{
	// Declarations for getopt
	extern int optind;
	extern char * optarg;
	int ch;
	char * format = "f:hnBm:";

	// Default makefile name will be Makefile
	char szMakefile[64] = "Makefile";
	char szTarget[64];
	char szLog[64];

	while((ch = getopt(argc, argv, format)) != -1)
	{
		switch(ch)
		{
			case 'f':
				strcpy(szMakefile, strdup(optarg));
				break;
			case 'n':
				break;
			case 'B':
				break;
			case 'm':
				strcpy(szLog, strdup(optarg));
				break;
			case 'h':
			default:
				show_error_message(argv[0]);
				exit(1);
		}
	}

	argc -= optind;
	argv += optind;

	// at this point, what is left in argv is the targets that were
	// specified on the command line. argc has the number of them.
	// If getopt is still really confusing,
	// try printing out what's in argv right here, then just running
	// with various command-line arguments.

	if(argc > 1)
	{
		show_error_message(argv[0]);
		return EXIT_FAILURE;
	}

	//You may start your program by setting the target that make406 should build.
	//if target is not set, set it to default (first target from makefile)
	if(argc == 1)
	{
	}
	else
	{
	}


	/* Parse graph file or die */
	if((parse(szMakefile)) == -1)
	{
		return EXIT_FAILURE;
	}

	//after parsing the file, you'll want to check all dependencies (whether they are available targets or files)
	//then execute all of the targets that were specified on the command line, along with their dependencies, etc.
	return EXIT_SUCCESS;
}
