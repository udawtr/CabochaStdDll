// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "stdafx.h"
#include "cabocha.h"
#include <stdio.h>

/* Definitions of function points */
typedef int        (WINAPI *fp_cabocha_do)            (int, char **);
typedef cabocha_t* (WINAPI *fp_cabocha_new)           (int, char **);
typedef cabocha_t* (WINAPI *fp_cabocha_new2)          (char *);
typedef char*      (WINAPI *fp_cabocha_strerror)      (cabocha_t*);
typedef char*      (WINAPI *fp_cabocha_sparse_tostr)  (cabocha_t *, char *);
typedef char*      (WINAPI *fp_cabocha_sparse_tostr2) (cabocha_t*,  char*, size_t);
typedef char*      (WINAPI *fp_cabocha_sparse_tostr3) (cabocha_t*,  char*, size_t, char *, size_t);
typedef void       (WINAPI *fp_cabocha_destroy)       (cabocha_t *);
typedef cabocha_tree_t*   (WINAPI *fp_cabocha_sparse_totree)   (cabocha_t*, char*);
typedef cabocha_tree_t*   (WINAPI *fp_cabocha_sparse_totree2)  (cabocha_t*, char*, size_t);
typedef size_t      (WINAPI *fp_cabocha_tree_size)       (cabocha_tree_t*);
typedef cabocha_token_t*  (WINAPI *fp_cabocha_tree_get_token)  (cabocha_tree_t*, size_t);
typedef char*             (WINAPI *fp_cabocha_tree_tostr)  (cabocha_tree_t*, int);
typedef char*             (WINAPI *fp_cabocha_tree_tostr2) (cabocha_tree_t*, int, char *, size_t);

fp_cabocha_do base_cabocha_do;
fp_cabocha_new base_cabocha_new;
fp_cabocha_new2 base_cabocha_new2;
fp_cabocha_strerror base_cabocha_strerror;
fp_cabocha_sparse_tostr base_cabocha_sparse_tostr;
fp_cabocha_sparse_tostr2 base_cabocha_sparse_tostr2;
fp_cabocha_sparse_tostr3 base_cabocha_sparse_tostr3 ;
fp_cabocha_destroy base_cabocha_destory;
fp_cabocha_sparse_totree base_cabocha_sparse_totree;
fp_cabocha_sparse_totree2 base_cabocha_sparse_totree2;
fp_cabocha_tree_size base_cabocha_tree_size;
fp_cabocha_tree_get_token base_cabocha_tree_get_token;
fp_cabocha_tree_tostr base_cabocha_tree_tostr;
fp_cabocha_tree_tostr2 base_cabocha_tree_tostr2;

BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
	)
{
	HINSTANCE hLib = NULL;

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		hLib = LoadLibraryA("libcabocha.dll");

		if (hLib) {
			base_cabocha_do = (fp_cabocha_do) GetProcAddress(hLib, "cabocha_do"); 
			base_cabocha_new = (fp_cabocha_new) GetProcAddress(hLib, "cabocha_new"); 
			base_cabocha_new2 = (fp_cabocha_new2) GetProcAddress(hLib, "cabocha_new2"); 
			base_cabocha_strerror = (fp_cabocha_strerror) GetProcAddress(hLib, "cabocha_strerror"); 
			base_cabocha_sparse_tostr = (fp_cabocha_sparse_tostr) GetProcAddress(hLib, "cabocha_sparse_tostr"); 
			base_cabocha_sparse_tostr2 = (fp_cabocha_sparse_tostr2) GetProcAddress(hLib, "cabocha_sparse_tostr2"); 
			base_cabocha_sparse_tostr3 = (fp_cabocha_sparse_tostr3) GetProcAddress(hLib, "cabocha_sparse_tostr3"); 
			base_cabocha_destory = (fp_cabocha_destroy) GetProcAddress(hLib, "cabocha_destroy"); 
			base_cabocha_sparse_totree = (fp_cabocha_sparse_totree) GetProcAddress(hLib, "cabocha_sparse_totree"); 
			base_cabocha_sparse_totree2 = (fp_cabocha_sparse_totree2) GetProcAddress(hLib, "cabocha_sparse_totree2"); 
			base_cabocha_tree_size = (fp_cabocha_tree_size) GetProcAddress(hLib, "cabocha_tree_size"); 
			base_cabocha_tree_get_token = (fp_cabocha_tree_get_token) GetProcAddress(hLib, "cabocha_tree_get_token"); 
			base_cabocha_tree_tostr = (fp_cabocha_tree_tostr) GetProcAddress(hLib, "cabocha_tree_tostr"); 
			base_cabocha_tree_tostr2 = (fp_cabocha_tree_tostr2) GetProcAddress(hLib, "cabocha_tree_tostr2"); 

			if (base_cabocha_do && base_cabocha_new && base_cabocha_new2 && base_cabocha_strerror 
				&& base_cabocha_sparse_tostr && base_cabocha_sparse_tostr2 && base_cabocha_sparse_tostr3
				&& base_cabocha_destory && base_cabocha_sparse_totree && base_cabocha_sparse_totree2
				&& base_cabocha_tree_size && base_cabocha_tree_get_token && base_cabocha_tree_tostr
				&& base_cabocha_tree_tostr2) 
			{
				return TRUE;
			}
			FreeLibrary(hLib);

		}
		return TRUE;
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		FreeLibrary(hLib);
		break;
	}
	return TRUE;
}

