TARGET=main.o
CXX=c++
OBJS=src/main.cpp

main:$(OBJS)
	g++ -o $(TARGET) -Wall -lglut -lGL -lGLU -lIrrKlang $(OBJS)

clean:
	rm -rf *.o
