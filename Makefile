
# Comandos para compilar os arquivos
all: tools/struct/afd.o tools/view/view.o tools/complement/complement.o tools/union/union.o tools/recognize/recognize.o afdtool.c
	gcc tools/struct/afd.o tools/view/view.o tools/complement/complement.o tools/union/union.o tools/recognize/recognize.o afdtool.c -o afdtool

construct.o: tools/struct/afd.h
	gcc -c tools/struct/afd.c

view.o: tools/view/view.h
	gcc -c tools/view/view.c

complement.o: tools/complement/complement.h
	gcc -c tools/complement/complement.c

union.o: tools/union/union.h
	gcc -c tools/union/union.c

recognize.o: tools/recognize/recognize.h
	gcc -c tools/recognize/recognize.c

# Comandos criados para facilitar a execução do programa:
clean:
	rm -rf *.o tools/*/*.o afdtool

getGraph:
	dot -Tpdf afd.dot > afd.pdf

# Executar o programa com a funcionalidade de exportar o AFD para o formato .dot
view:
	./afdtool --dot ./txt/afd.txt --output afd.dot

# Executar o programa com a funcionalidade de exportar o complemento do AFD para o formato especificado
complement:
	./afdtool --complemento ./txt/afd.txt --output complemento.txt

# Executar o programa com a funcionalidade de união de dois AFDs
union:
	./afdtool --uniao ./txt/afd3.txt ./txt/afd4.txt --output afd.dot

recognize:
	./afdtool --reconhecer ./txt/afd.txt ./txt/palavras.txt --output saida.txt

# Comando para executar o programa (rodar como 'make run')
run:
	make clean
	make
	clear
	make recognize
	make getGraph