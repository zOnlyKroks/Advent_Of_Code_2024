#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int countXMAS(const std::vector<std::string>& grid) {
    const std::string word = "XMAS";
    const int rows = grid.size();
    const int cols = grid[0].size();
    const int wordLen = word.size();
    int count = 0;

    // Define the eight possible directions
    const std::vector<std::pair<int, int>> directions = {
        {0, 1},  // Horizontal right
        {0, -1}, // Horizontal left
        {1, 0},  // Vertical down
        {-1, 0}, // Vertical up
        {1, 1},  // Diagonal down-right
        {-1, -1},// Diagonal up-left
        {1, -1}, // Diagonal down-left
        {-1, 1}  // Diagonal up-right
    };

    // Function to check if a word matches in a given direction
    auto isMatch = [&](int x, int y, int dx, int dy) {
        for (int i = 0; i < wordLen; ++i) {
            const int nx = x + i * dx;
            if (const int ny = y + i * dy; nx < 0 || ny < 0 || nx >= rows || ny >= cols || grid[nx][ny] != word[i]) {
                return false;
            }
        }
        return true;
    };

    // Traverse the grid
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'X') { // Potential start of "XMAS"
                for (const auto&[fst, snd] : directions) {
                    if (isMatch(i, j, fst, snd)) {
                        ++count;
                    }
                }
            }
        }
    }

    return count;
}

int countXMASPattern(const std::vector<std::string>& grid) {
    const int rows = grid.size();
    if (rows == 0) return 0; // Handle empty grid edge case
    const int cols = grid[0].size();
    if (cols == 0) return 0; // Handle empty grid edge case
    int count = 0;

    // Lambda function to check X-MAS pattern at (x, y)
    auto isXMASPattern = [&](const int x, const int y) {
        // Ensure bounds for the X-MAS pattern
        if (x - 1 < 0 || x + 1 >= rows || y - 1 < 0 || y + 1 >= cols) return false;

        // All possible rotations for "MAS"
        const std::string MAS1 = "MAS"; // Forwards
        const std::string MAS2 = "SAM"; // Backwards

        // Top-left diagonal check (M-A-S)
        const std::string topLeft = {grid[x - 1][y - 1], grid[x][y], grid[x + 1][y + 1]};
        // Bottom-left diagonal check (M-A-S)
        const std::string bottomLeft = {grid[x + 1][y - 1], grid[x][y], grid[x - 1][y + 1]};

        // Check if either diagonal matches the pattern
        return (topLeft == MAS1 && bottomLeft == MAS1) ||
               (topLeft == MAS1 && bottomLeft == MAS2) ||
               (topLeft == MAS2 && bottomLeft == MAS1) ||
               (topLeft == MAS2 && bottomLeft == MAS2);
    };

    // Traverse the grid
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            if (grid[i][j] == 'A' && isXMASPattern(i, j)) {
                ++count;
            }
        }
    }

    return count;
}

int main() {
    std::ifstream inputFile("C:/Users/finnr/CLionProjects/Advent_Of_Code_2024/input_4.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1;
    }

    std::vector<std::string> grid;
    std::string line;
    while (std::getline(inputFile, line)) {
        grid.push_back(line);
    }
    inputFile.close();

    if (grid.empty()) {
        std::cerr << "Error: Grid is empty." << std::endl;
        return 1;
    }

    // Part One
    int partOneResult = countXMAS(grid);
    std::cout << "Total occurrences of XMAS: " << partOneResult << std::endl;

    // Part Two
    int partTwoResult = countXMASPattern(grid);
    std::cout << "Total occurrences of X-MAS: " << partTwoResult << std::endl;

    return 0;
}

