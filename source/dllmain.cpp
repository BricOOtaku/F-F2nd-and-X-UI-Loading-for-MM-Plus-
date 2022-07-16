#include <Windows.h>
#include <sstream>
#include <string>

#include "detours.h"
#include "Helpers.h"
#include "Signature.h"
#include "toml.hpp"

int rnd;

bool randomLoading = false;
toml::table config;

//1.0.1 0x14040B6C0
//1.0.2 0x1406F2820
SIG_SCAN ( sigStartSong, "\x41\x54\x41\x55\x41\x57\x48\x83\xEC\x30\x4C\x8B\xFA\x45\x0F\xB6\xE8\x48\x63\x51\x08\x4C\x8B\xE1\x83\xFA\x04\x0F\x8D\x00\x00\x00\x00\x48\x89\x5C\x24\x00\x48\x8D\x0D\x00\x00\x00\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x48\x89\x7C\x24\x00\x4C\x89\x74\x24\x00\xE8\x00\x00\x00\x00\x48\x69\xEA\x00\x00\x00\x00\x48\x89\x44\x24\x00\x49\x03\xEC\x8B\x75\x48\x48\x8D\x4D\x30\x8B\x7D\x50\x4C\x8D\x75\x5C\x8B\x5D\x58\xE8\x00\x00\x00\x00\x89\x75\x48\x4C\x8D\x15\x00\x00\x00\x00\x48\x8B\x74\x24\x00\x89\x7D\x50\x48\x8B\x7C\x24\x00\x89\x5D\x58\x49\x63\x44\x24\x00\x49\x63\x0C\x24\x48\x8B\x6C\x24\x00\x48\x8D\x0C\x88\x41\x8B\x07\x45\x8B\x8C\x8A\x00\x00\x00\x00\x45\x8B\x84\x8A\x00\x00\x00\x00\x41\x8B\x94\x8A\x00\x00\x00\x00\x41\x89\x06\x41\x8B\x47\x04\x41\x89\x46\x04\x41\x8B\x47\x08\x41\x89\x46\x08\x41\x8B\x47\x0C\x41\x89\x46\x0C\x41\x8B\x47\x10\x41\x89\x46\x10\x41\x8B\x04\x24\x41\x89\x46\x14\x41\x8B\x44\x24\x00\x41\x89\x46\x18\x41\x0F\xB6\x47\x00\x41\x88\x46\x1C\x41\x6B\xC1\x64\x45\x89\x46\x24\x41\x89\x56\x28\x41\x89\x46\x20\x49\x63\x4F\x1C\x41\x89\x4E\x2C\x41\x0F\xB6\x47\x00\x41\x88\x46\x30\x84\xC0\x74\x1C\x49\x63\x04\x24\x49\x63\x84\x82\x00\x00\x00\x00\x41\x8B\x8C\x84\x00\x00\x00\x00\x33\xC0\x41\x89\x4E\x34\xEB\x38\x83\xF9\xFF\x74\x2D\x49\x63\x04\x24\x48\x8B\xD1\x4D\x63\x84\x82\x00\x00\x00\x00\x4A\x8D\x04\x81\x41\x8B\x8C\xC4\x00\x00\x00\x00\x4A\x8D\x04\x82\x41\x89\x4E\x34\x41\x8B\x84\xC4\x00\x00\x00\x00\xEB\x06\x33\xC0\x41\x89\x46\x34\x41\x89\x46\x38\x49\x8D\x56\x7C\x48\x8B\x44\x24\x00\x41\xB9\x00\x00\x00\x00\x0F\xB6\x80\x00\x00\x00\x00\x41\x88\x46\x3C\x41\x0F\xB6\x47\x00\x41\x88\x46\x3D\x41\x8B\x47\x24\x41\x89\x46\x40\x41\x0F\xB6\x47\x00\x41\x88\x46\x48\x41\x8B\x07\x41\x89\x44\x24\x00\x41\x8B\x47\x18\x41\x89\x44\x24\x00\x41\x8B\x47\x2C\x41\x89\x44\x24\x00\x41\x8B\x47\x2C\x41\x89\x46\x44\x41\x8B\x47\x30\x41\x89\x46\x4C\x41\x8B\x47\x48\x41\x89\x46\x64\x41\x8B\x47\x34\x41\x89\x46\x50\x41\x8B\x47\x4C\x41\x89\x46\x68\x41\x8B\x47\x38\x41\x89\x46\x54\x41\x8B\x47\x50\x41\x89\x46\x6C\x41\x8B\x47\x3C\x41\x89\x46\x58\x41\x8B\x47\x54\x41\x89\x46\x70\x41\x8B\x47\x40\x41\x89\x46\x5C\x41\x8B\x47\x58\x41\x89\x46\x74\x41\x8B\x47\x44\x41\x89\x46\x60\x41\x8B\x47\x5C\x4D\x2B\xFE\x41\x89\x46\x78\x49\x8D\x86\x00\x00\x00\x00\x0F\x1F\x40\x00\x48\x8D\x40\x05\x41\x0F\x10\x44\x17\x00\x48\x8D\x52\x14\x0F\x11\x42\xEC\x41\x8B\x4C\x17\x00\x89\x4A\xFC\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFB\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFC\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFD\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFE\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFF\x49\x83\xE9\x01\x75\xB3\x48\x8B\x5C\x24\x00\x45\x84\xED\x74\x09\x41\x8B\x4E\x08\xE8\x00\x00\x00\x00\x4C\x8B\x74\x24\x00\x48\x83\xC4\x30\x41\x5F\x41\x5D\x41\x5C\xC3\x48\x8B\xC4\x48\x89\x58\x18\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\x98\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x70\xB8\x0F\x29\x78\xA8\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x00\x48\x8B\xD9\x48\x63\x41\x08\x83\xF8\x04\x0F\x8D\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx?xxx????xxxx?xxxx?xxxx?xxxx?x????xxx????xxxx?xxxxxxxxxxxxxxxxxxxxx????xxxxxx????xxxx?xxxxxxx?xxxxxxx?xxxxxxxx?xxxxxxxxxxx????xxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxxxxxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx?xx????xxx????xxxxxxxx?xxxxxxxxxxxxxxxx?xxxxxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxx?xxxxxxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxxxxxxx?xxxxxxxxxx????xxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxx????xxxxxxxxxxxxxxxxxxx????" )

