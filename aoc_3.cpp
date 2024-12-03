#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    string filename = "/Users/finnrades/CLionProjects/aoc-2024/input_3.txt"; // File containing the corrupted memory
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return 1;
    }

    string line;
    long long totalPartOne = 0;
    long long totalPartTwo = 0;
    bool mulEnabled = true;

    // Regex patterns
    regex validMulPattern(R"(mul\((\d+),(\d+)\))");
    regex doPattern(R"(do\(\))");
    regex dontPattern(R"(don't\(\))");
    regex combinedPattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");

    while (getline(file, line)) {
        if (line.empty()) continue;

        smatch match;
        size_t pos = 0;

        while (pos < line.size()) {
            if (string substring = line.substr(pos); regex_search(substring, match, combinedPattern)) {
                if (string matchStr = match.str(); regex_match(matchStr, validMulPattern)) {
                    int x = stoi(match[1]);
                    int y = stoi(match[2]);

                    totalPartOne += x * y;
                    if (mulEnabled) {
                        totalPartTwo += x * y;
                    }
                } else if (regex_match(matchStr, doPattern)) {
                    mulEnabled = true;
                } else if (regex_match(matchStr, dontPattern)) {
                    mulEnabled = false;
                }

                pos += match.position() + match.length();
            } else {
                break;
            }
        }
    }

    file.close();

    cout << "Total sum of valid multiplications (Part One): " << totalPartOne << endl;
    cout << "Total sum of valid multiplications (Part Two): " << totalPartTwo << endl;

    return 0;
}
