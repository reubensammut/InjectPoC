// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>


void DoStuff(void)
{
    printf("Hello world from a good DLL :)\n\n");
    printf("Returning normally\n");
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
        printf("[SampleGood.dll] - DLL_THREAD_ATTACH\n");
        break;
    case DLL_THREAD_DETACH:
        printf("[SampleGood.dll] - DLL_THREAD_DETACH\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("[SampleGood.dll] - DLL_PROCESS_DETACH\n");
        break;
    }
    return TRUE;
}

