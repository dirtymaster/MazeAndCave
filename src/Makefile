FLAGS = g++ -Wall -Wextra -Werror
DATA = "In this application, you can generate beautiful mazes and caves with advanced functions."

all: install test

install:
	cd View && qmake && make && make clean && rm Makefile
	mv View/Maze.app/Contents/MacOS/Maze .
	./Maze

uninstall:
	rm -rf View/Maze.app Maze

reinstall: uninstall
	make install

dist:
	tar cfz Maze.tgz Maze

dvi:
	touch info.dvi
	@(echo $(DATA) >> info.dvi)

compile:
	$(FLAGS) tests.cpp Controller/*.cpp Model/Cave/*.cpp Model/Maze/*.cpp -lgtest -g

test: compile
	./a.out

leaks_check: compile
	CK_FORKS=no leaks -atExit -- ./a.out

clean:
	rm -rf Maze.tgz a.out* View/Maze.app info.dvi Maze build-Maze-Desktop_x86_darwin_generic_mach_o_64bit-Debug
