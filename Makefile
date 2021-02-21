NAME = compiler

run: compiler
	./$(NAME).exe

compiler:
	g++ *.cpp -o $(NAME).exe

clean:
	rm *.o *.exe