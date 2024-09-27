#ifndef SK_DEF_H
#define SK_DEF_H

typedef int SKBool;
typedef int SKErrno;

typedef void *SKHandle;
typedef void *SKBufferHandle;
typedef unsigned char *SKByteBuffer;

#define SK_BIT(v) 1 << (x)
#define SK_KB(b) ((unsigned long long)1024 * b)
#define SK_MB(b) ((unsinged long long)1024 * SK_KB(b))
#define SK_GB(b) ((unsigned long long)1024 * SK_MB(b))

#define TRUE 1
#define YES 1
#define SK_YES 1
#define SK_TRUE 1

#define FALSE 0
#define NO 0

#define SK_NO 0
#define SK_FALSE 0

#define SK_NULL (void *)0

#define SK_EXIT_FAILURE 1
#define SK_EXIT_SUCCESS 0

#ifdef _WIN32
#define SK_EXPORT __declspec(dllexport)
#elif __APPLE__
#define SK_EXPORT
#elif __linux__
#define SK_EXPORT
#endif

#endif
