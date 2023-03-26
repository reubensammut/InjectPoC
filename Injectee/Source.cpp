#include <iostream>
#include <string>

#include <Windows.h>

using namespace std;

void print_usage(void)
{
	cout << "Usage:" << endl;
	cout << "\tload <dllname>\tLoads a dll into the process" << endl;
	cout << "\texit\t\tExit the process" << endl;
}

DWORD WINAPI myThread(LPVOID lpParameter)
{
	char* libPath = (char*)lpParameter;

	cout << "[Thread] - Trying to load library" << endl;

	HMODULE hLib = LoadLibraryA(libPath);

	FreeLibrary(hLib);

	delete[] libPath;

	return 0;
}


void load_library(string libpath)
{
	char* libPath = new char[libpath.length() + 1];
	libpath.copy(libPath, libpath.length(), 0);

	cout << "Trying to load [" << libpath << "]" << endl;

	DWORD fAttr = GetFileAttributesA(libPath);

	if (fAttr == INVALID_FILE_ATTRIBUTES)
	{
		cerr << "File [" << libpath << "] does not exist" << endl;
		print_usage();
		return;
	}
	else if (fAttr == FILE_ATTRIBUTE_DIRECTORY)
	{
		cerr << "Provided path [" << libpath << "] is a directory" << endl;
		print_usage();
		return;
	}

	HANDLE hThread = CreateThread(0, 0, myThread, libPath, 0, 0);

	if (hThread == NULL)
	{
		cerr << "Failed to create thread: " << GetLastError() << endl;
	}
}


int main(int argc, char* argv[])
{
	cout << "Welcome to the DLL loader" << endl << endl;
	print_usage();

	string input;

	while (1)
	{
		cout << "$ ";
		cout.flush();

		getline(cin, input);

		if (input.compare(0, 5, "load ") == 0)
		{
			load_library(input.substr(5));
		}
		else if (input.compare(0, 4, "exit") == 0)
		{
			break;
		}
		else
		{
			cout << "Unknown command" << endl;
			print_usage();
		}
	}
}