parametrosCompilacao=-Wall -g #-Wshadow
nomePrograma=prova4_20246230
all: $(nomePrograma)

$(nomePrograma): main.o kdTree.o fprio.o
	gcc -o $(nomePrograma) main.o kdTree.o fprio.o $(parametrosCompilacao) -lm

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

kdTree.o: kdTree.c kdTree.h
	gcc -c kdTree.c $(parametrosCompilacao)

fprio.o: fprio.c fprio.h
	gcc -c fprio.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
	

gdb: $(nomePrograma)
	gdb ./$(nomePrograma)

