default: all

all: array\
	union\
	struct\
	mealy

array: array_example.c
	gcc array_example.c -o array_example.exe -std=c18 -Wall -pedantic	
	
union: union_example.c
	gcc union_example.c print_mem.c -o union_example.exe -std=c18 -Wall -pedantic -DCOLORED_CONSOLE=1

struct: struct_example.c
	gcc struct_example.c -o struct_example.exe -std=c18 -Wall -pedantic

mealy: mealy_machine_example.c
	gcc mealy_machine_example.c -o mealy_machine_example.exe -std=c18 -Wall -pedantic
	
clean: 
	rm -f array_example.exe
	rm -f union_example.exe
	rm -f struct_example.exe
	rm -f mealy_machine_example.exe