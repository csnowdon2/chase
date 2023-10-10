all:
	g++ chase.cpp -o chase

run: all
	./chase 1024 | python3 plot.py
