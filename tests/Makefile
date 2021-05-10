SRC = ../src

INCLUDE = -I../src
BUILD = ../build
DEFINED = -DUSE_STDLIB
#-DDEBUG
#-DDMEMORY
CFLAGS = ${INCLUDE} ${DEFINED}

all: test_structs

clean:
	rm $(BUILD)/*.o
	rm test_structs

test_structs: test_structs.o o_node.o i_node.o o_graph.o
	echo "Constucting test_structs"
	cc -o test_structs $(BUILD)/test_structs.o $(BUILD)/o_node.o $(BUILD)/i_node.o $(BUILD)/o_graph.o

test_structs.o:
	cc $(CFLAGS) -o $(BUILD)/test_structs.o -c test_structs.c

o_node.o:
	cc $(CFLAGS) -o $(BUILD)/o_node.o -c $(SRC)/o_node.c

i_node.o:
	cc $(CFLAGS) -o $(BUILD)/i_node.o -c $(SRC)/i_node.c

o_graph.o:
	cc $(CFLAGS) -o $(BUILD)/o_graph.o -c $(SRC)/o_graph.c

#test_structs: test_structs.o rs_tree.o rs_avl_tree.o
#	cc -o test_tree $(BUILD)/test_tree.o $(BUILD)/rs_tree.o $(BUILD)/rs_avl_tree.o

#test_structs.o: test_structs.c
#	cc $(CFLAGS) -o $(BUILD)/test_tree.o -c test_tree.c

#rs_tree.o: $(SRC)/rs_tree.c $(SRC)/rs_tree.h
#	cc $(CFLAGS) -o $(BUILD)/rs_tree.o -c $(SRC)/rs_tree.c

#rs_avl_tree.o: $(SRC)/rs_avl_tree.c $(SRC)/rs_avl_tree.h
#	cc $(CFLAGS) -o $(BUILD)/rs_avl_tree.o -c $(SRC)/rs_avl_tree.c


