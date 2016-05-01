# Expr2pci
An translator that aims to convert balanced expressions in pcode instructions.

# Grammar
Grammar for arithmetic expressions (Greibach) 
E -> 1
E -> 2
E -> x
E -> y
E -> (EAEB
A -> +
A -> -
A -> *
A -> /
B -> )

# Limitations
* This machine inherits the limitations of grammar
* X/Y variables dont receive values
* Although the pushdown automata give us the set of productions we need to add them manually to nodes.

# Compiling
gcc -o teste pcode.c rpn2pci.c btree2rpn.c pushdown.c main.c

# Running
./teste "expression"

# Example

List of productions to build the expr (((1-2)*1)+((2*1)/2)) without '(' ')': 
4 4 4 0 6 1 7 0 5 4 4 1 7 0 8 1 
Please apply productions to nodes. (Leftmost First)
E _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 0
A E E _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 1
A A E E E _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 3
A A E A E _ _ E E _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> 1 in node: 1
A 1 E A E _ _ E E _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production A -> - in node: 4
A 1 E A - _ _ E E _ _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> 2 in node: 9
A 1 E A - _ _ E E 2 _ _ _ _ _ _ _ _ _ _ _ 
Apply production A -> * in node: 4
A 1 E A * _ _ E E 2 _ _ _ _ _ _ _ _ _ _ _ 
Apply production E -> 1 in node: 10
A 1 E A * _ _ E E 2 1 _ _ _ _ _ _ _ _ _ _ 
Apply production A -> + in node: 0
+ 1 E A * _ _ E E 2 1 _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 2
+ 1 A A * E E E E 2 1 _ _ _ _ _ _ _ _ _ _ 
Apply production E -> EAE in node: 5
+ 1 A A * A E E E 2 1 E E _ _ _ _ _ _ _ _ 
Apply production E -> 2 in node: 11
+ 1 A A * A E E E 2 1 2 E _ _ _ _ _ _ _ _ 
Apply production A -> * in node: 5
+ 1 A A * * E E E 2 1 2 E _ _ _ _ _ _ _ _ 
Apply production E -> 1 in node: 12
+ 1 A A * * E E E 2 1 2 1 _ _ _ _ _ _ _ _ 
Apply production A -> / in node: 2
+ 1 / A * * E E E 2 1 2 1 _ _ _ _ _ _ _ _ 
Apply production E -> 2 in node: 6
+ 1 / A * * 2 E E 2 1 2 1 _ _ _ _ _ _ _ _ 

(See output.txt for automata and pcode execution)
