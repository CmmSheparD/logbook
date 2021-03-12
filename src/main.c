#include <locale.h>
#include <stdio.h>

#include "DString/dstring.h"

int main()
{
	setlocale(LC_ALL, "en_US.utf-8");
	dstring_t *str = ds_createString();
	wprintf(L"Enter string:\t");
	wchar_t c;
	while ((c = getwchar()) != EOF) {
		ds_appendChar(str, c);
		wprintf(L"Len: %d\n", str->size - 1);
	}
	wprintf(L"Is empy: %s\n", ds_isEmpty(str) ? "true" : "false");
	fputws(str->string, stdout);
	ds_appendString(str, L"\nArgh, shit, here we go again!\n");
	fputws(str->string, stdout);
	ds_freeString(str);
	return 0;
}
