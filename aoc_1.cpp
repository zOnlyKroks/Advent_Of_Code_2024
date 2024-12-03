#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>

int calculateTotalDistance(std::vector<int>& leftList, std::vector<int>& rightList) {
    std::ranges::sort(leftList);
    std::ranges::sort(rightList);

    int totalDistance = 0;
    for (size_t i = 0; i < leftList.size(); ++i) {
        totalDistance += std::abs(leftList[i] - rightList[i]);
    }

    return totalDistance;
}

int calculateSimilarityScore(const std::vector<int>& leftList, const std::vector<int>& rightList) {
    std::unordered_map<int, int> rightFrequency;
    for (int num : rightList) {
        rightFrequency[num]++;
    }

    int similarityScore = 0;
    for (int num : leftList) {
        similarityScore += num * rightFrequency[num];
    }

    return similarityScore;
}

int main() {
    std::vector<int> leftList;
    std::vector<int> rightList;

    std::ifstream inputFile("/Users/finnrades/CLionProjects/aoc-2024/input_1.txt");


    if (!inputFile) {
        std::cerr << "Unable to open the file." << std::endl;
        return 1;
    }

    int a, b;

    while (inputFile >> a >> b) {
        leftList.push_back(a);
        rightList.push_back(b);
    }

    inputFile.close();

    const int totalDistance = calculateTotalDistance(leftList, rightList);

    const int similarityScore = calculateSimilarityScore(leftList, rightList);

    std::cout << "The total distance between the two lists is: " << totalDistance << std::endl;
    std::cout << "The similarity score between the two lists is: " << similarityScore << std::endl;

    return 0;
}
