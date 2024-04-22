#pragma once
#include <Windows.h>
#include <winternl.h>
#include <cstdint>

typedef struct LDR_DATA_TABLE_ENTRY_FIX
{
	PVOID Reserved1[2];
	LIST_ENTRY InMemoryOrderLinks;
	PVOID Reserved2[2];
	PVOID DllBase;
	PVOID Reserved3[1];
	ULONG64 SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	PVOID Reserved5[2];
#pragma warning(push)
#pragma warning(disable: 4201)
	union
	{
		ULONG CheckSum;
		PVOID Reserved6;
	} DUMMYUNIONNAME;
#pragma warning(pop)
	ULONG TimeDateStamp;
};

#define to_lower(str) ((str >= 'A' && str <= 'Z') ? (str + 32) : str)
////////////////////////////////////////////////

template <typename str_type>
__declspec(noinline) constexpr unsigned short hash_str(str_type data_str, int len)
{
	unsigned short crc32 = 0xFFFF;
	while (len--)
	{
		auto cur_char = *data_str++;
		if (!cur_char)
			break;

		crc32 ^= to_lower(cur_char) << 8;
		for (int i = 0; i < 8; i++)
			crc32 = crc32 & 0x8000 ? (crc32 << 1) ^ 0x8408 : crc32 << 1;

	} return crc32;
}

template <typename str_type, typename in_str_type>
bool str_cmp(str_type str, in_str_type in_str, bool b_force)
{
	if (!str || !in_str)
		return false;

	wchar_t c1, c2;

	do
	{
		c1 = *str++;
		c2 = *in_str++;
		c1 = to_lower(c1);
		c2 = to_lower(c2);

		if (!c1 && (b_force ? !c2 : 1))
			return true;

	} while (c1 == c2); return false;
}
template <typename str_type>
PBYTE gmb(str_type module_name)
{
	PPEB_LDR_DATA p_peb = ((PTEB)__readgsqword(FIELD_OFFSET(NT_TIB, Self)))->ProcessEnvironmentBlock->Ldr;
	for (PLIST_ENTRY current_entry = p_peb->InMemoryOrderModuleList.Flink; current_entry != &p_peb->InMemoryOrderModuleList; current_entry = current_entry->Flink)
	{
		LDR_DATA_TABLE_ENTRY_FIX* p_entry = CONTAINING_RECORD(current_entry, LDR_DATA_TABLE_ENTRY_FIX, InMemoryOrderLinks);
		if (!module_name || str_cmp(module_name, p_entry->BaseDllName.Buffer, false))
			return (PBYTE)p_entry->DllBase;

	} return nullptr;
}
unsigned __int64 ugmd(const wchar_t* module_name)
{
	return (unsigned __int64)gmb(module_name);
}

#define get_module_base   gmb
#define u_get_module_base ugmd
#define in_range(x, a, b) (x >= a && x <= b) 
#define get_bits(x) (in_range((x&(~0x20)),'A','F')?((x&(~0x20))-'A'+0xA):(in_range(x,'0','9')?x-'0':0))
#define get_byte(a, b) (get_bits(a) << 4 | get_bits(b))
uint64_t get_absolute_address(uint64_t instruction_addr, uint64_t instruction_size, long relative)
{
	return instruction_addr + relative + instruction_size;
}

uint64_t get_absolute_address(uint64_t instruction_addr)
{
	if (instruction_addr < 0x1000)
		return 0;

	uint16_t instruction_size = 6;
	uint16_t offset_to_relative = 2;

	auto opcode = (unsigned char*)(instruction_addr);

	if (opcode[0] >= 0x48 && opcode[0] <= 0x4F) // 64 bit operand
	{
		instruction_size++;
		offset_to_relative++;
	}
	else if (opcode[0] == 0x80) // cmp
	{
		instruction_size = 7;
		offset_to_relative = 2;
	}
	else if (opcode[0] == 0xE8) // call
	{
		instruction_size = 5;
		offset_to_relative = 1;
	}

	return get_absolute_address(instruction_addr, instruction_size, *reinterpret_cast<long*>(instruction_addr + offset_to_relative));
}

PBYTE find_pattern(const char* pattern, const wchar_t* module_name = nullptr)
{
	unsigned __int64 start_address = u_get_module_base(module_name);
	if (!start_address)
		return 0;

	PBYTE first_match = nullptr;
	const char* current_pattern = pattern;

	PBYTE end_address = (PBYTE)(start_address + ((PIMAGE_NT_HEADERS)(start_address + ((PIMAGE_DOS_HEADER)start_address)->e_lfanew))->OptionalHeader.SizeOfImage);
	for (PBYTE p_current = (PBYTE)start_address; p_current < end_address; p_current++)
	{
		char pattern_byte = current_pattern[0];
		if (!pattern_byte)
			return first_match;

		if (pattern_byte == '\?' || *(BYTE*)p_current == get_byte(pattern_byte, current_pattern[1]))
		{
			if (!first_match) first_match = p_current;
			if (!current_pattern[2])
				return first_match;

			((pattern_byte == '\?') ? (current_pattern += 2) : (current_pattern += 3));
		}
		else
		{
			current_pattern = pattern;
			first_match = nullptr;
		}
	}

	return 0;
}

