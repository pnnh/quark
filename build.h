#ifdef _MSC_VER
#ifdef EXPORTING
#define CXAPI __declspec(dllexport)
#else
#define CXAPI __declspec(dllimport)
#endif

#else
#define CXAPI __attribute__((visibility("default")))
#endif
