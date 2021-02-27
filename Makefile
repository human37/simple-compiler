NAME = compiler

run: compiler
	./$(NAME).exe

compiler:
	g++ *.cpp -std=c++11 -o $(NAME).exe

clean:
	rm *.o *.exe