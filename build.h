#ifdef _MSC_VER
#define MTCXXAPI __declspec (dllexport)
#define MTCAPI __declspec (dllexport) extern "C"
#else
#define MTCXXAPI __attribute__((visibility("default")))
#define MTCAPI __attribute__((visibility("default"))) extern "C"
#endif
