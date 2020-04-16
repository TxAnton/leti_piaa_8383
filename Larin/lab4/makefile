all: ./src.cpp
	g++ ./src.cpp -o lab4
test: all test.py lab4
	python test.py lab4 Tests test answer result 4
clean:
	rm -f lab4
