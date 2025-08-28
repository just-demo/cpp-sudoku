#include <iostream>
#include <thread>
#include <future>
#include <chrono>
// #include <string>
//
// class Job {
// public:
//     void run() {
//         // Simulate work
//         std::this_thread::sleep_for(std::chrono::seconds(2));
//         std::cout << "ok" << std::endl;
//     }
// };
//
// int main() {
//     auto startTime = std::chrono::steady_clock::now();
//
//     for (int i = 0; i < 10; i++) {
//         Job job;
//
//         // Run Job::run asynchronously
//         auto future = std::async(std::launch::async, [&job]() {
//             job.run();
//         });
//
//         // Wait up to 3 seconds
//         if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
//             // Ensure exceptions (if any) are rethrown
//             future.get();
//         } else {
//             std::cout << "error: job timed out" << std::endl;
//         }
//     }
//
//     std::cout << "done!" << std::endl;
//     auto endTime = std::chrono::steady_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
//     std::cout << "Time: " << duration.count() << "ms" << std::endl;
//     return 0;
// }
//
// #include <iostream>
// #include <thread>
// #include <future>
// #include <chrono>

class Job {
    bool interrupted = false;
public:
    std::string run() {
        auto start = std::chrono::steady_clock::now();

        // emulate work for ~2 seconds
        while (!interrupted) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);

            if (elapsed.count() >= 2) {
                break;
            }

            // simulate some work (prevent 100% CPU burn)
            // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        // Simulate work
        // std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "ok" << std::endl;
        return "abc";
    }

    void interrupt() {
        interrupted = true;
    }
};

int main() {
    auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < 3; i++) {
        Job job;

        // Run Job::run asynchronously
        auto future = std::async(std::launch::async, [&job]() {
            return job.run();
        });

        // Wait up to 3 seconds
        if (future.wait_for(std::chrono::seconds(1)) == std::future_status::ready) {
            std::string result = future.get();
            std::cout << result << std::endl;
        } else {
            std::cout << "error: job timed out" << std::endl;
            job.interrupt();
            std::string result = future.get();
            std::cout << result << std::endl;
        }
    }

    std::cout << "done!" << std::endl;
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "Time: " << duration.count() << "ms" << std::endl;
    return 0;
}