all: clean compile link 
# ecleanObjAndrun



compile:
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/Action.o src/Action.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/Customer.o src/Customer.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/Order.o src/Order.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/Parser.o src/Parser.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/Volunteer.o src/Volunteer.cpp
	g++ -std=c++11 -g -Wall -Weffc++ -c -o bin/WareHouse.o src/WareHouse.cpp


link:
	g++ -std=c++11 -g -Wall -Weffc++ -o bin/warehouse bin/*.o



	
clean:
	rm -f bin/*

# cleanObjAndrun:
# 	rm -f *.o
# 	clear 
# 	valgrind --leak-check=full --show-reachable=yes ./bin/warehouse
