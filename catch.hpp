// ============================================================
// Catch2 v2.x Compatible Stub (with tag filtering + verbose)
// Replace with official catch.hpp for production use
// ============================================================
#ifndef CATCH_HPP_INCLUDED
#define CATCH_HPP_INCLUDED

#include <string>
#include <stdexcept>
#include <cmath>
#include <sstream>
#include <iostream>
#include <functional>
#include <vector>

#ifdef CATCH_CONFIG_MAIN
int main(int argc, char* argv[]);
#endif

namespace Catch {

    // Global verbose flag accessible from macros
    inline bool& showSuccess() {
        static bool val = false;
        return val;
    }

    struct ApproxHelper {
        double value;
        double epsilon = 0.00001;
        ApproxHelper(double v) : value(v) {}
        friend bool operator==(double lhs, const ApproxHelper& rhs) {
            return std::fabs(lhs - rhs.value) < rhs.epsilon;
        }
        friend bool operator==(const ApproxHelper& lhs, double rhs) {
            return std::fabs(rhs - lhs.value) < lhs.epsilon;
        }
    };

    struct TestCase {
        std::string name;
        std::string tags;
        std::function<void()> func;

        bool matchesFilter(const std::string& filter) const {
            if (filter.empty()) return true;
            if (filter.front() == '[' && filter.back() == ']') {
                return tags.find(filter) != std::string::npos;
            }
            return name.find(filter) != std::string::npos;
        }
    };

    inline std::vector<TestCase>& getTests() {
        static std::vector<TestCase> tests;
        return tests;
    }

    // Tracks current test name for verbose assertion output
    inline std::string& currentTest() {
        static std::string name;
        return name;
    }

    struct AutoReg {
        AutoReg(std::function<void()> f, const char* name, const char* tags) {
            getTests().push_back({name, tags, f});
        }
    };
}

inline Catch::ApproxHelper Approx(double v) { return Catch::ApproxHelper(v); }

#define INTERNAL_CATCH_UNIQUE_NAME2(name, line) name##line
#define INTERNAL_CATCH_UNIQUE_NAME(name, line) INTERNAL_CATCH_UNIQUE_NAME2(name, line)

#define TEST_CASE(name, tags) \
    static void INTERNAL_CATCH_UNIQUE_NAME(test_func_, __LINE__)(); \
    static Catch::AutoReg INTERNAL_CATCH_UNIQUE_NAME(autoreg_, __LINE__)( \
        INTERNAL_CATCH_UNIQUE_NAME(test_func_, __LINE__), name, tags); \
    static void INTERNAL_CATCH_UNIQUE_NAME(test_func_, __LINE__)()

#define REQUIRE(expr) \
    do { if (!(expr)) { \
        std::cerr << "  FAILED: " << #expr << "\n    at " << __FILE__ << ":" << __LINE__ << "\n"; \
        throw std::runtime_error("Assertion failed"); \
    } else if (Catch::showSuccess()) { \
        std::cout << "    PASSED: " << #expr << "\n"; \
    } } while(0)

#define REQUIRE_FALSE(expr) \
    do { if ((expr)) { \
        std::cerr << "  FAILED: !(" << #expr << ")\n    at " << __FILE__ << ":" << __LINE__ << "\n"; \
        throw std::runtime_error("Assertion failed"); \
    } else if (Catch::showSuccess()) { \
        std::cout << "    PASSED: !(" << #expr << ")\n"; \
    } } while(0)

#define REQUIRE_THROWS_AS(expr, type) \
    do { bool caught = false; \
        try { expr; } catch (const type&) { caught = true; } catch (...) {} \
        if (!caught) { \
            std::cerr << "  FAILED: Expected " << #type << " from " << #expr \
                      << "\n    at " << __FILE__ << ":" << __LINE__ << "\n"; \
            throw std::runtime_error("Assertion failed"); \
        } else if (Catch::showSuccess()) { \
            std::cout << "    PASSED: " << #expr << " threw " << #type << "\n"; \
        } \
    } while(0)

#ifdef CATCH_CONFIG_MAIN
int main(int argc, char* argv[]) {
    std::string filter;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-s" || arg == "--success") {
            Catch::showSuccess() = true;
        } else if (arg == "-r" && i + 1 < argc) {
            i++; // skip reporter name
        } else if (arg == "-l" || arg == "--list-tests") {
            for (auto& t : Catch::getTests()) {
                std::cout << "  " << t.name << "\n    " << t.tags << "\n";
            }
            return 0;
        } else if (!arg.empty() && arg[0] != '-') {
            filter = arg;
        }
    }

    int passed = 0, failed = 0, skipped = 0;

    for (auto& t : Catch::getTests()) {
        if (!t.matchesFilter(filter)) {
            skipped++;
            continue;
        }
        Catch::currentTest() = t.name;
        if (Catch::showSuccess()) {
            std::cout << "\n--- " << t.name << " " << t.tags << " ---\n";
        }
        try {
            t.func();
            passed++;
            std::cout << "PASSED: " << t.name << "\n";
        } catch (...) {
            failed++;
            std::cout << "FAILED: " << t.name << "\n";
        }
    }

    std::cout << "\n=======================================\n";
    if (!filter.empty()) {
        std::cout << "Filter: " << filter << "\n";
    }
    std::cout << passed << " passed, " << failed << " failed";
    if (skipped > 0) std::cout << ", " << skipped << " skipped";
    std::cout << "\n";

    return failed > 0 ? 1 : 0;
}
#endif

#endif // CATCH_HPP_INCLUDED
