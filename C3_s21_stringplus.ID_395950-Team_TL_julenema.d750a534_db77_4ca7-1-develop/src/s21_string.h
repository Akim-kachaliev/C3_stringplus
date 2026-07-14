#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

typedef unsigned long s21_size_t;
#define S21_NULL ((void*)0)

// Структура для s21_sprintf
typedef struct {
  int minus;
  int plus;
  int space;
  int width;
  int precision;
  int is_precision;
  char length;
  char specifier;
} opt_t;

// Массивы сообщений об ошибках для s21_strerror
// Mac и Linux имеют разные коды и описания ошибок,
// нужный массив выбирается автоматически при компиляции
#ifdef __APPLE__
#define S21_ERRLIST_SIZE 107
#define S21_ERRLIST                                                  \
  {                                                                  \
      "Undefined error: 0",                                /* 0 */   \
      "Operation not permitted",                           /* 1 */   \
      "No such file or directory",                         /* 2 */   \
      "No such process",                                   /* 3 */   \
      "Interrupted system call",                           /* 4 */   \
      "Input/output error",                                /* 5 */   \
      "Device not configured",                             /* 6 */   \
      "Argument list too long",                            /* 7 */   \
      "Exec format error",                                 /* 8 */   \
      "Bad file descriptor",                               /* 9 */   \
      "No child processes",                                /* 10 */  \
      "Resource deadlock avoided",                         /* 11 */  \
      "Cannot allocate memory",                            /* 12 */  \
      "Permission denied",                                 /* 13 */  \
      "Bad address",                                       /* 14 */  \
      "Block device required",                             /* 15 */  \
      "Resource busy",                                     /* 16 */  \
      "File exists",                                       /* 17 */  \
      "Cross-device link",                                 /* 18 */  \
      "Operation not supported by device",                 /* 19 */  \
      "Not a directory",                                   /* 20 */  \
      "Is a directory",                                    /* 21 */  \
      "Invalid argument",                                  /* 22 */  \
      "Too many open files in system",                     /* 23 */  \
      "Too many open files",                               /* 24 */  \
      "Inappropriate ioctl for device",                    /* 25 */  \
      "Text file busy",                                    /* 26 */  \
      "File too large",                                    /* 27 */  \
      "No space left on device",                           /* 28 */  \
      "Illegal seek",                                      /* 29 */  \
      "Read-only file system",                             /* 30 */  \
      "Too many links",                                    /* 31 */  \
      "Broken pipe",                                       /* 32 */  \
      "Numerical argument out of domain",                  /* 33 */  \
      "Result too large",                                  /* 34 */  \
      "Resource temporarily unavailable",                  /* 35 */  \
      "Operation now in progress",                         /* 36 */  \
      "Operation already in progress",                     /* 37 */  \
      "Socket operation on non-socket",                    /* 38 */  \
      "Destination address required",                      /* 39 */  \
      "Message too long",                                  /* 40 */  \
      "Protocol wrong type for socket",                    /* 41 */  \
      "Protocol not available",                            /* 42 */  \
      "Protocol not supported",                            /* 43 */  \
      "Socket type not supported",                         /* 44 */  \
      "Operation not supported",                           /* 45 */  \
      "Protocol family not supported",                     /* 46 */  \
      "Address family not supported by protocol family",   /* 47 */  \
      "Address already in use",                            /* 48 */  \
      "Can't assign requested address",                    /* 49 */  \
      "Network is down",                                   /* 50 */  \
      "Network is unreachable",                            /* 51 */  \
      "Network dropped connection on reset",               /* 52 */  \
      "Software caused connection abort",                  /* 53 */  \
      "Connection reset by peer",                          /* 54 */  \
      "No buffer space available",                         /* 55 */  \
      "Socket is already connected",                       /* 56 */  \
      "Socket is not connected",                           /* 57 */  \
      "Can't send after socket shutdown",                  /* 58 */  \
      "Too many references: can't splice",                 /* 59 */  \
      "Operation timed out",                               /* 60 */  \
      "Connection refused",                                /* 61 */  \
      "Too many levels of symbolic links",                 /* 62 */  \
      "File name too long",                                /* 63 */  \
      "Host is down",                                      /* 64 */  \
      "No route to host",                                  /* 65 */  \
      "Directory not empty",                               /* 66 */  \
      "Too many processes",                                /* 67 */  \
      "Too many users",                                    /* 68 */  \
      "Disc quota exceeded",                               /* 69 */  \
      "Stale NFS file handle",                             /* 70 */  \
      "Too many levels of remote in path",                 /* 71 */  \
      "RPC struct is bad",                                 /* 72 */  \
      "RPC version wrong",                                 /* 73 */  \
      "RPC prog. not avail",                               /* 74 */  \
      "Program version wrong",                             /* 75 */  \
      "Bad procedure for program",                         /* 76 */  \
      "No locks available",                                /* 77 */  \
      "Function not implemented",                          /* 78 */  \
      "Inappropriate file type or format",                 /* 79 */  \
      "Authentication error",                              /* 80 */  \
      "Need authenticator",                                /* 81 */  \
      "Device power is off",                               /* 82 */  \
      "Device error",                                      /* 83 */  \
      "Value too large to be stored in data type",         /* 84 */  \
      "Bad executable (or shared library)",                /* 85 */  \
      "Bad CPU type in executable",                        /* 86 */  \
      "Shared library version mismatch",                   /* 87 */  \
      "Malformed Mach-o file",                             /* 88 */  \
      "Operation canceled",                                /* 89 */  \
      "Too many levels of symbolic links",                 /* 90 */  \
      "Message queue overflow",                            /* 91 */  \
      "Invalid or incomplete multibyte or wide character", /* 92 */  \
      "No message of desired type",                        /* 93 */  \
      "Identifier removed",                                /* 94 */  \
      "No child processes",                                /* 95 */  \
      "No locks available",                                /* 96 */  \
      "Operation not supported",                           /* 97 */  \
      "Illegal byte sequence",                             /* 98 */  \
      "Attribute not found",                               /* 99 */  \
      "Bad message",                                       /* 100 */ \
      "Reserved",                                          /* 101 */ \
      "No message available on STREAM",                    /* 102 */ \
      "Reserved",                                          /* 103 */ \
      "No STREAM resources",                               /* 104 */ \
      "Not a STREAM",                                      /* 105 */ \
      "Protocol error",                                    /* 106 */ \
  }
