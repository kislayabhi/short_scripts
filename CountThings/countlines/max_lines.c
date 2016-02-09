#include<stdio.h>
#include<stdlib.h>

#define MAXLINELEN 1500

int get_line(FILE *fp, char curr_array[]);
void save(char src[], char dest[], int length);

/* Print longest input line */
int main()
{
	int maxline_len, currline_len;
	char curr_line[MAXLINELEN]; /* Stores the current line */
	char max_line[MAXLINELEN];  /* Stores the longest line */
	FILE *fp = fopen("max_lines.c", "r");

	maxline_len = currline_len = 0;
	while ((currline_len = get_line(fp, curr_line)) > 0)
		if (currline_len > maxline_len) {
			maxline_len = currline_len;
			save(curr_line, max_line, maxline_len);
		}
	if (maxline_len > 0) /* there was a line above */
		printf("%s", max_line);
	printf("\n");
	free(fp);
	return 0;
}

/* copy: copy the array from source to destination */
void save(char src[], char dest[], int length) {
	for(int i = 0; i < length; ++i)
		dest[i] = src[i];
}

/* get_line: read a line into curr_array, return length */
int get_line(FILE *fp, char curr_array[]) {
	char c;
	int line_len;

	for(line_len=0; ((c=getc(fp))!='\n') && (c!=EOF); ++line_len)
		curr_array[line_len] = c;
	if(c == '\n') {
		curr_array[line_len] = c;
		++line_len;
	}	
	return line_len;
}
