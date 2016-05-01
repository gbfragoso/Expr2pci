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
* Possible bug on bad organizated btree (Example)

# Compiling
gcc -o teste pcode.c rpn2pci.c btree2rpn.c pushdown.c main.c

# Running
./teste "expression"

# Example
```
./teste "((1*(1-2))+((2*1)/2))"
List of productions to build the expr ((1*(1-2))+((2*1)/2)) without '(' ')': 
4 4 0 7 4 0 6 1 5 4 4 1 7 0 8 1 
Please apply productions to nodes. (Leftmost First)
E _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 0
A E E _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 1
A A E E E _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> 1 in node: 3
A A E 1 E _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production A -> * in node: 1
A * E 1 E _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 4
A * E 1 A _ _ _ _ E E _ _ _ _ _ _ _ _ _ _ 
Apply production E -> 1 in node: 9 
A * E 1 A _ _ _ _ 1 E _ _ _ _ _ _ _ _ _ _ 
Apply production A -> - in node: 4
A * E 1 - _ _ _ _ 1 E _ _ _ _ _ _ _ _ _ _ 
Apply production E -> 2 in node: 10
A * E 1 - _ _ _ _ 1 2 _ _ _ _ _ _ _ _ _ _ 
Apply production A -> + in node: 0
+ * E 1 - _ _ _ _ 1 2 _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 2
+ * A 1 - E E _ _ 1 2 _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 5
+ * A 1 - A E _ _ 1 2 E E _ _ _ _ _ _ _ _ 
Apply production E -> 2 in node: 11
+ * A 1 - A E _ _ 1 2 2 E _ _ _ _ _ _ _ _ 
Apply production A -> * in node: 5
+ * A 1 - * E _ _ 1 2 2 E _ _ _ _ _ _ _ _ 
Apply production E -> 1 in node: 12
+ * A 1 - * E _ _ 1 2 2 1 _ _ _ _ _ _ _ _ 
Apply production A -> / in node: 2
+ * / 1 - * E _ _ 1 2 2 1 _ _ _ _ _ _ _ _ 
Apply production E -> 2 in node: 6
+ * / 1 - * 2 _ _ 1 2 2 1 _ _ _ _ _ _ _ _ 
Done! Output file generated 
```
(See output.txt for automata and pcode execution)
