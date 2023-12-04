#include "client/minecraft/minecraft.h"
#include "modules/modules.h";
#include "chipirones/chipirones.h";
#include "gui/gui_main.h"

DWORD WINAPI main(PVOID instance) {
    jsize count;

    // Checks if there are any JVMs
    if (JNI_GetCreatedJavaVMs(&lc->vm, 1, &count) != JNI_OK || count == 0) return 0;
    // Checks if the version is 1.8
    jint res = lc->vm->GetEnv((void**)&lc->env, JNI_VERSION_1_8);

    // If there are no JNI interface attached it attached a new one.
    if (res == JNI_EDETACHED) res = lc->vm->AttachCurrentThread((void**)&lc->env, nullptr);
    if (lc->env != nullptr) {
        lc->load_classes(); // Load classes into the Lunar Class.
        auto mc = std::make_unique<cminecraft>();
        CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(clicker::handle), 0, 0, nullptr));
        CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(gui::start), 0, 0, nullptr));
        CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(chipirones::check_keybinds), 0, 0, nullptr));

        while (true) {
            if (GetAsyncKeyState(VK_DELETE)) {
                cheat->thread_stopped = true;
            }

            if (cheat->thread_stopped) {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                break;
            }
            
            reach::handle(mc);

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);

    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    DisableThreadLibraryCalls(hModule);

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main, hModule, 0, nullptr));
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:

        break;
    }
    return TRUE;
}

