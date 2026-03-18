
#ifndef QKAPI_H
#define QKAPI_H

#ifdef MTQUARK_STATIC_DEFINE
#  define QKAPI
#  define MTQUARK_NO_EXPORT
#else
#  ifndef QKAPI
#    ifdef quark_EXPORTS
        /* We are building this library */
#      define QKAPI __declspec(dllexport)
#    else
        /* We are using this library */
#      define QKAPI __declspec(dllimport)
#    endif
#  endif

#  ifndef MTQUARK_NO_EXPORT
#    define MTQUARK_NO_EXPORT 
#  endif
#endif

#ifndef MTQUARK_DEPRECATED
#  define MTQUARK_DEPRECATED __declspec(deprecated)
#endif

#ifndef MTQUARK_DEPRECATED_EXPORT
#  define MTQUARK_DEPRECATED_EXPORT QKAPI MTQUARK_DEPRECATED
#endif

#ifndef MTQUARK_DEPRECATED_NO_EXPORT
#  define MTQUARK_DEPRECATED_NO_EXPORT MTQUARK_NO_EXPORT MTQUARK_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef MTQUARK_NO_DEPRECATED
#    define MTQUARK_NO_DEPRECATED
#  endif
#endif

#endif /* QKAPI_H */
