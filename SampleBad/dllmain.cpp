// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <Windows.h>

void DoStuff(void)
{
    printf("Hello world from a bad DLL '(?_?)'\n\n");
    printf("Calling ExitThread\n");
    ExitThread(0);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DoStuff();
        break;
    case DLL_THREAD_ATTACH:
        printf("[SampleBad.dll] - DLL_THREAD_ATTACH\n");
        break;
    case DLL_THREAD_DETACH:
        printf("[SampleBad.dll] - DLL_THREAD_DETACH\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("[SampleBad.dll] - DLL_PROCESS_DETACH\n");
        break;
    }
    return TRUE;
}

