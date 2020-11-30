#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstdint>
#include <stack>

// create cell array and pointer and initialize them to zero
std::array<uint8_t, 30000> cells = {};
unsigned int pointer = 0;

// keeps track of the farthest out cell thats been visited, used to print the values of all cells that have actually been accessed
unsigned int farthestCell = 0;

// used for indicating 
int lineNumber = 1;
int columnNumber = 0;

struct bracketLocation {
    std::streampos strmPos;
    int lnNum = 1;
    int colNum = 0;
};

void ptrOutOfBoundsErr();

void dumpCellValues();

int main(int argc, char* argv[])
{
    // keeps track of how far nested we are in brackets, used when finding closing brackets
    int depth;

    // used to make sure weve found a closing bracket
    bool closingFound;

    // used for keeping a record of locations of opening brackets to jump back to, depth of the bracket as key, location in stream as value
    std::stack<bracketLocation> openingBrackets;

    // stores where the current bracket is before jumping, for error printing and storage
    bracketLocation preJumpLoc;

    // check for file path argument
    if (argc < 2) {
        std::cerr << "you need to pass a file name/path as the first argument";
        return EXIT_FAILURE;
    }

    // open up the source code and start stepping through and executing
    std::ifstream sourceCode(argv[1]);
    if (!sourceCode.is_open()) {
        std::cerr << "couldn't open file, maybe the path or name given is wrong?";
        return EXIT_FAILURE;
    }
    char data;
    while (sourceCode.get(data)) {
        columnNumber++;
        switch (data) {
            case '-': cells[pointer]--; break;
            case '+': cells[pointer]++; break;
            case '>': 
                if (pointer == cells.size() - 1) { ptrOutOfBoundsErr(); return EXIT_FAILURE; }
                pointer++;
                if (pointer > farthestCell) { farthestCell = pointer; }
                break;
            case '<': 
                if (pointer == 0) { ptrOutOfBoundsErr(); return EXIT_FAILURE; }
                pointer--;
                break;
            case '.': std::cout << cells[pointer]; break;
            case ',': cells[pointer] = getchar(); break;
            case '[': 
                preJumpLoc = {sourceCode.tellg(), lineNumber, columnNumber};
                if (cells[pointer] != 0) { 
                    openingBrackets.push(preJumpLoc);
                    break; 
                }
                depth = 0;
                closingFound = false;
                while (sourceCode.get(data)) {
                    columnNumber++;
                    if (data == '[') {
                        depth++;
                    } else if (data == ']') {
                        if (depth == 0) {
                            closingFound = true;
                            break;
                        }
                        depth--;
                    } else if (data == '\n') {
                        lineNumber++; 
                        columnNumber = 0;
                    }
                }
                if (depth != 0 || !closingFound) {
                    std::cerr << "\nmy guy you forgot to close a bracket pair thats not very gamer pog of you\n" << "Line: " << preJumpLoc.lnNum << ", Column: " << preJumpLoc.colNum << "\n";;
                    dumpCellValues();
                    return EXIT_FAILURE;
                }
                break;
            case ']':
                if (openingBrackets.size() == 0) {
                    std::cerr << "\nYou just tried to use a closing bracket with no opening bracket, thats not very big brain\n" << "Line: " << lineNumber << ", Column: " << columnNumber << "\n";
                    dumpCellValues();
                    return EXIT_FAILURE;
                }
                if (cells[pointer] != 0) {
                    sourceCode.seekg(openingBrackets.top().strmPos);
                    lineNumber = openingBrackets.top().lnNum;
                    columnNumber = openingBrackets.top().colNum;
                    break;
                }
                openingBrackets.pop();
                break;
            case '\n': lineNumber++; columnNumber = 0; break;
        }
    }
    if (openingBrackets.size() != 0) {
        std::cerr << "\nwell that's weird, we reached the end of program and theres still some open loops... The unclosed bracket/s are on:";
        for (int i = openingBrackets.size(); i > 0; i--) {
            std::cerr << "\n";
            bracketLocation errorBracket = openingBrackets.top();
            std::cerr << "Line: " << errorBracket.lnNum << ", Column: " << errorBracket.colNum;
            openingBrackets.pop();
        }
    }
    sourceCode.close();
    std::cout << "\n";
    dumpCellValues();
}

void ptrOutOfBoundsErr() {
    std::cerr << "\nbro you just tried to go out side the cell array bounds, thats like, kinda cring\n" << "Line: " << lineNumber << ", Column: " << columnNumber << "\n";;
    dumpCellValues();
}

int recursionCount = 0;

void dumpCellValues() {
    std::cout << "Do you want to dump the memory cell values? y/n: ";
    std::string input;
    std::cin >> input;
    if (input == "y" || input == "yes") {
        for (unsigned int i = 0; i <= farthestCell; i++) {
            std::cout << "Cell " << i << ": " << +cells[i] << "\n";
        }
        std::cout << "Pointer is at cell " << pointer;
    } else if (input == "n" || input == "no") {
        std::cout << "coolio";
    } else {
        if (recursionCount < 4) {
            recursionCount++;
            dumpCellValues();
        } else {
            std::cout << "You are either really bad at typing or ABSOLUTELY HILARIOUS";
        }
    }
    return;
}




/* Code Graveyard:


uint8_t eightBit = getchar();
std::cout << eightBit << "   " << +eightBit << "\n";


for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << "\n";
}

std::cout << "Hello World!\n";  << psst this is the default hello world, they're like, a big deal!

assert(0 <= pointer && pointer < 100);


void increment() {
    cells[pointer]++;
}

void decrement() {
    cells[pointer]--;
}

void right() {
    pointer++;
}

void left() {
    pointer--;
}


*/

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
