CFLAGS = -O2

all: hda

objects = main.o graph.o hda_attack.o robust.o simple_assign.o simple_recover.o sort_assign.o tdr_recover.o dump.o

$(objects): graph.h 

hda: $(objects)
	cc $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(objects) hda
