#include <Windows.h>
#include <iostream>

using namespace std;

void Inject(int pid, const char* path)
{
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, false, pid);

	LPVOID addr = VirtualAllocEx(hProc, NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	size_t nWritten = 0;

	WriteProcessMemory(hProc, addr, path, strlen(path), &nWritten);

	LPTHREAD_START_ROUTINE procAddr = (LPTHREAD_START_ROUTINE)&LoadLibraryA;

	CreateRemoteThread(hProc, NULL, 0, procAddr, addr, 0, NULL);
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " <pid> <path of lib>" << endl;
		exit(1);
	}

	int pid = atoi(argv[1]);

	Inject(pid, argv[2]);

	return 0;
}