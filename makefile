all: StackMain.o Stack.o
	g++ StackMain.o Stack.o -o S.exe

StackMain.o: StackMain.cpp
	g++ StackMain.cpp -c

Stack.o: Stack.cpp
	g++ Stack.cpp -c

clean:
	@echo "Clean Stack project"
	rm -f Stack.o StackMain.o S.exe
	@echo "Clean complited"	