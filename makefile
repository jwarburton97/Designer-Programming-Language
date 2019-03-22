OBJS= lexeme.o lexer.o type.o parser.o environment.o evaluator.o pp.o
CFLAGS=-D uuDebug
CFLAGS=
export CFLAGS
evaluate: $(OBJS)
	gcc -Wall -g $(OBJS) -D uuDebug -std=c99 -o evaluate



lexeme.o: lexeme.c type.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c lexeme.c

lexer.o: lexer.c lexeme.c type.c parser.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c lexer.c

type.o: type.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c type.c

parser.o: parser.c evaluator.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c parser.c

pp.o: pp.c parser.c lexeme.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c pp.c



environment.o: environment.c lexeme.c
	gcc -Wall -g $(CFLAGS) -std=c99 -c environment.c

evaluator.o: evaluator.c lexeme.c type.c environment.c parser.c 
	gcc -Wall -g $(CFLAGS) -std=c99 -c evaluator.c

run: run
	
	

clean:
	rm -f ./*.o 

error1:
	cat error1.lusth

error1x:
	./evaluate error1.lusth

error2:
	cat error2.lusth

error2x:
	./evaluate error2.lusth

error3:
	cat error3.lusth

error3x:
	./evaluate error3.lusth

error4:
	cat error4.lusth

error4x:
	./evaluate error4.lusth

error5:
	cat error5.lusth

error5x:
	./evaluate error5.lusth
	
arrays:
	cat arrays.lusth

arraysx:
	./evaluate arrays.lusth

conditionals:
	cat conditionals.lusth

conditionalsx:
	./evaluate conditionals.lusth

recursion:
	cat recursion.lusth

recursionx:
	./evaluate recursion.lusth

iteration:
	cat iteration.lusth

iterationx:
	./evaluate iteration.lusth

functions:
	cat functions.lusth

functionsx:
	./evaluate functions.lusth

lamda:
	cat lamda.lusth

lamdax:
	./evaluate lamda.lusth

problem:
	cat problem.lusth

problemx:
	./evaluate problem.lusth

objects:
	cat objects.lusth

objectsx:
	./evaluate objects.lusth
	


