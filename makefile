all:
	rm datos.dat
	g++ -std=c++17  Menu.cpp -o Menu
	./Menu