#else
// Linux
#define S21_ERRLIST_SIZE 134
#define S21_ERRLIST                                                  \
  {                                                                  \
      "Success",                                           /* 0 */   \
      "Operation not permitted",                           /* 1 */   \
      "No such file or directory",                         /* 2 */   \
      "No such process",                                   /* 3 */   \
      "Interrupted system call",                           /* 4 */   \
      "Input/output error",                                /* 5 */   \
      "No such device or address",                         /* 6 */   \
      "Argument list too long",                            /* 7 */   \
      "Exec format error",                                 /* 8 */   \
      "Bad file descriptor",                               /* 9 */   \
      "No child processes",                                /* 10 */  \
      "Resource temporarily unavailable",                  /* 11 */  \
      "Cannot allocate memory",                            /* 12 */  \
      "Permission denied",                                 /* 13 */  \
      "Bad address",                                       /* 14 */  \
      "Block device required",                             /* 15 */  \
      "Device or resource busy",                           /* 16 */  \
      "File exists",                                       /* 17 */  \
      "Invalid cross-device link",                         /* 18 */  \
      "No such device",                                    /* 19 */  \
      "Not a directory",                                   /* 20 */  \
      "Is a directory",                                    /* 21 */  \
      "Invalid argument",                                  /* 22 */  \
      "Too many open files in system",                     /* 23 */  \
      "Too many open files",                               /* 24 */  \
      "Inappropriate ioctl for device",                    /* 25 */  \
      "Text file busy",                                    /* 26 */  \
      "File too large",                                    /* 27 */  \
      "No space left on device",                           /* 28 */  \
      "Illegal seek",                                      /* 29 */  \
      "Read-only file system",                             /* 30 */  \
      "Too many links",                                    /* 31 */  \
      "Broken pipe",                                       /* 32 */  \
      "Numerical argument out of domain",                  /* 33 */  \
      "Numerical result out of range",                     /* 34 */  \
      "Resource deadlock avoided",                         /* 35 */  \
      "File name too long",                                /* 36 */  \
      "No locks available",                                /* 37 */  \
      "Function not implemented",                          /* 38 */  \
      "Directory not empty",                               /* 39 */  \
      "Too many levels of symbolic links",                 /* 40 */  \
      "Unknown error 41",                                  /* 41 */  \
      "No message of desired type",                        /* 42 */  \
      "Identifier removed",                                /* 43 */  \
      "Channel number out of range",                       /* 44 */  \
      "Level 2 not synchronized",                          /* 45 */  \
      "Level 3 halted",                                    /* 46 */  \
      "Level 3 reset",                                     /* 47 */  \
      "Link number out of range",                          /* 48 */  \
      "Protocol driver not attached",                      /* 49 */  \
      "No CSI structure available",                        /* 50 */  \
      "Level 2 halted",                                    /* 51 */  \
      "Invalid exchange",                                  /* 52 */  \
      "Invalid request descriptor",                        /* 53 */  \
      "Exchange full",                                     /* 54 */  \
      "No anode",                                          /* 55 */  \
      "Invalid request code",                              /* 56 */  \
      "Invalid slot",                                      /* 57 */  \
      "Unknown error 58",                                  /* 58 */  \
      "Bad font file format",                              /* 59 */  \
      "Device not a stream",                               /* 60 */  \
      "No data available",                                 /* 61 */  \
      "Timer expired",                                     /* 62 */  \
      "Out of streams resources",                          /* 63 */  \
      "Machine is not on the network",                     /* 64 */  \
      "Package not installed",                             /* 65 */  \
      "Object is remote",                                  /* 66 */  \
      "Link has been severed",                             /* 67 */  \
      "Advertise error",                                   /* 68 */  \
      "Srmount error",                                     /* 69 */  \
      "Communication error on send",                       /* 70 */  \
      "Protocol error",                                    /* 71 */  \
      "Multihop attempted",                                /* 72 */  \
      "RFS specific error",                                /* 73 */  \
      "Bad message",                                       /* 74 */  \
      "Value too large for defined data type",             /* 75 */  \
      "Name not unique on network",                        /* 76 */  \
      "File descriptor in bad state",                      /* 77 */  \
      "Remote address changed",                            /* 78 */  \
      "Can not access a needed shared library",            /* 79 */  \
      "Accessing a corrupted shared library",              /* 80 */  \
      ".lib section in a.out corrupted",                   /* 81 */  \
      "Attempting to link in too many shared libraries",   /* 82 */  \
      "Cannot exec a shared library directly",             /* 83 */  \
      "Invalid or incomplete multibyte or wide character", /* 84 */  \
      "Interrupted system call should be restarted",       /* 85 */  \
      "Streams pipe error",                                /* 86 */  \
      "Too many users",                                    /* 87 */  \
      "Socket operation on non-socket",                    /* 88 */  \
      "Destination address required",                      /* 89 */  \
      "Message too long",                                  /* 90 */  \
      "Protocol wrong type for socket",                    /* 91 */  \
      "Protocol not available",                            /* 92 */  \
      "Protocol not supported",                            /* 93 */  \
      "Socket type not supported",                         /* 94 */  \
      "Operation not supported",                           /* 95 */  \
      "Protocol family not supported",                     /* 96 */  \
      "Address family not supported by protocol",          /* 97 */  \
      "Address already in use",                            /* 98 */  \
      "Cannot assign requested address",                   /* 99 */  \
      "Network is down",                                   /* 100 */ \
      "Network is unreachable",                            /* 101 */ \
      "Network dropped connection on reset",               /* 102 */ \
      "Software caused connection abort",                  /* 103 */ \
      "Connection reset by peer",                          /* 104 */ \
      "No buffer space available",                         /* 105 */ \
      "Transport endpoint is already connected",           /* 106 */ \
      "Transport endpoint is not connected",               /* 107 */ \
      "Cannot send after transport endpoint shutdown",     /* 108 */ \
      "Too many references: cannot splice",                /* 109 */ \
      "Connection timed out",                              /* 110 */ \
      "Connection refused",                                /* 111 */ \
      "Host is down",                                      /* 112 */ \
      "No route to host",                                  /* 113 */ \
      "Operation already in progress",                     /* 114 */ \
      "Operation now in progress",                         /* 115 */ \
      "Stale file handle",                                 /* 116 */ \
      "Structure needs cleaning",                          /* 117 */ \
      "Not a XENIX named type file",                       /* 118 */ \
      "No XENIX semaphores available",                     /* 119 */ \
      "Is a named type file",                              /* 120 */ \
      "Remote I/O error",                                  /* 121 */ \
      "Disk quota exceeded",                               /* 122 */ \
      "No medium found",                                   /* 123 */ \
      "Wrong medium type",                                 /* 124 */ \
      "Operation canceled",                                /* 125 */ \
      "Required key not available",                        /* 126 */ \
      "Key has expired",                                   /* 127 */ \
      "Key has been revoked",                              /* 128 */ \
      "Key was rejected by service",                       /* 129 */ \
      "Owner died",                                        /* 130 */ \
      "State not recoverable",                             /* 131 */ \
      "Operation not possible due to RF-kill",             /* 132 */ \
      "Memory page has hardware error",                    /* 133 */ \
  }
#endif

// Прототипы функций
int s21_sprintf(char* str, const char* format, ...);

void* s21_memchr(const void* str, int c, s21_size_t n);
int s21_memcmp(const void* str1, const void* str2, s21_size_t n);
void* s21_memcpy(void* dest, const void* src, s21_size_t n);
void* s21_memset(void* str, int c, s21_size_t n);
char* s21_strncat(char* dest, const char* src, s21_size_t n);
char* s21_strchr(const char* str, int c);
int s21_strncmp(const char* str1, const char* str2, s21_size_t n);
char* s21_strncpy(char* dest, const char* src, s21_size_t n);
s21_size_t s21_strcspn(const char* str1, const char* str2);
char* s21_strerror(int errnum);
s21_size_t s21_strlen(const char* str);
char* s21_strpbrk(const char* str1, const char* str2);
char* s21_strrchr(const char* str, int c);
char* s21_strstr(const char* haystack, const char* needle);
char* s21_strtok(char* str, const char* delim);

#endif  // S21_STRING_H