Sample make file:

```
# **all** is called the **target**
# For **all**, hello and clean are **dependancies**
# For **hello**, the **command** is g++ main.o matrix.o -o mat 

all: hello clean

hello: main.o matrix.o
	g++ main.o matrix.o -o mat

main.o: main.cpp
	g++ -c main.cpp

matrix.o: matrix.cpp
	g++ -c matrix.cpp

clean:
	rm -rf *.o
```
By convention, the file should be named as Makefile

One can issue commands as:
$ make main.o
or 
$ make clean
