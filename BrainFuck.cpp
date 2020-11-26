#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <cstdint>
#include <stack>

// create cell array and pointer and initialize them to zero
std::array<uint8_t, 30000> cells = {};
int pointer = 0;

/* used for indicating 
int lineNumber = 1;
int columnNumber = 1;*/

bool isPtrOutOfBounds();

int main(int argc, char* argv[])
{


    // keeps track of the farthest out cell thats been visited, used to print the values of all cells that have actually been accessed
    int farthestCell = 0;

    // keeps track of how far nested we are in brackets, used when finding opening and closing brackets
    int depth = 0;

    // used for keeping a record of locations of opening brackets to jump back to, depth of the bracket as key, location in stream as value
    std::stack<std::streampos> openingBrackets;

    // open up the source code and start stepping through and executing
    std::ifstream sourceCode(argv[1]);
    if (!sourceCode.is_open()) {
        std::cerr << "couldn't open file, maybe the path or name given is wrong?";
        return -1;
    }
    char data;
    while (sourceCode.get(data)) {
        // assert(0 <= pointer && pointer < 100);
        switch (data) {
            case '-': cells[pointer]--; break;
            case '+': cells[pointer]++; break;
            case '>': 
                pointer++; 
                if (isPtrOutOfBounds()) { return EXIT_FAILURE; }
                if (pointer > farthestCell) { farthestCell = pointer; }
                break;
            case '<': 
                pointer--; 
                if (isPtrOutOfBounds()) { return EXIT_FAILURE; }
                break;
            case '.': std::cout << cells[pointer]; break;
            case ',': cells[pointer] = getchar(); break;
            case '[': 
                if (cells[pointer] != 0) { 
                    openingBrackets.push(sourceCode.tellg());
                    break; 
                }
                depth = 0;
                while (sourceCode.get(data)) {
                    if (data == '[') {
                        depth++;
                    } else if (data == ']') {
                        if (depth == 0) {
                            break;
                        }
                        depth--;
                    }
                }
                if (depth != 0) {
                    std::cerr << "my guy you forgot to close a bracket pair thats not very gamer pog of you\n";
                    return -1;
                }
                break;
            case ']':
                if (openingBrackets.size() == 0) {
                    std::cerr << "You just tried to use a closing bracket with no opening bracket, thats not very big brain\n";
                    return -1;
                }
                if (cells[pointer] != 0) {
                    sourceCode.seekg(openingBrackets.top());
                    break;
                }
                openingBrackets.pop();
                break;
        }
    }
    sourceCode.close();
    std::cout << '\n';
    for (int i = 0; i <= farthestCell; i++) {
        std::cout << "Cell " << i << ": " << +cells[i] << "\n";
    }
}

bool isPtrOutOfBounds() {
    if (0 > pointer || pointer >= cells.size()) {
        std::cerr << "bro you just tried to go out side the cell array bounds, thats like, kinda cring\n";
        return true;
    }
    return false;
}


/* Code Graveyard:


uint8_t eightBit = getchar();
std::cout << eightBit << "   " << +eightBit << "\n";


for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << "\n";
}

std::cout << "Hello World!\n";  << psst this is the default hello world, they're like, a big deal!




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
