#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Function to generate the truth table based on the number of variables
void generateTruthTable(vector<vector<int>> &truthTable, int numVars) {
    int rows = 1 << numVars;  // Calculate the number of rows (2^numVars)

    // Resize the truth table to have the correct number of rows and columns
    truthTable.resize(rows, vector<int>(numVars));

    // Generate truth values for each combination of variables
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < numVars; ++j) {
            // Set each variable to either 0 or 1 based on its position in the combination
            truthTable[i][j] = (i >> (numVars - j - 1)) & 1;
        }
    }
}

// Function to evaluate a logical expression with variables (n1, n2, n3, ...)
bool evaluateExpression(const vector<int> &row, const string &expression) {
    // Map n1, n2, n3, etc. to the values in the row
    bool n1 = row[0];
    bool n2 = row[1];
    bool n3 = row[2];
    // Evaluate simple logical expressions based on all possible premises
    if (expression == "n1 && n2"||expression == "n2 && n1") return n1 && n2;// AND operation
    if (expression == "!n1 && n2"||expression == "n2 && !n1") return !n1&&n2; //And with not
    if (expression == "n1 && !n2"||expression == "!n2 && n1") return n1&&!n2; //And with not
    if (expression == "!n1 && !n2"||expression == "!n2 && !n1") return !n1&&!n2; //And with not
    if (expression == "n2 || n1"||expression == "n1 || n2") return n2 || n1; // OR operation
    if (expression == "!n1 || n2"||expression == "n2 || !n1") return !n1||n2; //Or with not
    if (expression == "n1 || !n2"||expression == "!n2 || n1") return n1||!n2; //Or with not
    if (expression == "!n1 || !n2"||expression == "!n2 || !n1") return !n1||!n2; //Or with not
    /////////
    if (expression == "n1 && n3"||expression == "n3 && n1") return n1 && n3;// AND operation
    if (expression == "!n1 && n3"||expression == "n3 && !n1") return !n1&&n3; //And with not
    if (expression == "n1 && !n3"||expression == "!n3 && n1") return n1&&!n3; //And with not
    if (expression == "!n1 && !n3"||expression == "!n3 && !n1") return !n1&&!n3; //And with not
    if (expression == "n3 || n1"||expression == "n1 || n3") return n3 || n1; // OR operation
    if (expression == "!n1 || n3"||expression == "n3 || !n1") return !n1||n3; //Or with not
    if (expression == "n1 || !n3"||expression == "!n3 || n1") return n1||!n3; //Or with not
    if (expression == "!n1 || !n3"||expression == "!n3 || !n1") return !n1||!n3; //Or with not
    /////
    if (expression == "n2 && n3"||expression == "n3 && n2") return n2 && n3;// AND operation
    if (expression == "!n2 && n3"||expression == "n3 && !n2") return !n2&&n3; //And with not
    if (expression == "n2 && !n3"||expression == "!n3 && n2") return n2&&!n3; //And with not
    if (expression == "!n2 && !n3"||expression == "!n3 && !n2") return !n2&&!n3; //And with not
    if (expression == "n3 || n2"||expression == "n2 || n3") return n3 || n2; // OR operation
    if (expression == "!n2 || n3"||expression == "n3 || !n2") return !n2||n3; //Or with not
    if (expression == "n2 || !n3"||expression == "!n3 || n2") return n2||!n3; //Or with not
    if (expression == "!n2 || !n3"||expression == "!n3 || !n2") return !n2||!n3; //Or with not

    return false;  // Default return for unsupported expressions
}

// Function to print the truth table and evaluate the premises and conclusion
void evaluateTruthTable(const vector<vector<int>> &truthTable,const string &premise1,const string &premise2,const string &conclusion) {
    bool satisfiable = false;
    bool valid = true;
    // Print the headers for the truth table
    cout << setw(4) << "n1" << setw(4) << "n2" << setw(4) << "n3" << setw(10) << "P1" << setw(10) << "P2" << setw(10) << "C" << endl;
    // Iterate through each row in the truth table
    for (const auto &row : truthTable) {
        // Evaluate the premises and conclusion for the current row
        bool p1 = evaluateExpression(row, premise1);
        bool p2 = evaluateExpression(row, premise2);
        bool c = evaluateExpression(row, conclusion);
        // Print the values for the current row
        cout << setw(4) << row[0] << setw(4) << row[1] << setw(4) << row[2] << setw(10) << p1 << setw(10) << p2 << setw(10) << c << endl;
        // Check if the premises and conclusion are satisfied
        if (p1 && p2 && c) {
            satisfiable = true;
        }
        if (p1 && p2 && !c) {
            valid = false;
        }
    }
    // Output the result for satisfiability and validity
    cout << "\nThe set of formulas is: " << (satisfiable ? "Satisfiable" : "Not Satisfiable") << endl;
    cout << "The argument is: " << (valid ? "Valid" : "Falsifiable") << endl;
}

int main() {
    int numVars = 3;  // Define the number of variables (n1, n2, n3)
    vector<vector<int>> truthTable;

    // Generate the truth table for the specified number of variables
    generateTruthTable(truthTable, numVars);

    // Ask the user to input logical expressions for the premises and conclusion
    cout << "Enter the premise1 and premise2 and conclusion\n"
         << "where the variables are (n1, n2, n3, ....).\n"
         << "and the operators are: (&&, ||, !) \n"
         << "The form is (variable1 operator variable2)" << endl;

    // Get user input for premise1, premise2, and conclusion
    cout << "premise1: " << endl;
    string premise1;  // Example: "n1 && n2" (I got a scholarship, and I got an "A" in math)
    getline(cin, premise1);

    cout << "premise2: " << endl;
    string premise2;  // Example: "!n3 || n2" (I'm not good at logic Or I got an "A" in math)
    getline(cin, premise2);

    cout << "conclusion: " << endl;
    string conclusion;  // Example: "n3 || !n1" (I'm good at logic Or I don't get a scholarship)
    getline(cin, conclusion);

    // Evaluate the truth table with the provided premises and conclusion
    evaluateTruthTable(truthTable, premise1, premise2, conclusion);  // Output should be Satisfiable and Falsifiable

    // another example that Satisfiable and Valid => P1:(!n1 && n2),P2:(!n3 || n2),C(n3 || !n1)
    return 0;
}

