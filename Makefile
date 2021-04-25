NAME = compiler

CXXFLAGS=-Wall -Werror -fno-stack-protector -D_FORTIFY_SOURCE=0

interpret: compiler
	./$(NAME).exe -i INPUT.c

compile: compiler
	./$(NAME).exe -c INPUT.c

debug:
	g++-9 *.cpp -g -o $(NAME).exe -z execstack

compiler:
	g++-9 *.cpp -o $(NAME).exe -z execstack

clean:
	rm *.o *.exe