TARGET=main.o
CXX=c++
OBJS=main.cpp

main:$(OBJS)
	g++ -o $(TARGET) -Wall -lglut -lGL -lGLU $(OBJS)

clean:
	rm -rf *.o
