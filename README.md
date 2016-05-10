# Expr2pci
An translator that aims to convert balanced expressions in pcode instructions.

# Grammar
Grammar for arithmetic expressions (Greibach) 
* E -> 1 (P0)
* E -> 2 (P1)
* E -> x (P2)
* E -> y (P3)
* E -> (EAEB (P4)
* A -> + (P5)
* A -> - (P6)
* A -> * (P7)
* A -> / (P8)
* B -> ) (P9)

# Limitations
* This machine inherits the limitations of grammar
* X/Y variables dont receive values

# Compiling
gcc -o teste ada2asa.c pcode.c rpn2pci.c btree2rpn.c pushdown.c main.c

# Running
./teste "expression"

# Example
See output.txt for automata and pcode execution
