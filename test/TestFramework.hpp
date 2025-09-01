#pragma once

#include <string>
#include <iostream>
#include <stdexcept>
#include <functional>

namespace just::demo::test {
    class TestFramework {
    public:
        static void assertEquals(const std::string &expected, const std::string &actual) {
            if (expected != actual) {
                std::cerr << "Assertion failed!\n";
                std::cerr << "Expected:\n" << expected << "\n";
                std::cerr << "Actual:\n" << actual << "\n";
                throw std::runtime_error("Test assertion failed");
            }
        }

        static void runTest(const std::string &testName, std::function<void()> testFunc) {
            try {
                std::cout << "Running " << testName << "... ";
                testFunc();
                std::cout << "PASSED\n";
            } catch (const std::exception &e) {
                std::cout << "FAILED: " << e.what() << "\n";
                throw;
            }
        }

        static void runTests(const std::string &suiteName,
                             const std::vector<std::pair<std::string, std::function<void()> > > &tests) {
            std::cout << "\n=== Running Test Suite: " << suiteName << " ===\n";

            int passed = 0;
            int failed = 0;

            for (const auto &[testName, testFunc]: tests) {
                try {
                    runTest(testName, testFunc);
                    ++passed;
                } catch (...) {
                    ++failed;
                }
            }

            std::cout << "\n=== Test Suite Summary ===\n";
            std::cout << "Total: " << (passed + failed) << ", Passed: " << passed << ", Failed: " << failed << "\n";

            if (failed > 0) {
                throw std::runtime_error("Test suite failed with " + std::to_string(failed) + " failures");
            }
        }
    };
}
