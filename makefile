mesh: main.cpp mesh.o
	g++ -std=c++11 main.cpp mesh.cpp -liup -liupgl -framework OpenGL -framework GLUT -o mesh