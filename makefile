DEP=colors.h game.h othello.h piece.h
OBJ=othello.cc game.cc main.cc

all:build archive

build:game

game: othello.o game.o main.o
	g++ -o $@ $^

game.o: game.cc $(DEP)
	g++ -c game.cc

main.o: main.cc $(DEP)
	g++ -c main.cc

othello.o: othello.cc $(DEP)
	g++ -c othello.cc

clean:
	rm -f *.o core *.core game Othello.tar.gz

archive: $(DEP) $(OBJ) makefile
	tar cvzf Othello.tar.gz $^
