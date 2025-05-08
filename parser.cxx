#include "parser.hpp"
#include "expr_tree.hpp"
#include "expr_tree_number.hpp"
#include "expr_tree_negation.hpp"
#include "expr_tree_subtraction.hpp"

Parser::Parser()
    : top(nullptr), bottom(nullptr)
{
}

bool Parser::parse(const std::string &input)
{
    resetTree();

    int pos = 0;
    int number = 0;
    bool parsing_number = false;
    bool expect_number = true;  

    while (pos < input.length()) {
        char c = input[pos];

        if (std::isspace(c)) {
            if (parsing_number) {
                if (!addNumberToTree(number)) {
                    resetTree();
                    return false;
                }
                parsing_number = false;
                number = 0;
                expect_number = false; 
            }
            pos++;
            continue;
        }

       
        if (std::isdigit(c)) {
            parsing_number = true;
            number = number * 10 + (c - '0');
            pos++;
            continue;
        }

        
        if (c == '-') {
            if (parsing_number) {
                if (!addNumberToTree(number)) {
                    resetTree();
                    return false;
                }
                parsing_number = false;
                number = 0;
                expect_number = false;
            }
            addMinusToTree();
            expect_number = true; 
            pos++;
            continue;
        }

        
        resetTree();
        return false;
    }

    
    if (parsing_number) {
        if (!addNumberToTree(number)) {
            resetTree();
            return false;
        }
        expect_number = false;
    }

   
    if (expect_number) {
        resetTree();
        return false;
    }

    return true;
}

ExprTree *Parser::getExpression() const
{
    return top;
}

/*
TODO: uncomment below 2 methods and call them inside of the parse() method.
*/

bool Parser::addNumberToTree(int num)
{
    ExprTree *expr = new ExprTreeNumber(num);
    if(bottom == nullptr && top == nullptr) {
        top = expr;
    } else if(bottom == nullptr) {
        delete expr;
        return false;
    } else {
        bottom->addRight(expr);
        bottom = nullptr;
    }
    return true;
}

void Parser::addMinusToTree()
{
    if(bottom == nullptr && top == nullptr) {
        ExprTree *expr = new ExprTreeNegation();
        bottom = expr;
        top = bottom;
    } else if(bottom == nullptr) {
        ExprTree *expr = new ExprTreeSubtraction(top);
        top = expr;
        bottom = expr;
    } else {
        ExprTree *expr = new ExprTreeNegation();
        bottom->addRight(expr);
        bottom = expr;
    }
}

void Parser::resetTree()
{
    delete top;
    top = nullptr;
    bottom = nullptr;
}
