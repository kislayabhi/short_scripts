#include<stdio.h>
#include<stdlib.h> /* Needed for malloc */
#include<string.h>
#define MAXLINE 1000

#define MAX_WORD_LENGTH 50

/* Make a histogram of word length */

int main(int argc, char **argv)
{
	if(argc < 2)  {	
		fprintf(stderr, "File not provided\n");
		exit(EXIT_FAILURE);
	}
	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL)  {
		fprintf(stderr, "File not found\n");\
		exit(EXIT_FAILURE);
	}

	int wordcount[MAX_WORD_LENGTH];
	for(int i= 0; i < MAX_WORD_LENGTH; ++i)
		wordcount[i] = 0;



	char *sentence = malloc(MAXLINE);
	char *dptr = " \t\r\n\v\f";
	while(fgets(sentence, MAXLINE, fp))	
		for(char *result = strtok(sentence, dptr); result; result = strtok(NULL, dptr))
			++wordcount[strlen(result)];
	
	printf("\nno. of words per length:\n");
	for(int i = 1; i < MAX_WORD_LENGTH; ++i) {
		if(wordcount[i]>0) {
			printf("\t%2d count:\t%6d ", i, wordcount[i]);
			for(int j = 0; j < wordcount[i]; ++j) {
				printf("-");
			}
			printf("\n");
		}
	}
}
