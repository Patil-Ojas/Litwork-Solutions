#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();
        // creating 3 2d matrices to check for rows, col, and grids
        int rowcase[9][9] = {0};
        int colcase[9][9] = {0};
        int gridcase[9][9] = {0};

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '0'; // converting char to no.

                    int k = i / 3 * 3 + j / 3; // finding grid no.
                    if (rowcase[i][num - 1]++ || colcase[j][num - 1]++ || gridcase[k][num - 1]++)
                        return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution solution;

    vector<vector<char>> sudokuBoard(9, vector<char>(9));
    int size;
    cin>>size;
    cout << "Enter the Sudoku board (use '.' for empty cells):\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> sudokuBoard[i][j];
        }
    }

    bool isValid = solution.isValidSudoku(sudokuBoard);

    if (isValid) {
        cout << "The Sudoku board is valid.\n";
    } else {
        cout << "The Sudoku board is not valid.\n";
    }

    return 0;
}
