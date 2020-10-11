
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<vector<char>> ReadFile(const char *fileName, int &status)
{
    fstream newfile;
    vector<vector<char>> board;

    status = 0;
    int col = -1;
    newfile.open(fileName, ios::in);

    if (newfile.is_open()){

        string line;
        //Reading each line from the file
        while(getline(newfile, line)){
            vector<char> rowVector;

            //Iterating through each characters in the line
            for(int i = 0; i < line.length(); i++)
            {
                if(line[i] != '\r' && line[i] != '\n')
                    rowVector.push_back(line[i]);
            }

            //For the first time, recording the colomn length
            if(col == -1)
                col = rowVector.size();
            else if(col != rowVector.size())
            {
                //If the colomn length of next row is not same, then print error.
                status = -1;
                cout << "File doesn`t have same no. of column in all rows.";
                break;
            }

            board.push_back(rowVector);

        }
        newfile.close();
    }
    else
    {
        //Printing the error is File doesn`t exist or issue reading file
        status = -1;
        cout << "File doesn`t exist or issue reading file.";
    }
    return board;
}

vector<vector<char>> RandomBoard()
{
    //Assumption of a square board with rows from 5 to 15
    int row = 5 + (rand() % 10);
    int col = row, prob;

    vector<vector<char>> board;

    for(int i = 0; i < row; i++)
    {
        vector<char> rowVector;

        for(int j = 0; j < col; j++)
        {
            prob = rand() % 100;
            //Filling live cell with 30% of probability
            if((prob % 3) == 0)
                rowVector.push_back('X');
            else
                rowVector.push_back('-');
        }

        board.push_back(rowVector);
    }

    return board;
}

void PrintBoard(vector<vector<char>> board)
{
    //Printing header
    cout << endl;
    for(int j = 0; j < board[0].size(); j++)
        cout << "---" ;
    cout << endl;

    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            cout << " " << board[i][j] << " ";
        }
        cout << endl;
    }

    //Printing footer
    for(int j = 0; j < board[0].size(); j++)
        cout << "---" ;
    cout << endl;
}

bool isBoardEmpty(vector<vector<char>> board)
{

    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            //If any of the cell contains 'X', then returns false
            if(board[i][j] == 'X')
            {
                return false;
            }
        }
    }
    return true;

}

vector<vector<char>> PrintMenu(int &status)
{
    vector<vector<char>> board;

    cout << "=============================" << endl;
    cout << "   Welcome to Game of Life" << endl;
    cout << "=============================" << endl;

    int choice = 0;

    cout << "Do you want to load world from " << endl;
    cout << "1. From a file " << endl;
    cout << "2. Random board " << endl;
    cout << ">";

    while(choice != 1 && choice != 2)
    {
        cin >> choice;

        if(choice == 1)
        {
            cout << "Enter file name :" ;
            string fileName;
            cin >> fileName;

            board = ReadFile(fileName.c_str(), status);
        }
        else if(choice == 2)
        {
            board = RandomBoard();
        }
        else
            cout << "Please enter a valid choice." << endl;
            cout << ">";
    }

    return board;
}

int ReadBoundaryCondition()
{
    int borderCondition = 0;

    cout << "Please select a Border condition" << endl;
    cout << "1. Classic mode" << endl;
    cout << "2. Doughnut mode" << endl;
    cout << ">" ;

    while(borderCondition != 1 && borderCondition != 2)
    {
        cin >> borderCondition;
        if(borderCondition != 1 && borderCondition != 2)
            cout << "Please choose a valid option (1/2) :";
    }

    return borderCondition;
}

bool ReadPauseCondition()
{
    char choice;
    cout << "Do you want to pause between each generation (Y/N) :";

    while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
    {
        cin >> choice;
        if(choice == 'y' || choice == 'Y')
            return true;
        if(choice == 'n' || choice == 'N')
            return false;

        cout << "Please enter a valid option (Y/N) :";
    }

}

int getNeighbourState(vector<vector<char>> board, int i, int j, int borderCondition)
{
    int rows = board.size();
    int cols = board[0].size();

    if(borderCondition == 2)
    {
        //Doughnut mode : Wrapping up the x and y to the other side of the boundary.
        i = (i + board.size()) % board.size();
        j = (j + board[0].size()) % board[0].size();

        if(board[i][j] == 'X')
            return 1;
    }
    else
    {
        //Classic mode : All boundaries to be treated as dead cells.
        if(i < 0 || i >= rows || j < 0 || j >= cols)
            return 0;

        if(board[i][j] == 'X')
            return 1;
    }
    return 0;
}

int getNeighbourCount(vector<vector<char>> board, int i, int j, int borderCondition)
{
    int rows = board.size();
    int cols = board[0].size();
    int count = 0;

    count += getNeighbourState(board, i - 1, j - 1, borderCondition);
    count += getNeighbourState(board, i - 1, j, borderCondition);
    count += getNeighbourState(board, i - 1, j + 1, borderCondition);

    count += getNeighbourState(board, i, j - 1, borderCondition);
    count += getNeighbourState(board, i, j + 1, borderCondition);

    count += getNeighbourState(board, i + 1, j - 1, borderCondition);
    count += getNeighbourState(board, i + 1, j, borderCondition);
    count += getNeighbourState(board, i + 1, j + 1, borderCondition);

    return count;
}
vector<vector<char>> moveNextGeneration(vector<vector<char>> board, int borderCondition)
{
    vector<vector<char>> newBoard;

    //Creating a new board with same size as old board
    for(int i = 0; i < board.size(); i++)
    {
        vector<char> rowVector;
        for(int j = 0; j < board[i].size(); j++)
        {
            rowVector.push_back(board[i][j]);
        }
        newBoard.push_back(rowVector);
    }

    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            int noOfNeigh = getNeighbourCount(board, i, j, borderCondition);

            if(noOfNeigh <= 1)
            {
               newBoard[i][j] = '-';
            }
            else if(noOfNeigh >= 4)
            {
                newBoard[i][j] = '-';
            }
            else if(noOfNeigh == 3)
            {
                newBoard[i][j] = 'X';
            }
        }
    }
    return newBoard;
}

int main()
{
    int status, borderCondition;
    bool pauseState;

    vector<vector<char>> board = PrintMenu(status);

    if(status == -1)
        return 1;

    borderCondition = ReadBoundaryCondition();

    pauseState = ReadPauseCondition();

    std::cin.ignore();

    PrintBoard(board);

    int generation = 1;
    while(!isBoardEmpty(board))
    {
        cout << endl << "Generation : " << generation << endl;

        board = moveNextGeneration(board, borderCondition);

        PrintBoard(board);

        if(pauseState)
        {
            cout << endl << "Press any key to continue." << endl;
            std::cin.ignore();
        }

        generation++;
    }

    return 0;
}
