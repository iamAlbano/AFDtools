
all: tools/struct/afd.o tools/view/view.o 
	gcc tools/struct/afd.o tools/view/view.o afdtool.c -o afdtool

construct.o: tools/struct/afd.h
	gcc -c tools/struct/afd.c

view.o: tools/view/view.h
	gcc -c tools/view/view.c

clean:
	rm -rf *.o tools/*/*.o afdtool
