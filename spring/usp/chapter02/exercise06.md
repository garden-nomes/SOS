# Exercise 6
Listlib.h/.c uses the "static" keyword to approximate private variables and functions, and
instance variables (which can be made public with the "extern" keyword). What it can't do
is create seperate instances.

We actually saw a few hacks to fix this in OS161, such as passing a struct of state information
to "member" functions or creating whole "classes" using preprocessor directives to create
lists of different types.