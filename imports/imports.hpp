#pragma once
/*░█████╗░░██╗░░░░░░░██╗███╗░░██╗███████╗██████╗░  ██████╗░██████╗░░█████╗░░░░░░██╗███████╗░█████╗░████████╗
  ██╔══██╗░██║░░██╗░░██║████╗░██║██╔════╝██╔══██╗  ██╔══██╗██╔══██╗██╔══██╗░░░░░██║██╔════╝██╔══██╗╚══██╔══╝
  ██║░░██║░╚██╗████╗██╔╝██╔██╗██║█████╗░░██████╔╝  ██████╔╝██████╔╝██║░░██║░░░░░██║█████╗░░██║░░╚═╝░░░██║░░░
  ██║░░██║░░████╔═████║░██║╚████║██╔══╝░░██╔══██╗  ██╔═══╝░██╔══██╗██║░░██║██╗░░██║██╔══╝░░██║░░██╗░░░██║░░░
  ╚█████╔╝░░╚██╔╝░╚██╔╝░██║░╚███║███████╗██║░░██║  ██║░░░░░██║░░██║╚█████╔╝╚█████╔╝███████╗╚█████╔╝░░░██║░░░
░  ╚════╝░░░░╚═╝░░░╚═╝░░╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░╚═╝░╚════╝░░╚════╝░╚══════╝░╚════╝░░░░╚═╝░░░

				𝗵𝘁𝘁𝗽𝘀://𝘃𝗸.𝗰𝗼𝗺/𝗰𝗹𝗲𝗮𝗿𝗵𝗲𝗮𝗱𝗲𝗮𝗱𝘄𝗳
*/
#ifndef imports_hpp
#define imports_hpp


int f_get_async_key_state(int vk) {
	return v_import<int>(XORWSTR(L"user32"), XORWSTR(L"GetAsyncKeyState"), vk);
}
int f_get_key_state(int vk)
{
	return v_import<int>(XORWSTR(L"user32"), XORWSTR(L"GetKeyState"), vk);
}
namespace crt
{
	void* f_free(void* memblock)
	{
		return v_import<void*>(XORWSTR(L"msvcrt"), XORWSTR(L"free"), memblock);
	}
	void* f_malloc(size_t size)
	{
		return v_import<void*>(XORWSTR(L"msvcrt"), XORWSTR(L"malloc"), size);
	}
	float f_cosf(float x)
	{
		return v_import<float>(XORWSTR(L"msvcrt"), XORWSTR(L"cosf"), x);
	}

	float f_sinf(float x)
	{
		return v_import<float>(XORWSTR(L"msvcrt"), XORWSTR(L"sinf"), x);
	}
	__forceinline size_t strlen(const char* const string)
	{
		size_t length = 0;

		while (string[length] != '\0')
			length++;

		return length;
	}

	int powInt(int x, int y)
	{
		for (int i = 0; i < y; i++)
		{
			x *= 10;
		}
		return x;
	}

	int parseInt(char* chars)
	{
		int sum = 0;
		int len = strlen(chars);
		for (int x = 0; x < len; x++)
		{
			int n = chars[len - (x + 1)] - '0';
			sum = sum + powInt(n, x);
		}
		return sum;
	}
	auto itoa(int number, char* destination, int base) -> char*
	{
		int count = 0;
		do
		{
			int digit = number % base;
			destination[count++] = (digit > 9) ? digit - 10 + 'A' : digit + '0';
		} while ((number /= base) != 0);
		destination[count] = 0;
		int i;
		for (i = 0; i < count / 2; ++i)
		{
			wchar_t symbol = destination[i];
			destination[i] = destination[count - i - 1];
			destination[count - i - 1] = symbol;
		}
		return destination;
	}
}
char* __cdecl m_strstr(const char* str1, const char* str2)
{
	char* cp = (char*)str1;
	char* s1, * s2;

	if (!*str2)
		return((char*)str1);

	while (*cp)
	{
		s1 = cp;
		s2 = (char*)str2;

		while (*s1 && *s2 && !(*s1 - *s2))
			s1++, s2++;

		if (!*s2)
			return(cp);

		cp++;
	}

	return(0);
}
char* __cdecl m_strchr(const char* string, int ch)
{
	while (*string && *string != (char)ch)
		string++;
	if (*string == (char)ch)
		return((char*)string);
	return(0);
}
int m_strcmp(const char* src, const char* dst)
{
	int ret = 0;
	unsigned char* p1 = (unsigned char*)src;
	unsigned char* p2 = (unsigned char*)dst;
	while (!(ret = *p1 - *p2) && *p2)
		++p1, ++p2;

	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;

	return ret;
}

char* m_strcpy(char* dest, const char* src)
{
	char* ret = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return ret;
}

unsigned m_strlen(const char* str)
{
	int cnt = 0;
	if (!str)
		return 0;
	for (; *str != '\0'; ++str)
		++cnt;
	return cnt;
}

unsigned m_strlen_w(const wchar_t* str)
{
	int cnt = 0;
	if (!str)
		return 0;
	for (; *str != '\0'; ++str)
		++cnt;
	return cnt;
}
auto m_itoa(int number, char* destination, int base) -> char*
{
	int count = 0;
	do
	{
		int digit = number % base;
		destination[count++] = (digit > 9) ? digit - 10 + 'A' : digit + '0';
	} while ((number /= base) != 0);
	destination[count] = 0;
	int i;
	for (i = 0; i < count / 2; ++i)
	{
		wchar_t symbol = destination[i];
		destination[i] = destination[count - i - 1];
		destination[count - i - 1] = symbol;
	}
	return destination;
}
auto m_memcpy(void* dest, void* src, unsigned int len) -> void*
{
	unsigned int i;
	char* char_src = (char*)src;
	char* char_dest = (char*)dest;
	for (i = 0; i < len; i++) {
		char_dest[i] = char_src[i];
	}
	return dest;
}
auto m_memset(void* dest, char c, unsigned int len) -> void*
{
	unsigned int i;
	unsigned int fill;
	unsigned int chunks = len / sizeof(fill);
	char* char_dest = (char*)dest;
	unsigned int* uint_dest = (unsigned int*)dest;
	fill = (c << 24) + (c << 16) + (c << 8) + c;

	for (i = len; i > chunks * sizeof(fill); i--) {
		char_dest[i - 1] = c;
	}

	for (i = chunks; i > 0; i--) {
		uint_dest[i - 1] = fill;
	}

	return dest;
}
auto m_atoi(const char* str) -> int
{
	int sign = 1, base = 0, i = 0;

	// if whitespaces then ignore.
	while (str[i] == ' ')
	{
		i++;
	}

	// sign of number
	if (str[i] == '-' || str[i] == '+')
	{
		sign = 1 - 2 * (str[i++] == '-');
	}

	// checking for valid input
	while (str[i] >= '0' && str[i] <= '9')
	{
		// handling overflow test case
		if (base > 2147483647 / 10
			|| (base == 2147483647 / 10
				&& str[i] - '0' > 7))
		{
			if (sign == 1)
				return 2147483647;
			else
				return (-2147483647 - 1);
		}
		base = 10 * base + (str[i++] - '0');
	}
	return base * sign;
}
static PVOID m_RtlSecureZeroMemory(PVOID  ptr, SIZE_T cnt) {
	return m_memset(ptr, 0, cnt);
}



#endif // !imports_hpp
