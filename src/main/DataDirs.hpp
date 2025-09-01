#pragma once

#include <filesystem>

namespace just::demo::main {
    class DataDirs {
    public:
        static inline const std::filesystem::path DATA_DIR{"data"};
        static inline const std::filesystem::path READY_DIR{DATA_DIR / "ready"};
        static inline const std::filesystem::path REDUCER_FAILED_DIR{DATA_DIR / "reducer-failed"};
        static inline const std::filesystem::path REDUCER_FIXED_DIR{DATA_DIR / "reducer-fixed"};
    };
}
