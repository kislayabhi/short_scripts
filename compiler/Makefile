TARGET = scanner
OBJECT = lex.yy.o symboltable.o hash_table.o
CC = cc -g -std=c99
LEX = flex
LIBS = -lfl

scanner: lex.yy.o symboltable.o hash_table.o
	$(CC) -o scanner lex.yy.o symboltable.o hash_table.o

symboltable.o: symboltable.c
	$(CC) -c symboltable.c

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

hash_table.o: hash_table.c
	$(CC) -c hash_table.c

lex.yy.c: lexer.lex
	$(LEX) $(LIB) lexer.lex

clean:
	rm -f $(TARGET) $(OBJECT) lex.yy.c
