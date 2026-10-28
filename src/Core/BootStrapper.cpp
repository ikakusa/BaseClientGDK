//
// Created by ikasa on 2026/10/28.
//
#include "BootStrapper.h"

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reasonForCalling, LPVOID lpReserved)
{
    //EntryPoint
    switch (ul_reasonForCalling)
    {
    case DLL_PROCESS_ATTACH: {
            break;
        }
    case DLL_THREAD_ATTACH: {
            break;
        }
    case DLL_THREAD_DETACH:
        break;
    default: break;
    }
    return TRUE;
}