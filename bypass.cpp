#include <iostream>
#include <windows.h>

using namespace std;

class Bypass{
	
public:
	Bypass();
	~Bypass();
		
		
	bool Attach(dWORD dwPid);
	bool Read  (uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead = NULL);
	bool Write (uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten = NULL);
	
	
private:
	
	HANDLE m_hProcess = NULL;
		
	
};

Bypass::Bypass(){}


Bypass::~Bypass(){
	if (m_hProcess != NULL) CloseHandle(m_hProcess);
}



bool Bypass::Attach(dWORD dwPid){
	m_hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwPid);
	if (m_hProcess != NULL) return true; return false;
	
}


bool Bypass::Read(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesRead) {
	if (ReadProcessMemory(m_hProcess, (LPCVOID)lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead)) return true; return false;
	
	
}


bool Bypass::Write(uintptr_t lpBaseAddress, void* lpBuffer, SIZE_T nSize, SIZE_T* lpNumberOfBytesWritten) {
	if (WriteProcessMemory(m_hProcess, (LPVOID)lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten)) return true; return false;
	
	
}




int main() {
	DWORD pid = 0;
	cout << "PID: ";
	cin >> dec >> pid;
 
	Bypass* bypass = new Bypass();
	if (!bypass->Attach(pid)) {
		cout<<"OpenProcess failed. GetLastError = " <<dec <<GetLastError() <<endl;
		system("pause");
		return EXIT_FAILURE;
	}
 
	//----------------------------------------------------------------------
	uintptr_t memoryAddress = 0x0;
	cout<< "Memory address of the integer to read (in hexadecimal): 0x";
	cin>> hex >>memoryAddress;
	cout<< "Reading 0x" <<hex <<uppercase <<memoryAddress << " ..." <<endl;
 
	//----------------------------------------------------------------------
	int intRead = 0;
	if (!bypass->Read(memoryAddress, &intRead, sizeof(int))) {
		cout<< "ReadProcessMemory failed. GetLastError = " <<dec <<GetLastError() <<endl;
		system("pause");
		return EXIT_FAILURE;
	}
 
	cout<< "intRead = " <<dec <<intRead <<endl;
	cout<< "Press ENTER to quit." <<endl;
	
	
	
	system("pause > nul");
	delete bypass;
	return EXIT_SUCCESS;
}
 