extern "C"
{

	__declspec(dllexport) int __stdcall cabocha_do(int a, char ** b)
	{
		return (*base_cabocha_do)(a, b);
	}

	__declspec(dllexport) cabocha_t*  __stdcall cabocha_new(int a, char ** b)
	{
		return (*base_cabocha_new)(a,b);
	}

	__declspec(dllexport) cabocha_t* __stdcall cabocha_new2(char * a)
	{
		return (*base_cabocha_new2)(a);
	}

	__declspec(dllexport) char* __stdcall cabocha_strerror(cabocha_t* a)
	{
		return (*base_cabocha_strerror)(a);
	}

	__declspec(dllexport) char* __stdcall cabocha_sparse_tostr  (cabocha_t * a, char * b)
	{
		return (*base_cabocha_sparse_tostr)(a, b);
	}

	__declspec(dllexport) char* __stdcall cabocha_sparse_tostr2 (cabocha_t* a,  char* b, size_t c)
	{
		return (*base_cabocha_sparse_tostr2)(a, b, c);
	}

	__declspec(dllexport) char* __stdcall cabocha_sparse_tostr3 (cabocha_t* a,  char* b, size_t c, char * d, size_t e)
	{
		return (*base_cabocha_sparse_tostr3)(a,b,c,d,e);
	}

	__declspec(dllexport) void __stdcall cabocha_destroy       (cabocha_t * a)
	{
		return (*base_cabocha_destory)(a);
	}

	__declspec(dllexport) cabocha_tree_t* __stdcall cabocha_sparse_totree   (cabocha_t* a, char* b)
	{
		return (*base_cabocha_sparse_totree)(a, b);
	}

	__declspec(dllexport) cabocha_tree_t* __stdcall cabocha_sparse_totree2  (cabocha_t* a, char* b, size_t c)
	{
		return (*base_cabocha_sparse_totree2)(a, b, c);
	}

	__declspec(dllexport) size_t __stdcall cabocha_tree_size       (cabocha_tree_t* a)
	{
		return (*base_cabocha_tree_size)(a);
	}

	__declspec(dllexport) cabocha_token_t* __stdcall cabocha_tree_get_token  (cabocha_tree_t* a, size_t b)
	{
		return (*base_cabocha_tree_get_token)(a, b);
	}

	__declspec(dllexport) char* __stdcall cabocha_tree_tostr  (cabocha_tree_t* a, int b)
	{
		return (*base_cabocha_tree_tostr)(a, b);
	}

	__declspec(dllexport) char* __stdcall cabocha_tree_tostr2 (cabocha_tree_t* a, int b, char * c, size_t d)
	{
		return (*base_cabocha_tree_tostr2)(a, b, c, d);
	}


}