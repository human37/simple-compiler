NAME = compiler

CXXFLAGS=-Wall -Werror -fno-stack-protector -D_FORTIFY_SOURCE=0

run: compiler
	./$(NAME).exe

compiler:
  g++-9 *.cpp -o $(NAME).exe -z execstack

clean:
	rm *.o *.exe