#define const_str_len(str) ((sizeof(str) - sizeof(str[0])) / sizeof(str[0]))
#define const_hash_str(str) [](){ constexpr unsigned short crc = hash_str(str, const_str_len(str)); return crc; }()

template <typename ptr_type>
__forceinline ptr_type encrypt_ptr(ptr_type ptr)
{
	typedef union
	{
		struct
		{
			unsigned short key_1;
			unsigned short key_2;
			unsigned short key_3;
			unsigned short key_4;
		}; unsigned long long key;
	} crypt_data;

	crypt_data key
	{
		const_hash_str(__TIME__),
		const_hash_str(__DATE__),
		const_hash_str(__TIMESTAMP__),
		const_hash_str(__TIMESTAMP__)
	};

	return (ptr_type)((DWORD64)ptr ^ key.key);
}

#define e_ptr(ptr) encrypt_ptr(ptr)
////////////////////////////////////////////////

////////////////////////////////////////////////
PVOID return_address_stub = 0;
extern "C" void* _spoofer_stub();

template<typename ret = void, typename _first = void*, typename _second = void*, typename _third = void*, typename _fourth = void*, typename... _stack>
__forceinline ret spoof_call(void* function, _first a1 = _first{}, _second a2 = _second{}, _third a3 = _third{}, _fourth a4 = _fourth{}, _stack... args)
{
	struct shell_params
	{
		const void* a1;
		void* a2;
		void* a3;
	};

	shell_params call_ctx =
	{
		e_ptr(return_address_stub),
		function,
		nullptr
	};

	typedef ret(*m_shell)(_first, _second, _third, _fourth, PVOID, PVOID, _stack...);
	return ((m_shell)&_spoofer_stub)(a1, a2, a3, a4, &call_ctx, nullptr, args...);
}

__forceinline void set_spoof_stub(PVOID R15_Stub)
{
	return_address_stub = e_ptr(R15_Stub);
}

template<typename ret = void, typename... args>
__forceinline ret f_spoof_virtual(PVOID base, int index, args... add_args)
{
	return spoof_call<ret>((*(PVOID**)base)[index / 8], base, add_args...);
}

#define f_spoof spoof_call
#define v_spoof f_spoof_virtual

PVOID get_export_address(PBYTE h_dll, const wchar_t* name)
{
	PIMAGE_NT_HEADERS nt_head = (PIMAGE_NT_HEADERS)(h_dll + ((PIMAGE_DOS_HEADER)h_dll)->e_lfanew);
	PIMAGE_EXPORT_DIRECTORY exp_dir = (PIMAGE_EXPORT_DIRECTORY)(h_dll + nt_head->OptionalHeader.DataDirectory[0].VirtualAddress);

	for (unsigned long i = 0; i < exp_dir->NumberOfNames; i++)
	{
		unsigned short ordinal = ((unsigned short*)(h_dll + exp_dir->AddressOfNameOrdinals))[i];
		const char* exp_name = (const char*)h_dll + ((unsigned long*)(h_dll + exp_dir->AddressOfNames))[i];

		if (str_cmp(name, exp_name, true))
			return (PVOID)(h_dll + ((unsigned long*)(h_dll + exp_dir->AddressOfFunctions))[ordinal]);

	} return nullptr;
}

template <typename t, typename... args>
t c_import(const wchar_t* module_name, const wchar_t* function_name, args... add_args)
{
	PVOID f_addr = nullptr;
	if (!f_addr)
		f_addr = e_ptr(get_export_address(gmb(module_name), function_name));

	return f_spoof<t>(e_ptr(f_addr), add_args...);
}

#define call_import(Mod, Name, ...) [&](){ PVOID f_addr = nullptr; \
		if (!f_addr) f_addr = e_ptr(get_export_address(gmb(Mod), Name)); \
		return f_spoof<p_void>(e_ptr(f_addr), __VA_ARGS__); \
	}()

#define call_import_f(Mod, Name, ...) [&](){ PVOID f_addr = nullptr; \
		if (!f_addr) f_addr = e_ptr(get_export_address(gmb(Mod), Name)); \
		return f_spoof<f32>(e_ptr(f_addr), __VA_ARGS__); \
	}()

#define call_import_f64(Mod, Name, ...) [&](){ PVOID f_addr = nullptr; \
		if (!f_addr) f_addr = e_ptr(get_export_address(gmb(Mod), Name)); \
		return f_spoof<f64>(e_ptr(f_addr), __VA_ARGS__); \
	}()

#define v_import c_import
