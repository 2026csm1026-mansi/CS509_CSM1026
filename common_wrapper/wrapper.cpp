#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;


// --------------------------------------------------
// Check whether a file exists
// --------------------------------------------------

bool fileExists(const fs::path& path)
{
    return fs::exists(path);
}


// --------------------------------------------------
// Run an external command
// --------------------------------------------------

void runCommand(const std::string& command)
{
    std::cout << "\nRunning:\n";
    std::cout << command << "\n\n";

    STARTUPINFOA startupInfo{};
    PROCESS_INFORMATION processInfo{};

    startupInfo.cb = sizeof(startupInfo);

    std::string commandLine = command;

    BOOL success = CreateProcessA(
        nullptr,
        commandLine.data(),
        nullptr,
        nullptr,
        FALSE,
        0,
        nullptr,
        nullptr,
        &startupInfo,
        &processInfo
    );

    if (!success)
    {
        std::cout
            << "Error: could not start process. Error code: "
            << GetLastError()
            << "\n";

        return;
    }

    WaitForSingleObject(
        processInfo.hProcess,
        INFINITE
    );

    DWORD exitCode = 0;

    GetExitCodeProcess(
        processInfo.hProcess,
        &exitCode
    );

    CloseHandle(processInfo.hProcess);
    CloseHandle(processInfo.hThread);

    if (exitCode != 0)
    {
        std::cout
            << "\nError: command failed with exit code "
            << exitCode
            << ".\n";
    }
}


// --------------------------------------------------
// Display menu
// --------------------------------------------------

void showMenu()
{
    std::cout << "\n====================================\n";
    std::cout << "       CS509 Assignment Wrapper\n";
    std::cout << "====================================\n";
    std::cout << "1. Run GEMM - selected test\n";
    std::cout << "2. Run GEMM - all tests\n";
    std::cout << "3. Run CSR - selected test\n";
    std::cout << "4. Run CSR - all tests\n";
    std::cout << "5. Run Bellman-Ford - selected test\n";
    std::cout << "6. Run Bellman-Ford - all tests\n";
    std::cout << "7. Run Floyd-Warshall - selected test\n";
    std::cout << "8. Run Floyd-Warshall - all tests\n";
    std::cout << "9. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Enter your choice: ";
}


// --------------------------------------------------
// Put quotes around a path
// --------------------------------------------------

std::string quotePath(const fs::path& path)
{
    return "\"" + path.string() + "\"";
}


// --------------------------------------------------
// Main
// --------------------------------------------------

