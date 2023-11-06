
#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <string>
#include <fstream>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

#define square "\u2588"

void printMenu();
string decimalToBinary(int number);
void celluarAutomation(vector<int> &parentGeneration, int generations);
string addingTrailingZeros(string binaryString);
void initializeGrid(vector<vector<int>> &grid);
void printGrid(const vector<vector<int>> &grid);
void updateGrid(vector<vector<int>> &grid);
void playGame();

const int ROWS = 20;
const int COLS = 40;

int main()
{
    printMenu();
    return 0;
}

string decimalToBinary(int number)
{
    std::string binaryString = std::bitset<32>(number).to_string();

    size_t found = binaryString.find_first_not_of('0');
    if (found != std::string::npos)
    {
        binaryString = binaryString.substr(found);
    }
    else
    {
        binaryString = "0";
    }

    return addingTrailingZeros(binaryString);
}

string addingTrailingZeros(string binaryString)
{
    int numOfZeros = 8 - binaryString.length();
    for (int i = 0; i < numOfZeros; i++)
    {
        binaryString = "0" + binaryString;
    }

    return binaryString;
}

void printPatternFromFile(const string &filename)
{
    ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            cout << line << endl;
        }
        inputFile.close();
    }
    else
    {
        cerr << "File Error Encountered" << endl;
    }
}
void addFile(vector<string> &generation)
{
    ofstream outputFile("pattern.txt", std::ios::trunc);
    if (outputFile.is_open())
    {
        for (string cell : generation)
        {
            outputFile << cell << endl;
        }
        outputFile.close();
    }
    else
    {
        cerr << "File Error Encountered";
    }
}
void celluarAutomation(vector<int> &parentGeneration, int generations)
{

    int ruleToBeUsed;
    vector<int> possibility(8);
    vector<string> patternGrid;

    while (true)
    {
        cout << "Enter the rule that you would like to showcase (1-256): ";
        if (cin >> ruleToBeUsed)
        {
            if (ruleToBeUsed >= 1 && ruleToBeUsed <= 256)
            {
                break; // Valid input, exit the loop
            }
            else
            {
                cout << "Invalid input. Please enter a rule between 1 and 256." << endl;
            }
        }
        else
        {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string binaryConversion = decimalToBinary(ruleToBeUsed);
    for (int i = 0; i < 8; i++)
    {
        possibility[i] = binaryConversion[i] - '0';
    }

    int parentLength = parentGeneration.size();
    vector<int> newGenerations(parentLength);

    for (int generationsCount = 0; generationsCount < generations; generationsCount++)
    {
        for (int j = 0; j < parentLength; j++)
        {
            int left = parentGeneration[(j - 1 + parentLength) % parentLength];
            int right = parentGeneration[(j + 1) % parentLength];

            if (left == 1 && right == 1 && parentGeneration[j] == 1)
            {
                if (possibility[0] == 1)
                {
                    newGenerations[j] = 1;
                }
                else
                {
                    newGenerations[j] = 0;
                }
            }
            else if (left == 1 && right == 1 && parentGeneration[j] == 0)
            {
                if (possibility[1] == 1)
                {
                    newGenerations[j] = 1;
                }
                else
                {
                    newGenerations[j] = 0;
                }
            }
            else if (left == 1 && right == 0 && parentGeneration[j] == 1)
            {
                if (possibility[2] == 1)
                {
                    newGenerations[j] = 1;
                }
                else
                {
                    newGenerations[j] = 0;
                }
            }
            else if (left == 1 && right == 0 && parentGeneration[j] == 0)
            {
                if (possibility[3] == 1)
                {
                    newGenerations[j] = 1;
                }
                else
                {
                    newGenerations[j] = 0;
                }
            }
            else if (left == 0 && right == 1 && parentGeneration[j] == 1)
            {
                if (possibility[4] == 1)
                {
                    newGenerations[j] = 1;
                }
                else
                {
                    newGenerations[j] = 0;
                }
            }
            else if (left == 0 && right == 1 && parentGeneration[j] == 0)
            {
                if (possibility[5] == 1)
                {
                    newGenerations[j] = 1;
                }
                else
                {
                    newGenerations[j] = 0;
                }
            }
            else if (left == 0 && right == 0 && parentGeneration[j] == 1)
            {
                if (possibility[6] == 1)
                {
                    newGenerations[j] = 1;
                }
                else
                {
                    newGenerations[j] = 0;
                }
            }
            else if (left == 0 && right == 0 && parentGeneration[j] == 0)
            {
                if (possibility[7] == 1)
                {
                    newGenerations[j] = 1;
                }
                else
                {
                    newGenerations[j] = 0;
                }
            }
        }

        string parentGenerationString;

        for (int cell : parentGeneration)
        {
            if (cell == 1)
            {
                cout << square;
                parentGenerationString = parentGenerationString + square;
            }
            else
            {
                cout << "  ";
                parentGenerationString = parentGenerationString + "  ";
            }
        }
        cout << endl;
        patternGrid.push_back(parentGenerationString);

        parentGeneration = newGenerations;

        addFile(patternGrid);
    }
}

void printMenu()
{
    int input;
    while (true)
    {
        cout << "[1] Run Cellular Automation" << endl;
        cout << "[2] Run Game" << endl;
        cout << "[3] Load Last Saved Cellular Automation from file " << endl;
        cout << "[4] Convert Decimal Number to Binary Number" << endl;
        cout << "[5] Exit Programme" << endl;
        cout << "Enter desired Option: ";
        if (cin >> input)
        {
            if (input >= 1 && input <= 5)
            {
                break;
            }
            else
            {
                cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            }
        }
        else
        {
            cout << "Invalid input. Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (input == 1)
    {
        int choice;

        while (true)
        {
            cout << "[1] Customized Generations" << endl;
            cout << "[2] Random Generations" << endl;
            cout << "[3] Go Back" << endl;

            cout << "Enter your choice: ";
            cin >> choice;

            if (cin.fail()) // Check if input is not an integer
            {
                cout << "Invalid input. Please enter a valid option (1, 2, or 3)." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (choice < 1 || choice > 3)
            {
                cout << "Invalid input. Please enter a valid option (1, 2, or 3)." << endl;
            }
            else
            {
                // Valid choice made, exit the loop
                break;
            }
        }

        if (choice == 1)
        {
            vector<int> initialGeneration;
            cout << " Enter Parent Generation in Binary (For eg: 00010000000)";
            string generationInput;
            cin >> generationInput;

            for (char bit : generationInput)
            {
                int value = bit - '0';
                initialGeneration.push_back(value);
            }

            cout << "Enter the number of generations to produce: ";
            int numGenerations;
            while (true)
            {
                cin >> numGenerations;

                if (numGenerations <= 0)
                {
                    cout << "Invalid input.Please enter a positive integer for the length.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    break;
                }
            }
            celluarAutomation(initialGeneration, numGenerations);
            printMenu();
        }
        else if (choice == 2)
        {
            vector<int> initialGeneration;
            string generationInput = "00010000000";

            for (char bit : generationInput)
            {
                int value = bit - '0';
                initialGeneration.push_back(value);
            }
            celluarAutomation(initialGeneration, 10);
            printMenu();
        }
        else if (choice == 3)
        {
            printMenu();
        }
    }
    else if (input == 2)
    {
        printMenu();
    }
    else if (input == 3)
    {
        printPatternFromFile("pattern.txt");
        printMenu();
    }
    else if (input == 4)
    {
        int number;
        cout << "Enter Decimal Number that is to be converted: " << endl;
        cin >> number;
        cout << decimalToBinary(number) << endl;
        printMenu();
    }
    else if (input == 5)
    {

        exit(0);
    }
}

void initializeGrid(vector<vector<int>> &grid, int numRows, int numCols)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            grid[i][j] = 0; // Initialize all cells as dead (0)
        }
    }
}

void printGrid(const vector<vector<int>> &grid)
{
    for (const auto &row : grid)
    {
        for (int cell : row)
        {
            if (cell == 1)
            {
                cout << " K "; // Print a filled cell
            }
            else
            {
                cout << " . "; // Print an empty cell
            }
        }
        cout << endl;
    }
}

void updateGrid(vector<vector<int>> &grid)
{
    int numRows = grid.size();
    int numCols = grid[0].size();
    vector<vector<int>> newGrid(numRows, vector<int>(numCols, 0));

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            int neighbors = 0;

            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    if (x == 0 && y == 0)
                        continue; // Skip the current cell
                    int ni = (i + x + numRows) % numRows;
                    int nj = (j + y + numCols) % numCols;
                    neighbors += grid[ni][nj];
                }
            }

            if (grid[i][j] == 1)
            {
                if (neighbors < 2 || neighbors > 3)
                {
                    newGrid[i][j] = 0; // Cell dies due to underpopulation or overpopulation
                }
            }
            else
            {
                if (neighbors == 3)
                {
                    newGrid[i][j] = 1; // Cell is born due to reproduction
                }
            }
        }
    }

    if (newGrid == grid)
    {
        cout << "The grid has stabilized. The game will now terminate." << endl;
        exit(0); // Terminate the game
    }

    grid = newGrid; // Update the grid
}

