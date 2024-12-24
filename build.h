#ifdef _MSC_VER
#define MTAPI __declspec (dllexport)
#else
#define MTAPI __attribute__((visibility("default")))
#endif
