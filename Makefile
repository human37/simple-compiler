NAME = compiler

run: compiler
	./$(NAME).exe

compiler:
	g++ *.cpp -ggdb -fno-stack-protector -std=c++17 -o $(NAME).exe -z execstack

clean:
	rm *.o *.exe