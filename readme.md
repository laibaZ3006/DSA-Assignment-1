# DSA Assignment 1 - BSEF24A029
## Expression Conversion and Evaluation

## Description
This program converts an infix arithmetic expression into postfix notation and evaluates the expression.

The program supports:
- Multi-digit integers
- Variables
- Operators:
  - +
  - -
  - *
  - /
- Brackets:
  - ()
  - []
  - {}

The program:
1. Tokenizes the infix expression
2. Converts infix to postfix
3. Asks user to enter values for variables
4. Evaluates the postfix expression
5. Displays the final result

---

# Compilation

Compile using g++:

```bash
g++ main.cpp -o main
```

---

# Run

```bash
./main
```

For Windows:

```bash
main.exe
```

---

# Example

## Input

```text
a + b * (c + 2)
```

## Output

```text
Postfix Expression:
a b c 2 + * +

Enter value for a: 3
Enter value for b: 5
Enter value for c: 2

Final Result = 23
```

---

# Features
- Infix to postfix conversion
- Postfix evaluation
- Multi-digit number support
- Variable support
- Bracket validation
- Error handling

---

# Author
Laiba Zaheer