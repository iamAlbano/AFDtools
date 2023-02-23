
all: tools/struct/afd.o tools/view/view.o 
	gcc tools/struct/afd.o tools/view/view.o afdtool.c -o afdtool

construct.o: tools/struct/afd.h
	gcc -c tools/struct/afd.c

view.o: tools/view/view.h
	gcc -c tools/view/view.c

clean:
	rm -rf *.o tools/*/*.o afdtool

getGraph:
	dot -Tpdf afd.dot > afd.pdf

run:
	make clean
	make
	clear
	./afdtool --dot ./txt/afd.txt --output afd.dot
	make getGraph