#ifndef PUSHDOWN_H
#define PUSHDOWN_H

// Print execution trace and return the set of applied productions
int * pushDownAutomata(char word[50], int productions[50], FILE *output);

// Add an value at start of stack
void push(char* source, char *value);

// Remove and return the leftmost value at stack
char pop();

// Replace leftmost occurrence of A with B and return new string
char* replace(char* str, char* a, char* b);

#endif