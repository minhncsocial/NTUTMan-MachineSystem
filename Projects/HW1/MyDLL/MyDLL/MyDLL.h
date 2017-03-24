#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

	MYDLL_API int __cdecl fnMyDLL(int a, int b);

#ifdef __cplusplus
}
#endif