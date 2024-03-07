#include "dllmain.hpp"

using namespace base;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    DisableThreadLibraryCalls(hinstDLL);
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        constexpr std::pair<std::string_view, std::string_view> addrs[4]{
            {"\xC7\x46\x00\x00\x00\x00\x00\x75\x18", "XX?????XX"},
            {"\x75\x18\x8B\x43\x24", "XXXXX"},
            {"\xC7\x87\x00\x00\x00\x00\x00\x00\x00\x00\x8D\x44\x00\x01", "XX????????XXXX"},
            {"\x75\x1A\x8B\x4F\x24", "XXXXX"}
        };

        // CHW::createDevice
        patch::writeMemory<DWORD>(patch::FindPattern(nullptr, addrs[0].first.data(), addrs[0].second.data()) + 3, 0x80000000);
        patch::writeMemory<UCHAR>(patch::FindPattern(nullptr, addrs[1].first.data(), addrs[1].second.data()), 0xEB);
        // CHW::reset
        patch::writeMemory<DWORD>(patch::FindPattern(nullptr, addrs[2].first.data(), addrs[2].second.data()) + 6, 0x80000000);
        patch::writeMemory<UCHAR>(patch::FindPattern(nullptr, addrs[3].first.data(), addrs[3].second.data()), 0xEB);
    }
    return TRUE;
}