//1.0.1 0x140CC30F0
//1.0.2 0x140CC2138
SIG_SCAN ( sigLoadingBg, "\x6C\x6F\x61\x64\x69\x6E\x67\x5F\x62\x67\x00\x00\x00\x00\x00\x00", "xxxxxxxxxx??????" )

void InjectCode(void* address, const std::vector<uint8_t> data)
{
	const size_t byteCount = data.size() * sizeof(uint8_t);

	DWORD oldProtect;
	VirtualProtect(address, byteCount, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(address, data.data(), byteCount);
	VirtualProtect(address, byteCount, oldProtect, nullptr);
}

void load_bg(unsigned char v1, unsigned char v2)
{
	unsigned char zeroX = '0x0';
	std::stringstream sstream;
	sstream << std::hex << v1;
	sstream << std::hex << v2;
	std::string result = sstream.str();
	unsigned char V1 = zeroX + v1;
	unsigned char V2 = zeroX + v2;
	InjectCode((void*)sigLoadingBg(), { 0x6C, 0x6F, 0x61, 0x64, 0x69, 0x6E, 0x67, 0x5F, V1, V2 }); //loading_xx
}

void random_bg()
{
	srand(time(NULL));
	rnd = rand() % 40;
	int first = rnd / 10;
	rnd = rnd % 10;
	int second = rnd;
	load_bg(first, second);
}

HOOK(void, __fastcall, _StartSong, sigStartSong(), int* a1, __int64 a2, char a3)
{
	original_StartSong(a1, a2, a3);
	random_bg();
}

extern "C" __declspec(dllexport) void Init()
{
	printf("[X UI Loading for MM+] Initializing...\n");
	try
	{
		config = toml::parse_file("config.toml");
		try
		{
			randomLoading = config["Random_Loading"].value_or(false);
		}
		catch (std::exception& exception)
		{
			char text[1024];
			sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
			MessageBoxA(nullptr, text, "X UI Loading for MM+", MB_OK | MB_ICONERROR);
		}
	}
	catch (std::exception& exception)
	{
		char text[1024];
		sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
		MessageBoxA(nullptr, text, "X UI Loading for MM+", MB_OK | MB_ICONERROR);
	}

	if (randomLoading)
	{
		random_bg();
		INSTALL_HOOK(_StartSong);
	}
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
