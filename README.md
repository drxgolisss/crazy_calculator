crazy_calculator

A minimal “crazy” integer calculator supporting only subtraction and unary negation.

Project Overview

crazy_calculator parses and evaluates expressions composed of integer literals and the - operator (both binary subtraction and unary negation). Internally, it builds an expression tree where each node is one of:

Number: a leaf holding an integer value

Negation: a unary node that flips the sign of its child

Subtraction: a binary node that subtracts its right subtree from its left subtree

The tree’s compute() method recursively evaluates the expression.

Invalid inputs (e.g. stray operators, missing operands) are detected and reported with an error message.

Repository Layout

crazy_calculator/
├── CMakeLists.txt              # CMake project configuration
├── expr_tree.hpp               # Base ExprTree interface
├── expr_tree_number.cpp        # Implementation of leaf nodes (numbers)
├── expr_tree_negation.cpp      # Implementation of unary negation nodes
├── expr_tree_subtraction.cpp   # Implementation of binary subtraction nodes
├── parser.hpp                  # Parser declarations
├── parser.cxx                  # Parser implementation (token → ExprTree)
├── main.cxx                    # CLI & unit‐test snippets
├── .gitignore                  # Ignores PDF and build artifacts
└── README.md                   # This file

Note: All .pdf task descriptions (e.g. task_description.pdf) are excluded via .gitignore.

Building

Requirements:

C++17‐compatible compiler

CMake 3.10+

# From project root
mkdir build
cd build
cmake ..             # or: cmake -DCMAKE_BUILD_TYPE=Release ..
make                 # produces the `crazy_calculator` executable

Running

./crazy_calculator

You will be prompted to enter an expression. Tokens must be separated by spaces. Examples:

Enter expression: - - - - 2
Result: 2

Enter expression: 3 - 2
Result: 1

Enter expression: - 3 - - 2
Result: -1

Enter expression: 42
Result: 42

Enter expression: 2 - -
Error: unexpected operator “-” at position 4

How It Works

Lexing & TokenizationThe parser splits the input string on whitespace into numbers and - tokens.

Tree Construction

A number token becomes a NumberNode.

A - when expecting a value becomes a NegationNode.

A - when expecting a binary operator becomes a SubtractionNode.

EvaluationCalling compute() on the root node recursively computes the value of the entire tree.

Extending & Testing

To add a new operator, create a subclass of ExprTree and implement compute() and parsing logic in parser.cxx.

In main.cxx, you’ll find commented‐out unit tests for each node type. Uncomment to run targeted tests.

License

MIT License

Author: Piotr Kharashkevich, crazy_calculator