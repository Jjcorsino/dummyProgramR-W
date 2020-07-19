#include <Windows.h>
#include <iostream>
 
using namespace std;
 
int main() {
	DWORD pid = 0; 
	cout<< "Program id: ";
	cin>> dec >>pid; 
 
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	//---------------------------------------------------------------
	uintptr_t memoryAddress = 0x0;
	cout<< "Memory address of the integer to write(in hexadecimal): 0x";
	cin>> hex >> memoryAddress;
	cout<< "Writing 0x" << hex << uppercase << memoryAddress << " ..." <<endl;
	//----------------------------------------------------------------
	int intWrite = 98765;
	BOOL wpmReturn = WriteProcessMemory(hProcess, (LPVOID)memoryAddress, &intWrite, sizeof(int), NULL);
 	//----------------------------------------------------------------
	cout<< "Overwritten successfully: " << dec << intWrite <<endl;
	cout<< "Press ENTER to quit." <<endl;
	//-----------------------------------------------------------------
	
	system("pause > nul");
	return EXIT_SUCCESS;
}
