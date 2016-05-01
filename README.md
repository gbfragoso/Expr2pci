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
* Although the pushdown automata give us the set of productions we need to add them manually to nodes.
* Possible bug on bad organizated btree

# Compiling
gcc -o teste pcode.c rpn2pci.c btree2rpn.c pushdown.c main.c

# Running
./teste "expression"

# Example
```
./teste "((1-2)*1)"
List of productions to build the expr ((1-2)*1) without '(' ')': 
4 4 0 6 1 7 0 
Please apply productions to nodes. (Leftmost First)
E _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 0
A E E _ _ _ _ _ _ 
Apply production E -> EAE in node: 1
A A E E E _ _ _ _ 
Apply production E -> 1 in node: 3
A A E 1 E _ _ _ _ 
Apply production A -> - in node: 1
A - E 1 E _ _ _ _ 
Apply production E -> 2 in node: 4
A - E 1 2 _ _ _ _ 
Apply production A -> * in node: 0
* - E 1 2 _ _ _ _ 
Apply production E -> 1 in node: 2
* - 1 1 2 _ _ _ _ 
Done! Output file generated
```
(See output.txt for automata and pcode execution)
