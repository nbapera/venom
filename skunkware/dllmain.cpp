#include <windows.h>
#include "dependencies/interfaces/interfaces.hpp"
#include "dependencies/utilities/csgo.hpp"
#include "core/config/config.hpp"
#include "hooks.hpp"
#include "core/menu/menu.hpp"

void unload(HMODULE hmod) {
    wndproc_release;
    /*
    menu.unload();
    events.release();*/
    hooks::release();
    FreeLibraryAndExitThread(hmod, 0);
}

void setup(HMODULE hmod) {
    interfaces::initialize();
    //window_initialize;
    wndproc_initialize;

    local_player = static_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

    hooks::initialize();
    //events.initialize();
    while (true) {
        Sleep(10);
        local_player = static_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
        if (GetAsyncKeyState(VK_DELETE) & 1) {
            unload(hmod);
        }
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)setup, hModule, NULL, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}