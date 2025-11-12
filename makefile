parametrosCompilacao=-Wall #-Wshadow
nomePrograma=prova4_20246230

all: $(nomePrograma)

$(nomePrograma): main.o kdTree.o
	gcc -o $(nomePrograma) main.o kdTree.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: kdTree.h kdTree.c
	gcc -c kdTree.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)