
#ifndef QKAPI_H
#define QKAPI_H

#ifdef MTQUARK_STATIC_DEFINE
#  define QKAPI
#  define MTQUARK_NO_EXPORT
#else
#  ifndef QKAPI
#    ifdef quark_EXPORTS
        /* We are building this library */
#      define QKAPI __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define QKAPI __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef MTQUARK_NO_EXPORT
#    define MTQUARK_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef MTQUARK_DEPRECATED
#  define MTQUARK_DEPRECATED __attribute__ ((__deprecated__))
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
