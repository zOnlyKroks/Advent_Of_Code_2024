#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

bool isSafeReport(const vector<int>& levels) {
    const int n = levels.size();
    if (n < 2) {
        return false;
    }

    const bool increasing = levels[1] > levels[0];
    for (int i = 1; i < n; ++i) {
        const int diff = levels[i] - levels[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
        if ((increasing && diff < 0) || (!increasing && diff > 0)) {
            return false;
        }
    }

    return true;
}

// Function to check if removing one level makes the report safe
bool isSafeWithDampener(const vector<int>& levels) {
    const int n = levels.size();

    for (int i = 0; i < n; ++i) {

        vector<int> reducedLevels;
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                reducedLevels.push_back(levels[j]);
            }
        }

        if (isSafeReport(reducedLevels)) {
            return true;
        }
    }

    return false;
}

int main() {
    string filename = "/Users/finnrades/CLionProjects/aoc-2024/input_2.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return 1;
    }

    string line;
    int safeReports = 0;
    int dampenedSafeReports = 0;

    while (getline(file, line)) {
        vector<int> levels;
        stringstream ss(line);
        int number;

        while (ss >> number) {
            levels.push_back(number);
        }

        if (isSafeReport(levels)) {
            ++safeReports;
            ++dampenedSafeReports;
        } else if (isSafeWithDampener(levels)) {
            ++dampenedSafeReports;
        }
    }

    file.close();

    cout << "Number of safe reports (without Dampener): " << safeReports << endl;
    cout << "Number of safe reports (with Dampener): " << dampenedSafeReports << endl;

    return 0;
}
