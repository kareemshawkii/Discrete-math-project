#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Function to generate the truth table
void generateTruthTable(vector<vector<int>> &truthTable, int numVars) {
    int rows = 1 << numVars;
    truthTable.resize(rows, vector<int>(numVars));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < numVars; ++j) {
            truthTable[i][j] = (i >> (numVars - j - 1)) & 1;
        }
    }
}
// Function to evaluate a logical expression
bool evaluateExpression(const vector<int> &row, const string &expression) {
    bool n1 = row[0];
    bool n2 = row[1];
    bool n3 = row[2];
    if (expression == "n1 && n2") return n1 && n2;
    if (expression == "!n3 || n2") return !n3 || n2;
    if (expression == "n3 || !n1") return n3 || !n1;
    return false;
}
// Function to print the truth table and evaluate premises and conclusion
void evaluateTruthTable(const vector<vector<int>> &truthTable,const string &premise1,const string &premise2,const string &conclusion) {
    bool satisfiable = false;
    bool valid = true;
    cout << setw(4) << "n1" << setw(4) << "n2" << setw(4) << "n3"<< setw(10) << "P1" << setw(10) << "P2" << setw(10) << "C" << endl;
    for (const auto &row : truthTable) {
        bool p1 = evaluateExpression(row, premise1);
        bool p2 = evaluateExpression(row, premise2);
        bool c = evaluateExpression(row, conclusion);
        cout << setw(4) << row[0] << setw(4) << row[1] << setw(4) << row[2]<< setw(10) << p1 << setw(10) << p2 << setw(10) << c << endl;
        if (p1 && p2 && c) {
            satisfiable = true;
        }
        if (p1 && p2 && !c) {
            valid = false;
        }
    }
    cout << "\nThe set of formulas is: " << (satisfiable ? "Satisfiable" : "Not Satisfiable") << endl;
    cout << "The argument is: " << (valid ? "Valid" : "Falsifiable") << endl;
}

int main() {
    int numVars = 3; // Number of variables n1, n2, n3
    vector<vector<int>> truthTable;
    generateTruthTable(truthTable, numVars);
    string premise1 = "n1 && n2";    // I got a scholarship, and I got an "A" in math
    string premise2 = "!n3 || n2";   // I'm not good at logic or I got an "A" in math
    string conclusion = "n3 || !n1"; // I'm good at logic or I don't get a scholarship
    evaluateTruthTable(truthTable, premise1, premise2, conclusion);

    return 0;
}
