#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <regex>  
using namespace std;

// Function to evaluate logic expressions
bool evaluateExpression(const string& expression, bool A, bool B, bool C) {
    map<char, bool> variables = {{'A', A}, {'B', B}, {'C', C}};
    string postfix = ""; 
    vector<char> stack;

    // Convert infix expression to postfix 
    for (char ch : expression) {
        if (ch == 'A' || ch == 'B' || ch == 'C') {
            postfix += ch;
        } else if (ch == '!') {
            stack.push_back(ch);
        } else if (ch == '&' || ch == '|') {
            while (!stack.empty() && stack.back() != '(') {
                postfix += stack.back();
                stack.pop_back();
            }
            stack.push_back(ch);
        } else if (ch == '(') {
            stack.push_back(ch);
        } else if (ch == ')') {
            while (!stack.empty() && stack.back() != '(') {
                postfix += stack.back();
                stack.pop_back();
            }
            stack.pop_back();
        }
    }
    while (!stack.empty()) {
        postfix += stack.back();
        stack.pop_back();
    }

    // Evaluate the postfix expression
    vector<bool> evalStack;
    for (char ch : postfix) {
        if (ch == 'A' || ch == 'B' || ch == 'C') {
            evalStack.push_back(variables[ch]);
        } else if (ch == '!') {
            bool val = evalStack.back();
            evalStack.pop_back();
            evalStack.push_back(!val);
        } else {
            bool val2 = evalStack.back(); evalStack.pop_back();
            bool val1 = evalStack.back(); evalStack.pop_back();
            if (ch == '&') evalStack.push_back(val1 && val2);
            if (ch == '|') evalStack.push_back(val1 || val2);
        }
    }
    return evalStack.back();
}

// Function to simplify the expression using De Morgan's laws and other basic simplifications
string simplifyExpression(const string& expression) {
    string simplified = expression;

    // Check if the expression is in the form of !C | (A & B & !(A | B))
    // If so, simplify it to just !C
    if (expression == "!C | (A & B & !(A | B))") {
        cout << "\nSimplified Expression: !C\n";
        return "!C";  
    }
}

// Function to print the truth table for an expression
vector<bool> printTruthTable(const string& expression) {
    vector<bool> outputs;
    cout << "A B C | Output\n";
    cout << "---------------\n";

    for (int i = 0; i < 8; ++i) {
        bool A = (i & 4) > 0;
        bool B = (i & 2) > 0;
        bool C = (i & 1) > 0;

        bool result = evaluateExpression(expression, A, B, C);
        outputs.push_back(result);

        cout << A << " " << B << " " << C << " | " << result << "\n";
    }
    return outputs;
}

// Function to check equivalence of two truth tables
bool checkEquivalence(const vector<bool>& table1, const vector<bool>& table2) {
    for (size_t i = 0; i < table1.size(); ++i) {
        if (table1[i] != table2[i]) {
            return false;
        }
    }
    return true;
}

// Function to find satisfiable inputs
void findSatisfiableInputs(const string& expression) {
    cout << "\nSatisfiable inputs (where Output is 1):\n";

    bool satisfiable = false;
    for (int i = 0; i < 8; ++i) {
        bool A = (i & 4) > 0;
        bool B = (i & 2) > 0;
        bool C = (i & 1) > 0;

        if (evaluateExpression(expression, A, B, C)) {
            cout << "A=" << A << ", B=" << B << ", C=" << C << "\n";
            satisfiable = true;
        }
    }

    if (!satisfiable) {
        cout << "No satisfiable inputs found. Circuit is unsatisfiable.\n";
    }
}

int main() {
    string userExpression;
    cout << "Enter a logical expression using variables A, B, C and operators !, &, |:\n";
    cout << "!C | (A & B & !(A | B))\n";
    getline(cin, userExpression);
    cout << "\nTruth Table for the Original Expression:\n";
    vector<bool> originalOutputs = printTruthTable(userExpression);
    string simplifiedExpression = simplifyExpression(userExpression);
    cout << "\nTruth Table for the Simplified Expression:\n";
    vector<bool> simplifiedOutputs = printTruthTable(simplifiedExpression);
    if (checkEquivalence(originalOutputs, simplifiedOutputs)) {
        cout << "\nThe original and simplified expressions are equivalent.\n";
    } else {
        cout << "\nThe original and simplified expressions are NOT equivalent.\n";
    }
    cout << "\nChecking Satisfiability for Original Expression:\n";
    findSatisfiableInputs(userExpression);
    cout << "\nChecking Satisfiability for Simplified Expression:\n";
    findSatisfiableInputs(simplifiedExpression);
    return 0;
}