void playGame()
{
    const int numRows = 15;
    const int numCols = 15;

    vector<vector<int>> grid(numRows, vector<int>(numCols, 0));

    srand(static_cast<unsigned>(time(nullptr)));

    int numCells;
    while (true)
    {
        cout << "Enter the number of cells you want to add: ";
        if (cin >> numCells)
        {
            if (numCells >= 0 && numCells <= numRows * numCols)
            {
                break;
            }
            else
            {
                cout << "Invalid input. Please enter a valid number of cells.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else
        {
            cout << "Invalid input. Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    initializeGrid(grid, numRows, numCols);

    for (int i = 0; i < numCells; i++)
    {
        int row, col;
        while (true)
        {
            cout << "Enter the row and column (0-" << numRows - 1 << ") for cell " << i + 1 << ": ";
            if (cin >> row >> col)
            {
                if (row >= 0 && row < numRows && col >= 0 && col < numCols)
                {
                    if (grid[row][col] == 1)
                    {
                        cout << "Cell already occupied. Please select another cell.\n";
                    }
                    else
                    {
                        grid[row][col] = 1; // Set the specified cell as alive (1)
                        break;
                    }
                }
                else
                {
                    cout << "Invalid input. Please enter valid row and column.\n";
                }
            }
            else
            {
                cout << "Invalid input. Please enter valid row and column.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    while (true)
    {
        cout << "Current state of the grid:\n";
        printGrid(grid);
        updateGrid(grid);
        this_thread::sleep_for(chrono::milliseconds(500)); // Delay between generations (500 milliseconds)
        cout << "\033[H\033[J";                            // Clear the console (Unix/Linux)
    }
}
