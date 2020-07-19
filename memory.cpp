#include <Windows.h>
#include <iostream>
 
using namespace std;
 
int main() {
	DWORD pid = 0; 
	cout<< "PID: ";
	cin>> dec >>pid; 
 
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	//---------------------------------------------------------------
	uintptr_t memoryAddress = 0x0;
	cout<< "Memory address of the integer to read (in hexadecimal): 0x";
	cin>> hex >> memoryAddress;
	cout<< "Reading 0x" << hex << uppercase << memoryAddress << " ..." <<endl;
	//----------------------------------------------------------------
	int intRead = 0;
	BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID)memoryAddress, &intRead, sizeof(int), NULL);
 	//----------------------------------------------------------------
	cout<< "intRead = " << dec << intRead <<endl;
	cout<< "Press ENTER to quit." <<endl;
	//-----------------------------------------------------------------
	
	system("pause > nul");
	return EXIT_SUCCESS;
}
