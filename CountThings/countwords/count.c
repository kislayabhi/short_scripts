#include<stdio.h>
#include<stdbool.h>

#define IN 0
#define OUT 1
#define MAX_WORD_LENGTH 50

/* Make a histogram of word lengths. */

int main(int argc, char** argv)
{
	int c, nwords, ncurr, state;	
	int wordcount[MAX_WORD_LENGTH];
	FILE *fp;

	nwords = ncurr = 0;
	state = OUT;
	for(int i = 0; i < MAX_WORD_LENGTH; ++i)
		wordcount[i] = 0;
	if(argc > 1)
		fp = fopen(argv[1], "r");
	else
		fp = fopen("count.c", "r");	

	while((c = getc(fp)) != EOF) {
		if(c == ' ' || c == '\t' || c == '\n')
			state = OUT;
		else if(state == OUT) {
			state = IN;
			++nwords;
			++wordcount[ncurr];
			ncurr = 1;
		}
		else
			++ncurr;
	}

	printf("\ntotal no. of words: %d", nwords);
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
