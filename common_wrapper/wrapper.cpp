#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <filesystem>
namespace fs = std::filesystem;

bool fileExists(const fs::path& path)
{
    return fs::exists(path);
}

void runCommand(const std::string& command)
{
    std::cout << "\nRunning:\n";
    std::cout << command << "\n\n";
    std::string executable;
    std::string arguments;

    if (!command.empty() && command[0] == '"')
    {
        size_t endQuote = command.find('"', 1);

        if (endQuote == std::string::npos)
        {
            std::cout << "Error: invalid command format.\n";
            return;
        }

        executable =
            command.substr(1, endQuote - 1);

        arguments =
            command.substr(endQuote + 1);
    }
    else
    {
        size_t space = command.find(' ');

        if (space == std::string::npos)
        {
            executable = command;
            arguments = "";
        }
        else
        {
            executable =
                command.substr(0, space);

            arguments =
                command.substr(space + 1);
        }
    }


    STARTUPINFOA startupInfo{};
    PROCESS_INFORMATION processInfo{};

    startupInfo.cb = sizeof(startupInfo);
    std::string commandLine = command;

    BOOL success = CreateProcessA(
        executable.c_str(),     
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

    // Wait until algorithm finishes
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
    std::cout << command << "\n\n";
}  


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
    std::cout << "9. Run MST (Kruskal + Prim) - selected test\n";
    std::cout << "10. Run MST (Kruskal + Prim) - all tests\n";
    std::cout << "11. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Enter your choice: ";
}


std::string quotePath(const fs::path& path)
{
    return "\"" + path.string() + "\"";
}


int main()
{
    fs::path wrapperDirectory =
        fs::current_path();

    fs::path repositoryRoot =
        wrapperDirectory.parent_path();


 fs::path assignmentPath =
        repositoryRoot / "assignment_01";

    fs::path driverPath =
        assignmentPath / "driver";

    fs::path testsPath =
        assignmentPath / "tests";
    fs::path assignment02Path =
        repositoryRoot / "assignment_02";

    fs::path assignment02DriverPath =
        assignment02Path / "driver";

    fs::path assignment02TestsPath =
        assignment02Path / "tests";
   fs::path assignment03Path =
        repositoryRoot / "assignment_03";

    fs::path assignment03DriverPath =
        assignment03Path / "driver";

    fs::path assignment03TestsPath =
        assignment03Path / "tests";
 fs::path gemmExecutable =
        driverPath / "gemm_test.exe";

    fs::path csrExecutable =
        driverPath / "csr_test.exe";

    fs::path assignment02Executable =
        assignment02DriverPath / "driver.exe";

    fs::path mstExecutable =
        assignment03DriverPath / "driver_mst.exe";

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
        else if (choice == 9)
{
            if (!fileExists(mstExecutable))
            {
                std::cout
                    << "Error: MST executable not found:\n"
                    << mstExecutable.string()
                    << "\n";

                continue;
            }

            std::string testFile;

            std::cout
                << "Enter MST test file name "
                   "(example: mst_10.txt): ";

            std::cin >> testFile;

            fs::path testPath =
                assignment03TestsPath / testFile;

            if (!fileExists(testPath))
            {
                std::cout
                    << "Error: test file not found:\n"
                    << testPath.string()
                    << "\n";

                continue;
            }

            std::string command =
                quotePath(mstExecutable)
                + " "
                + quotePath(testPath);

            runCommand(command);
        }
        else if (choice == 10)
        {
            if (!fileExists(mstExecutable))
            {
                std::cout
                    << "Error: MST executable not found:\n"
                    << mstExecutable.string()
                    << "\n";

                continue;
            }

            const std::string tests[] =
            {
                "mst_10.txt",
                "mst_100.txt",
                "mst_10000.txt",
                "mst_50000.txt",
                "mst_100000.txt"
            };

            for (const std::string& test : tests)
            {
                fs::path testPath =
                    assignment03TestsPath / test;

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
                    quotePath(mstExecutable)
                    + " "
                    + quotePath(testPath);

                runCommand(command);
            }
        }
        else if (choice == 11)
        {
            std::cout
                << "Exiting wrapper.\n";

            break;
        }
        else
        {
            std::cout
                << "Error: invalid choice.\n";
        }
    }


    return 0;
}