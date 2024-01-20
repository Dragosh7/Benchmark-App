#include "ProgressForm.h" 
#include <iostream>
#include <chrono> //#include <Windows.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdio> // Pentru stergerea fisierului creat
#include <random>
#include <cmath>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <algorithm>  
#include <thread>
#pragma comment(lib, "ws2_32.lib")
using namespace System;
using namespace System::Windows::Forms;

std::string getCPUInfo() {
    std::ostringstream resultStream;

    //https://stackoverflow.com/questions/850774/how-to-determine-the-hardware-cpu-and-ram-on-a-machine
    int CPUInfo[4] = { -1 };
    unsigned   nExIds, i = 0;
    char CPUBrandString[0x40];
    // Get the information associated with each extended ID.
    __cpuid(CPUInfo, 0x80000000);
    nExIds = CPUInfo[0];
    for (i = 0x80000000; i <= nExIds; ++i)
    {
        __cpuid(CPUInfo, i);
        // Interpret CPU brand string
        if (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
    }
    //string includes manufacturer, model and clockspeed
    resultStream << "CPU Type: " << CPUBrandString << std::endl;


    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    resultStream << "Number of Cores: " << sysInfo.dwNumberOfProcessors << std::endl;

    return resultStream.str();
}
std::string BenchmarkApp::ProgressForm::info()
{
    std::ostringstream resultStream;

    resultStream << getCPUInfo();

    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&memoryStatus)) {
        // Dimensiunea totală a memoriei RAM
        long long totalMemory = memoryStatus.ullTotalPhys;

        resultStream << "Random Access Memory: " << (totalMemory / 1024) / 1024 / 1000 << "GB" << std::endl;
    }
    else {
        resultStream << "Eroare la accesarea informațiilor despre memorie\n";
    }

    // Convert the std::ostringstream to a System::String
    return resultStream.str();
}

double performNetworkTest(const char* host, const char* path)
{
    // Create a socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    // Resolve server address
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    addrinfo* result = nullptr;
    if (getaddrinfo(host, "http", &hints, &result) != 0)
    {
        std::cerr << "Failed to resolve server address." << std::endl;
        closesocket(clientSocket);
        return -1;
    }

    // Connect to the server
    if (connect(clientSocket, result->ai_addr, static_cast<int>(result->ai_addrlen)) == SOCKET_ERROR)
    {
        std::cerr << "Failed to connect to the server." << std::endl;
        freeaddrinfo(result);
        closesocket(clientSocket);
        return -1;
    }

    // Free the result structure
    freeaddrinfo(result);

    // HTTP GET request
    std::string httpRequest = "GET " + std::string(path) + " HTTP/1.1\r\n"
        "Host: " + std::string(host) + "\r\n"
        "Cache-Control: no-cache\r\n"
        "Connection: close\r\n\r\n";

    // Start clock measurement
    auto start = std::chrono::high_resolution_clock::now();

    // Send the HTTP request
    if (send(clientSocket, httpRequest.c_str(), static_cast<int>(httpRequest.length()), 0) == SOCKET_ERROR)
    {
        std::cerr << "Failed to send HTTP request." << std::endl;
        closesocket(clientSocket);
        return -1;
    }

    // Receive the server's response
    char buffer[4096];
    std::ostringstream response;

    while (true)
    {
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0)
        {
            response.write(buffer, bytesRead);
        }
        else if (bytesRead == 0)
        {
            // Connection closed by the server
            break;
        }
        else
        {
            std::cerr << "Error while receiving data." << std::endl;
            closesocket(clientSocket);
            return -1;
        }
    }

    // Stop clock measurement
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Print the transfer time
    double transferTime = duration.count() / 1e6; // Convert microseconds to seconds
    std::cout << "Total transfer time to " << host << path << ": " << transferTime << " seconds\n";

    // Clean up
    closesocket(clientSocket);
    return transferTime;
}
double BenchmarkApp::ProgressForm::networkMeasurement()
{
    // Initialize WinSock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to initialize WinSock." << std::endl;
        return 0;
    }

    double result = 0;

    // First Test
    result += performNetworkTest("www.google.com", "/search?q=tesla+:apple.com&tbm=vid&hl=fr");

    // Second Test
    result += performNetworkTest("www.google.com", "/search?q=bmw+-bmw.ro&tbs=qdr:y%2Citp:animated&hl=de");

    // Third Test
    result += performNetworkTest("www.google.com", "/search?q=cars+for+sale+type=pdf&tbm=isch&tbs=qdr:y%2Citp:clipart&hl=es");
    
    // 4th Test
    result += performNetworkTest("www.google.com", "/search?q=cars+for+rent+type=pdf&tbm=isch&tbs=qdr:y%2Citp:clipart&hl=ro");

    std::cout << "Total transfer network time " << ": " << result / 4.0f << " seconds\n";


    // Clean up
    WSACleanup();

    return result;
}

