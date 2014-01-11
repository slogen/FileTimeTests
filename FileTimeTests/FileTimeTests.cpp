#include <Windows.h>
#include <WinBase.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	// Input to conversion: 2014-01-10 20:58:18.789
	SYSTEMTIME st;
	st.wYear = 2014;
	st.wMonth = 01;
	st.wDayOfWeek = 5;
	st.wDay = 10;
	st.wHour = 20;
	st.wMinute = 58;
	st.wSecond = 18;
	st.wMilliseconds = 789;

	union { 
		// We cannot convert between FILETIME and INT64 by casting because of alignment.
		// FILETIME can be 4-byte aligned, INT64 requires 8-byte alignment.
		FILETIME AsFileTime;
		INT64 AsInt64;
	} value;

	// Standard conversion from SYSTEMTIME to FILETIME
	SystemTimeToFileTime(&st, &value.AsFileTime);
	// Look at the int64 converted value as bytes
	unsigned char *ft_bytes = (unsigned char*)&value.AsInt64;

	printf("DateTime: %02hu-%02hu-%02hu %02hu:%02hu:%02hu.%hu\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	printf("100ns: %lld == 0x%llx\n", value.AsInt64, value.AsInt64);
	printf("mem: 0x%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx\n", ft_bytes[0], ft_bytes[1], ft_bytes[2], ft_bytes[3], ft_bytes[4], ft_bytes[5], ft_bytes[6], ft_bytes[7]);
	return 0;

	/*
		Generates the following output:
DateTime: 2014-01-10 20:58:18.789
100ns: 130338610987890000 == 0x1cf0e46b0737550
mem: 0x507573b0460ecf01
	*/
}

