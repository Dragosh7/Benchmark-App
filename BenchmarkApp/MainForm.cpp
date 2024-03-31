#include "MainForm.h" //#include <boost/asio.hpp>
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


void main(array<String^>^ args)
{
    
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	BenchmarkApp::MainForm form;
	Application::Run(% form);
   
    
}

