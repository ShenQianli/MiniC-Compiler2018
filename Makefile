#! /bin/bash
all : eeyore tigger riscv64
OBJ1 = src/eeyore/main.o src/eeyore/eeyore.o src/eeyore/mystack.o src/eeyore/mytree.o src/eeyore/y.tab.o src/eeyore/lex.yy.o
eeyore : $(OBJ1)
	gcc $^ -o eeyore
OBJ2 = src/tigger/main.o src/tigger/tigger.o src/tigger/mytree.o src/tigger/LSRA.o src/tigger/optimize.o src/tigger/y.tab.o src/tigger/lex.yy.o
tigger : $(OBJ2)
	gcc $^ -o tigger
OBJ = src/riscv64/main.o src/riscv64/riscv64.o src/riscv64/mytree.o src/riscv64/optimize.o src/riscv64/y.tab.o src/riscv64/lex.yy.o
riscv64 : $(OBJ)
	gcc $^ -o riscv64
clean :
	rm -rf eeyore tigger riscv64 src/eeyore/*.o src/tigger/*.o src/riscv64/*.o
