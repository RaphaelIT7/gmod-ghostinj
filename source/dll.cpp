#include <GarrysMod/Lua/LuaInterface.h>
#include <Platform.hpp>
#include <stdio.h>

void Load(bool TInit)
{
	Msg("--- GhostInj loading ---\n");

	// Do your stuff here

	Msg("--- GhostInj loaded ---\n");
}

void Unload(bool TShutdown)
{
	Msg("--- GhostInj unloading ---\n");

	// Do your stuff here

	Msg("--- GhostInj unloaded ---\n");
}

#if SYSTEM_WINDOWS
#include <windows.h>
BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpvReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch( fdwReason ) 
	{ 
	case DLL_PROCESS_ATTACH:
		Load(false);
		break;

	case DLL_THREAD_ATTACH:
		Load(true);
		break;

	case DLL_THREAD_DETACH:
		Unload(true);
		break;

	case DLL_PROCESS_DETACH:
		if (lpvReserved != nullptr)
		{
			break;
		}

		Unload(false);
		break;
	}

	return TRUE;
}

#else
typedef void (*plugin_main)();
void __attribute__((constructor)) SO_load()
{
	Load(false); // Idk how to check if it's loaded from another thread.
}

typedef void (*plugin_main)();
void __attribute__((destructor)) SO_unload()
{
	Unload(false); // Idk how to check if it's loaded from another thread.
}
#endif