int main()
{
    // --------------------------------------------------
    // Find repository root
    // --------------------------------------------------

    fs::path wrapperDirectory =
        fs::current_path();

    fs::path repositoryRoot =
        wrapperDirectory.parent_path();


    // --------------------------------------------------
    // Assignment 1 paths
    // --------------------------------------------------

    fs::path assignmentPath =
        repositoryRoot / "assignment_01";

    fs::path driverPath =
        assignmentPath / "driver";

    fs::path testsPath =
        assignmentPath / "tests";


    // --------------------------------------------------
    // Assignment 2 paths
    // --------------------------------------------------

    fs::path assignment02Path =
        repositoryRoot / "assignment_02";

    fs::path assignment02DriverPath =
        assignment02Path / "driver";

    fs::path assignment02TestsPath =
        assignment02Path / "tests";


    // --------------------------------------------------
    // Executable paths
    // --------------------------------------------------

    fs::path gemmExecutable =
        driverPath / "gemm_test.exe";

    fs::path csrExecutable =
        driverPath / "csr_test.exe";

    fs::path assignment02Executable =
        assignment02DriverPath / "driver.exe";


    // --------------------------------------------------
    // Main menu loop
    // --------------------------------------------------

    while (true)
    {
        showMenu();

        int choice;

        std::cin >> choice;


        // --------------------------------------------------
        // Invalid input
        // --------------------------------------------------

        if (!std::cin)
        {
            std::cin.clear();

            std::cin.ignore(
                10000,
                '\n'
            );

            std::cout
                << "Error: invalid menu choice.\n";

            continue;
        }


        // ==================================================
        // 1. GEMM - SELECTED TEST
        // ==================================================

        if (choice == 1)
        {
            if (!fileExists(gemmExecutable))
            {
                std::cout
                    << "Error: GEMM executable not found:\n"
                    << gemmExecutable.string()
                    << "\n";

                continue;
            }

            std::string testFile;
            int blockSize;

            std::cout
                << "Enter GEMM test file name "
                   "(example: gemm_test_01.txt): ";

            std::cin >> testFile;

            std::cout
                << "Enter block size: ";

            std::cin >> blockSize;

            if (blockSize <= 0)
            {
                std::cout
                    << "Error: block size must be greater than zero.\n";

                continue;
            }

            fs::path testPath =
                testsPath / testFile;

            if (!fileExists(testPath))
            {
                std::cout
                    << "Error: test file not found:\n"
                    << testPath.string()
                    << "\n";

                continue;
            }

            std::string command =
                quotePath(gemmExecutable)
                + " "
                + quotePath(testPath)
                + " "
                + std::to_string(blockSize);

            runCommand(command);
        }


        // ==================================================
        // 2. GEMM - ALL TESTS
        // ==================================================

        else if (choice == 2)
        {
            if (!fileExists(gemmExecutable))
            {
                std::cout
                    << "Error: GEMM executable not found:\n"
                    << gemmExecutable.string()
                    << "\n";

                continue;
            }

            const std::string tests[] =
            {
                "gemm_test_01.txt",
                "gemm_test_02.txt",
                "gemm_test_03.txt",
                "gemm_test_04.txt"
            };

            int blockSize;

            std::cout
                << "Enter block size: ";

            std::cin >> blockSize;

            if (blockSize <= 0)
            {
                std::cout
                    << "Error: block size must be greater than zero.\n";

                continue;
            }

            for (const std::string& test : tests)
            {
                fs::path testPath =
                    testsPath / test;

                if (!fileExists(testPath))
                {
                    std::cout
                        << "\nError: test file not found:\n"
                        << testPath.string()
                        << "\n";

                    continue;
                }

                std::cout
                    << "\n========== "
                    << test
                    << " ==========\n";

                std::string command =
                    quotePath(gemmExecutable)
                    + " "
                    + quotePath(testPath)
                    + " "
                    + std::to_string(blockSize);

                runCommand(command);
            }
        }


        // ==================================================
        // 3. CSR - SELECTED TEST
        // ==================================================

        else if (choice == 3)
        {
            if (!fileExists(csrExecutable))
            {
                std::cout
                    << "Error: CSR executable not found:\n"
                    << csrExecutable.string()
                    << "\n";

                continue;
            }

            std::string testFile;

            std::cout
                << "Enter CSR test file name "
                   "(example: csr_test_01.txt): ";

            std::cin >> testFile;

            fs::path testPath =
                testsPath / testFile;

            if (!fileExists(testPath))
            {
                std::cout
                    << "Error: test file not found:\n"
                    << testPath.string()
                    << "\n";

                continue;
            }

            fs::path expectedFile =
                testPath.stem().string()
                + "_expected.txt";

            fs::path expectedPath =
                testsPath / expectedFile;

            if (!fileExists(expectedPath))
            {
                std::cout
                    << "Error: expected file not found:\n"
                    << expectedPath.string()
                    << "\n";

                continue;
            }

            std::string command =
                quotePath(csrExecutable)
                + " "
                + quotePath(testPath)
                + " "
                + quotePath(expectedPath);

            runCommand(command);
        }


        // ==================================================
        // 4. CSR - ALL TESTS
        // ==================================================

        else if (choice == 4)
        {
            if (!fileExists(csrExecutable))
            {
                std::cout
                    << "Error: CSR executable not found:\n"
                    << csrExecutable.string()
                    << "\n";

                continue;
            }

            const std::string tests[] =
            {
                "csr_test_01.txt",
                "csr_test_02.txt",
                "csr_test_03.txt"
            };

            for (const std::string& test : tests)
            {
                fs::path testPath =
                    testsPath / test;

                if (!fileExists(testPath))
                {
                    std::cout
                        << "\nError: test file not found:\n"
                        << testPath.string()
                        << "\n";

                    continue;
                }

                fs::path expectedFile =
                    testPath.stem().string()
                    + "_expected.txt";

                fs::path expectedPath =
                    testsPath / expectedFile;

                if (!fileExists(expectedPath))
                {
                    std::cout
                        << "\nError: expected file not found:\n"
                        << expectedPath.string()
                        << "\n";

                    continue;
                }

                std::cout
                    << "\n========== "
                    << test
                    << " ==========\n";

                std::string command =
                    quotePath(csrExecutable)
                    + " "
                    + quotePath(testPath)
                    + " "
                    + quotePath(expectedPath);

                runCommand(command);
            }
        }


        // ==================================================
        // 5. BELLMAN-FORD - SELECTED TEST
        // ==================================================

        else if (choice == 5)
        {
            if (!fileExists(assignment02Executable))
            {
                std::cout
                    << "Error: Assignment 2 executable not found:\n"
                    << assignment02Executable.string()
                    << "\n";

                continue;
            }

            std::string testFile;

            std::cout
                << "Enter Bellman-Ford test file name "
                   "(example: bf_10.txt): ";

            std::cin >> testFile;

            fs::path testPath =
                assignment02TestsPath / testFile;

            if (!fileExists(testPath))
            {
                std::cout
                    << "Error: test file not found:\n"
                    << testPath.string()
                    << "\n";

                continue;
            }

            std::string command =
                quotePath(assignment02Executable)
                + " bellman-ford "
                + quotePath(testPath);

            runCommand(command);
        }


        // ==================================================
        // 6. BELLMAN-FORD - ALL TESTS
        // ==================================================

        else if (choice == 6)
        {
            if (!fileExists(assignment02Executable))
            {
                std::cout
                    << "Error: Assignment 2 executable not found:\n"
                    << assignment02Executable.string()
                    << "\n";

                continue;
            }

            const std::string tests[] =
            {
                "bf_10.txt",
                "bf_100.txt",
                "bf_10000.txt",
                "bf_50000.txt",
                "bf_100000.txt"
            };

            for (const std::string& test : tests)
            {
                fs::path testPath =
                    assignment02TestsPath / test;

                if (!fileExists(testPath))
                {
                    std::cout
                        << "\nError: test file not found:\n"
                        << testPath.string()
                        << "\n";

                    continue;
                }

                std::cout
                    << "\n========== "
                    << test
                    << " ==========\n";

                std::string command =
                    quotePath(assignment02Executable)
                    + " bellman-ford "
                    + quotePath(testPath);

                runCommand(command);
            }
        }


        // ==================================================
        // 7. FLOYD-WARSHALL - SELECTED TEST
        // ==================================================

        else if (choice == 7)
        {
            if (!fileExists(assignment02Executable))
            {
                std::cout
                    << "Error: Assignment 2 executable not found:\n"
                    << assignment02Executable.string()
                    << "\n";

                continue;
            }

            std::string testFile;

            std::cout
                << "Enter Floyd-Warshall test file name "
                   "(example: fw_10.txt): ";

            std::cin >> testFile;

            fs::path testPath =
                assignment02TestsPath / testFile;

            if (!fileExists(testPath))
            {
                std::cout
                    << "Error: test file not found:\n"
                    << testPath.string()
                    << "\n";

                continue;
            }

            std::string command =
                quotePath(assignment02Executable)
                + " floyd-warshall "
                + quotePath(testPath);

            runCommand(command);
        }


        // ==================================================
        // 8. FLOYD-WARSHALL - ALL TESTS
        // ==================================================

        else if (choice == 8)
        {
            if (!fileExists(assignment02Executable))
            {
                std::cout
                    << "Error: Assignment 2 executable not found:\n"
                    << assignment02Executable.string()
                    << "\n";

                continue;
            }

            const std::string tests[] =
            {
                "fw_10.txt",
                "fw_100.txt",
                "fw_500.txt",
                "fw_1000.txt",
                "fw_2000.txt"
            };

            for (const std::string& test : tests)
            {
                fs::path testPath =
                    assignment02TestsPath / test;

                if (!fileExists(testPath))
                {
                    std::cout
                        << "\nError: test file not found:\n"
                        << testPath.string()
                        << "\n";

                    continue;
                }

                std::cout
                    << "\n========== "
                    << test
                    << " ==========\n";

                std::string command =
                    quotePath(assignment02Executable)
                    + " floyd-warshall "
                    + quotePath(testPath);

                runCommand(command);
            }
        }


        // ==================================================
        // 9. EXIT
        // ==================================================

        else if (choice == 9)
        {
            std::cout
                << "Exiting wrapper.\n";

            break;
        }


        // ==================================================
        // INVALID MENU OPTION
        // ==================================================

        else
        {
            std::cout
                << "Error: invalid choice.\n";
        }
    }


    return 0;
}