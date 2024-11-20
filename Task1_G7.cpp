#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;
// Function to generate the truth table
void generateTruthTable(vector<vector<int>>& truthTable, int num) {
    int rows = 1 << num; // calculate 2^(num)
  truthTable.resize(rows, vector<int>(num)); //resizes truthTable to have rows number of rows, each containing a vector of num integers. Initially, all values are set to 0.
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < num; ++j) {
            truthTable[i][j] = (i >> (num - j - 1)) & 1;//This is a bitwise right shift operation. It shifts the bits of i to the right by (numVars - j - 1) positions-& 1: This performs a bitwise AND operation with 1, effectively extracting the bit at the position (numVars - j - 1) of i.
        }
    }
}
// Function to print the truth table
void printTruthTable(const vector<vector<int>>& truthTable) {
    int numVars = truthTable[0].size();
    // Print header
    for (int i = 0; i < numVars; ++i) {
        cout << "n" << i + 1 << " ";
    }
    cout << endl;
    // Print rows
    for (const auto& row : truthTable) {
        for (int val : row) {
            cout << setw(4) << val << " ";//This line prints each value in the row with a width of 4 characters, followed by a space. The setw(4) function from the <iomanip> library ensures that each value is printed with a fixed width
        }
        cout << endl;
    }
}
// Function to evaluate the premises and conclusion
bool evaluateExpression(const vector<int>& row, const string& expression) {
    if (expression == "n1 && n2") {
        return row[0] && row[1];
    }
    else if (expression == "n1 || n2") {
        return row[0] || row[1];
    }
    else if (expression == "!n1") {
        return !row[0];
    }
    return false;
}
// Function to check satisfiability and validity
void checkSatisfiabilityAndValidity(const vector<vector<int>>& truthTable, const string& premises, const string& conclusion) {
    bool satisfiable = false;
    bool valid = true;
    for (const auto& row : truthTable) {
        bool premiseResult = evaluateExpression(row, premises);
        bool conclusionResult = evaluateExpression(row, conclusion);
        if (premiseResult && conclusionResult) {
            satisfiable = true;
        }
        if (premiseResult && !conclusionResult) {
            valid = false;
        }
    }
    cout << "The set of formulas is: " << (satisfiable ? "Satisfiable" : "Not satisfiable") << endl;
    cout << "The argument is: " << (valid ? "Valid" : "Falsifiable") << endl;
}
int main() {
    int num = 3;
    vector<vector<int>> truthTable;
    generateTruthTable(truthTable, num);
    printTruthTable(truthTable);
    string premises = "n1 && n2";
    string conclusion = "n1 || n2";
    checkSatisfiabilityAndValidity(truthTable, premises, conclusion);
    return 0;
}