#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>

namespace just::demo::util {
    class FileUtils {
    public:
        static std::string readFile(const std::filesystem::path &file) {
            std::ifstream ifs(file);
            if (!ifs.is_open()) {
                throw std::runtime_error("Cannot open file: " + file.string());
            }
            std::stringstream buffer;
            buffer << ifs.rdbuf();
            return buffer.str();
        }

        static void writeFile(const std::filesystem::path &file, const std::string &data) {
            std::filesystem::create_directories(file.parent_path());
            std::ofstream ofs(file);
            if (!ofs.is_open()) {
                throw std::runtime_error("Cannot create file: " + file.string());
            }
            ofs << data;
        }

        static void appendFile(const std::filesystem::path &file, const std::string &data) {
            std::filesystem::create_directories(file.parent_path());
            std::ofstream ofs(file, std::ios::app);
            if (!ofs.is_open()) {
                throw std::runtime_error("Cannot append to file: " + file.string());
            }
            ofs << data;
        }

        static std::vector<std::filesystem::path> streamFiles(const std::filesystem::path &dir) {
            std::vector<std::filesystem::path> files;
            if (std::filesystem::is_directory(dir)) {
                for (const auto &entry: std::filesystem::recursive_directory_iterator(dir)) {
                    if (std::filesystem::is_regular_file(entry)) {
                        files.push_back(entry.path());
                    }
                }
            }
            return files;
        }
    };
}
