# My-Tokenizer project for cisc 3160
Tokenizer tokenize the string and print out the result if there is no error other ways cout error 


Program:
	Assignment*

Assignment:
	Identifier = Exp;

Exp: 
	Exp + Term | Exp - Term | Term

Term:
	Term * Fact  | Fact

Fact:
	( Exp ) | - Fact | + Fact | Literal | Identifier

Identifier:
     	Letter [Letter | Digit]*

Letter:
	a|...|z|A|...|Z|_

Literal:
	0 | NonZeroDigit Digit*
		
NonZeroDigit:
	1|...|9

Digit:
	0|1|...|9

Sample inputs and outputs
Input 1
x = 001;

Output 1
error

Input 2
x_2 = 0;

Output 2
x_2 = 0

Input 3
x = 0
y = x;
z = ---(x+y);

Output 3
error

Input 4
x = 1;
y = 2;
z = ---(x+y)*(x+-y);

Output 4
x = 1
y = 2
z = 3
