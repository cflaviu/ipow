import qbs

CppApplication {
    cpp.cxxLanguageVersion: "c++20"
    cpp.enableRtti: false
    consoleApplication: true
    install: true
    files: [
        "performance_test.cpp",
        "unsafe_ipow.hpp",
    ]
}
