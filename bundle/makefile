output: Item.o driver.o Algo.o Node.o
	g++ Item.o driver.o Algo.o Node.o -o output

Item.o: Item.cpp
	g++ -c Item.cpp

Algo.o: Algo.cpp
	g++ -c Algo.cpp

Node.o: Node.cpp
	g++ -c Node.cpp

driver.o: driver.cpp
	g++ -c driver.cpp

clean:
	rm *.o output