std::string generateRandomString(int length) {
    //https://inversepalindrome.com/blog/how-to-create-a-random-string-in-cpp
    const std::string characters = "0123456789abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXY";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, characters.size() - 1);

    std::string randomString;
    for (int i = 0; i < length; ++i) {
        randomString += characters[distribution(generator)];
    }

    return randomString;
}
std::string generateRandomText() {
    // Function to generate a text with x lines of random letters, numbers, and spaces

    const int lines = 1024 * 1024;// 1MB
    const int charactersPerLine = 100;

    std::string randomText;
    for (int i = 0; i < lines; ++i) {
        randomText += generateRandomString(charactersPerLine) + "\n";
    }

    return randomText;
}
double writeToFile(const std::string& filename) {

    const std::string contentToWrite =
        "This is a file write and read test!\n"
        "It involves writing and reading an amount of data to simulate a challenging scenario.";

    std::string content = generateRandomText();

    auto start = std::chrono::high_resolution_clock::now();

    std::ofstream outFile(filename);

    if (outFile.is_open()) {
        outFile << content;
        outFile.close();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "File '" << filename << "' written successfully. Time: "
            << duration.count() / 1e6 << " seconds." << std::endl;
        return (duration.count() / 1e6);
    }
    else {
        std::cerr << "Unable to open file '" << filename << "' for writing." << std::endl;
        return -1;
    }
}
double readFromFile(const std::string& filename) {
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inFile(filename);
    std::string content;

    if (inFile.is_open()) {
        std::string line;
        while (getline(inFile, line)) {
            content += line + "\n";
        }
        inFile.close();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "File '" << filename << "' read successfully. Time: "
            << duration.count() / 1e6 << " seconds." << std::endl;

        std::remove(filename.c_str());
        std::cout << "File '" << filename << "' was deleted successfully.\n";
        return (duration.count() / 1e6);
    }
    else {
        std::cerr << "Unable to open file '" << filename << "' for reading." << std::endl;
        return -1;
    }

    //return content; for verifying the function ( std::string)
}
double BenchmarkApp::ProgressForm::dataMeasurement()
{
    const std::string filename = "testfile.txt";
    double x = 0;
    // Write to file
    x+=writeToFile(filename);

    // Read from file 
    x+=readFromFile(filename);


    // Testing if content was written and displaying it
    // std::string contentRead = readFromFile(filename);
    //std::cout << "Content read from file:\n" << contentRead << std::endl;
    return x;
}

std::string addTwoStrings(const std::string& str1, const std::string& str2) {
    std::string result;
    int carry = 0;

    int len1 = str1.length();
    int len2 = str2.length();
    int maxSize = (((len1) > (len2)) ? (len1) : (len2));

    for (int i = 0; i < maxSize || carry; ++i) {
        int digit1 = (i < len1) ? (str1[len1 - i - 1] - '0') : 0;
        int digit2 = (i < len2) ? (str2[len2 - i - 1] - '0') : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;

        result.push_back((sum % 10) + '0');
    }

    std::reverse(result.begin(), result.end());
    return result;
}
void fib(int a) {
    //int a;
    //std::cout << "Find how many numbers? \n";
    //std::cin >> a;

    std::string x = "0";
    std::string y = "1";
    std::string z;

    for (int b = 0, c = 0; b < a; ++b) {
        if (b % 3 == 0) {
            ++c;
            //std::cout << "\n" << c << ") ";
        }

        //std::cout << x << "  ";
        z = y;
        y = x;
        x = addTwoStrings(x, z);

        if (x.length() < z.length()) {
            std::cout << "\nMaxed out at " << b + 1;
            break;
        }
    }
    //std::cout << x << "  ";
}


double cpuTime = 0;
void calculateFibInThread(int n) {

    auto start = std::chrono::high_resolution_clock::now();
    fib(50000);//10000

    //time taken by each thread
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Thread nr:" << n << ", Time: " << duration.count() / 1e6 << " seconds" << std::endl;
    cpuTime+= (duration.count() / 1e6);
}
double BenchmarkApp::ProgressForm::cpuMeasurement() {
    std::vector<std::thread> threads;
    unsigned int numThreads = std::thread::hardware_concurrency();

    for (int i = 0; i < numThreads; ++i) {

        threads.emplace_back(calculateFibInThread, i);
    }

    // Join threads; pentru asigurarea ca isi termina executia
    for (auto& thread : threads) {
        thread.join();
    }
    return (cpuTime / numThreads);
}

