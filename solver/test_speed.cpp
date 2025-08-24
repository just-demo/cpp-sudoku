#include "solver.hpp"
#include "format.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

std::vector<std::string> listLines(const std::string& filePath) {
    std::vector<std::string> lines;
    std::ifstream file(filePath);
    std::string line;
    
    while (std::getline(file, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    
    return lines;
}

int countLines(const std::string& filePath) {
    return listLines(filePath).size();
}

int main() {
    std::string readyDir = "../data/ready";
    std::vector<std::string> files;
    
    // Get all files in the ready directory
    for (const auto& entry : std::filesystem::directory_iterator(readyDir)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }
    
    std::sort(files.begin(), files.end());
    
    // Count lines in each file
    std::map<std::string, int> counts;
    int totalCount = 0;
    
    for (const auto& file : files) {
        int count = countLines(file);
        counts[std::filesystem::path(file).filename().string()] = count;
        totalCount += count;
    }
    
    std::cout << "Files:" << std::endl;
    for (const auto& file : files) {
        std::cout << file << std::endl;
    }
    
    std::cout << "Counts:" << std::endl;
    for (const auto& [filename, count] : counts) {
        std::cout << filename << ": " << count << std::endl;
    }
    
    std::cout << "Total count: " << totalCount << std::endl;
    
    auto start = std::chrono::high_resolution_clock::now();
    int counter = 0;
    std::map<std::string, std::pair<int, double>> statistics;
    
    for (const auto& file : files) {
        auto fileStart = std::chrono::high_resolution_clock::now();
        int fileCount = 0;
        
        auto lines = listLines(file);
        for (const auto& line : lines) {
            std::cout << line << std::endl;
            counter++;
            fileCount++;
            
            if (counter % 2 == 0) {
                auto now = std::chrono::high_resolution_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start);
                std::cout << "progress: " << counter << " / " << elapsed.count() / 1000000000.0 << "s" << std::endl;
            }
            
            if (counter > 10) {
                std::cout << "Stopped after 10 puzzles" << std::endl;
                goto end_loop;
            }
            
            auto sudoku = sudokuFrom1DString(line);
            Solver solver(sudoku);
            solver.solve();
        }
        
        auto fileEnd = std::chrono::high_resolution_clock::now();
        auto fileDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(fileEnd - fileStart);
        statistics[std::filesystem::path(file).filename().string()] = 
            std::make_pair(fileCount, fileDuration.count() / 1000000000.0);
    }
    
end_loop:
    auto end = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    std::cout << "Total time: " << totalDuration.count() / 1000000000.0 << "s" << std::endl;
    
    for (const auto& [filename, stat] : statistics) {
        std::cout << filename << ": " << stat.second << "s / " 
                  << (stat.first > 0 ? stat.second / stat.first : 0) << "s per puzzle" << std::endl;
    }
    
    return 0;
}
