#include "dllmain.hpp"

using namespace base;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    DisableThreadLibraryCalls(hinstDLL);
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // CHW::createDevice
        patch::writeMemory<DWORD>(0x48B095 + 3, 0x80000000);
        patch::writeMemory<UCHAR>(0x48B09C, 0xEB);
        // CHW::reset
        patch::writeMemory<DWORD>(0x48A879 + 6, 0x80000000);
        patch::writeMemory<UCHAR>(0x48A88D, 0xEB);
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}