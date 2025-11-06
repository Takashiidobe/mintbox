#ifndef LIBC_ERRNO_H
#define LIBC_ERRNO_H

extern int errno;
#define __set_errno(err) (errno = err)

// Gemdos error messages

#define E_OK 0      // OK. No error has arisen
#define EINVFN -32  // Unknown function number
#define EFILNF -33  // File not found
#define EPTHNF -34  // Directory folder not found
#define ENHNDL -35  // No more handles available
#define EACCDN -36  // Access denied
#define EIHNDL -37  // Invalid file handle
#define ENSMEM -39  // Insufficient memory
#define EIMBA -40   // Invalid memory block address
#define EDRIVE -46  // Invalid drive specification
#define ECWD -47    // Current directory cannot be deleted
#define ENSAME -48  // Files on different logical drives
#define ENMFIL -49  // No more files can be opened
#define ELOCKED -58 // Segment of a file is protected network
#define ENSLOCK -59 // Invalid lock removal request
// #define ERANGE -64  // File pointer in invalid segment
#define EINTRN -65 // Internal error of GEMDOS
#define EPLFMT -66 // Invalid program load format
#define EGSBF -67  // Allocated memory block could not be enlarged
#define EBREAK -68 // Program termination by Control-C
#define EXCPT -69  // 68000 exception bombs
#define EPTHOV -70 // Path overflow
#define ELOOP -80  // Endless loop with symbolic links
#define EPIPE -81  // Write to broken pipe.

// Freemint error messages

#define EERROR -1        /* Generic error */
#define EBUSY -2         /* Resource busy */
#define EUKCMD -3        /* Unknown command */
#define ECRC -4          /* CRC error */
#define EBADR -5         /* Bad request */
#define ESPIPE -6        /* Illegal seek */
#define EMEDIUMTYPE -7   /* Wrong medium type */
#define ESECTOR -8       /* Sector not found */
#define EWRITE -10       /* Write fault */
#define EGENERIC -12     /* General mishap */
#define EROFS -13        /* Write protected */
#define ECHMEDIA -14     /* Media change */
#define ENODEV -15       /* No such device */
#define EBADSEC -16      /* Bad sectors found */
#define ENOMEDIUM -17    /* No medium found */
#define ESRCH -20        /* No such process */
#define ECHILD -21       /* No child processes */
#define EDEADLK -22      /* Resource deadlock would occur */
#define ENOTBLK -23      /* Block device required */
#define EISDIR -24       /* Is a directory */
#define EINVAL -25       /* Invalid argument */
#define EFTYPE -26       /* Inappropriate file type or format */
#define EILSEQ -27       /* Illegal byte sequence */
#define ENOSYS -32       /* Function not implemented */
#define ENOENT -33       /* No such file or directory */
#define ENOTDIR -34      /* Not a directory */
#define EMFILE -35       /* Too many open files */
#define EACCES -36       /* Permission denied */
#define EBADF -37        /* Bad file descriptor */
#define EPERM -38        /* Operation not permitted */
#define ENOMEM -39       /* Cannot allocate memory */
#define EFAULT -40       /* Bad address */
#define ENXIO -46        /* No such device or address */
#define EXDEV -48        /* Cross-device link */
#define ENMFILES -49     /* No more matching file names */
#define ENFILE -50       /* File table overflow */
#define ELOCKED -58      /* Locking conflict */
#define ENSLOCK -59      /* No such lock */
#define EBADARG -64      /* Bad argument */
#define EINTERNAL -65    /* Internal error */
#define ENOEXEC -66      /* Invalid executable file format */
#define ESBLOCK -67      /* Memory block growth failure */
#define EBREAK -68       /* Aborted by user */
#define EXCPT -69        /* Terminated with bombs */
#define ETXTBSY -70      /* Text file busy */
#define EFBIG -71        /* File too big */
#define ELOOP -80        /* Too many symbolic links, possibly endless loop */
#define EPIPE -81        /* Broken pipe */
#define EMLINK -82       /* Too many links */
#define ENOTEMPTY -83    /* Directory not empty */
#define EEXIST -85       /* File exists */
#define ENAMETOOLONG -86 /* Name too long */
#define ENOTTY -87       /* Not a TTY */
#define ERANGE -88       /* Range error */
#define EDOM -89         /* Domain error */
#define EIO -90          /* I/O error */
#define ENOSPC -91       /* No space left on device */
/*
#define RESERVED_92 -92 // reserved for TraPatch
#define RESERVED_93 -93 // reserved for TraPatch
#define RESERVED_94 -94 // reserved for TraPatch
#define RESERVED_95 -95 // reserved for TraPatch
#define RESERVED_96 -96 // reserved for TraPatch
#define RESERVED_97 -97 // reserved for TraPatch
#define RESERVED_98 -98 // reserved for TraPatch
#define RESERVED_99 -99 // reserved for TraPatch
*/
#define EPROCLIM -100      /* Too many processes for user */
#define EUSERS -101        /* Too many users */
#define EDQUOT -102        /* Quota exceeded */
#define ESTALE -103        /* Stale NFS file handle */
#define EREMOTE -104       /* Object is remote */
#define EBADRPC -105       /* RPC struct is bad */
#define ERPCMISMATCH -106  /* RPC version wrong */
#define EPROGUNAVAIL -107  /* RPC program not available */
#define EPROGMISMATCH -108 /* RPC program version wrong */
#define EPROCUNAVAIL -109  /* RPC bad procedure for program */
#define ENOLCK -110        /* No locks available */
#define EAUTH -111         /* Authentication error */
#define ENEEDAUTH -112     /* Need authenticator */
#define EBACKGROUND                                                            \
  -113                       /* Inappropriate operation for background process \
                              */
#define EBADMSG -114         /* Not a data message */
#define EIDRM -115           /* Identifier removed */
#define EMULTIHOP -116       /* Multihop attempted */
#define ENODATA -117         /* No data available */
#define ENOLINK -118         /* Link has been severed */
#define ENOMSG -119          /* No message of desired type */
#define ENOSR -120           /* Out of streams resources */
#define ENOSTR -121          /* Device not a stream */
#define EOVERFLOW -122       /* Value too large for defined data type */
#define EPROTO -123          /* Protocol error */
#define ETIME -124           /* Timer expired */
#define E2BIG -125           /* Argument list too long */
#define ERESTART -126        /* Interrupted system call should be */
#define ECHRNG -127          /* Channel number out of range */
#define EINTR -128           /* Interrupted function call */
#define ESNDLOCKED -129      /* Sound system is already locked */
#define ESNDNOTLOCK -130     /* Sound system is not locked */
#define EL2NSYNC -131        /* Level 2 not synchronized */
#define EL3HLT -132          /* Level 3 halted */
#define EL3RST -133          /* Level 3 reset */
#define ELNRNG -134          /* Link number out of range */
#define EUNATCH -135         /* Protocol driver not attached */
#define ENOCSI -136          /* No CSI structure available */
#define EL2HLT -137          /* Level 2 halted */
#define EBADE -138           /* Invalid exchange */
#define EXFULL -139          /* Exchange full */
#define ENOANO -140          /* No anode */
#define EBADRQC -141         /* Invalid request code */
#define EBADSLT -142         /* Invalid slot */
#define EBFONT -143          /* Bad font file format */
#define ENONET -144          /* Machine is not on the network */
#define ENOPKG -145          /* Package is not installed. */
#define EADV -146            /* Advertise error */
#define ESRMNT -147          /* Srmount error */
#define ECOMM -148           /* Communication error on send */
#define EDOTDOT -149         /* RFS specific error */
#define ELIBACC -150         /* Cannot access a needed shared library */
#define ELIBBAD -151         /* Accessing a corrupted shared library */
#define ELIBSCN -152         /* lib section in a.out corrupted */
#define ELIBMAX -153         /* Attempting to link too many shared libraries */
#define ELIBEXEC -154        /* Cannot exec a shared library directly */
#define ESTRPIPE -155        /* Streams pipe error */
#define EUCLEAN -156         /* Structure needs cleaning */
#define ENOTNAM -157         /* Not a XENIX named type file */
#define ENAVAIL -158         /* No XENIX semaphores available */
#define EREMOTEIO -159       /* Remote I/O error */
#define EMOUNT -200          /* Mount point crossed (indicator) */
#define ENOTSOCK -300        /* Socket operation on non-socket */
#define EDESTADDRREQ -301    /* Destination address required */
#define EMSGSIZE -302        /* Message too long */
#define EPROTOTYPE -303      /* Protocol wrong type for socket */
#define ENOPROTOOPT -304     /* Protocol not available */
#define EPROTONOSUPPORT -305 /* Protocol not supported */
#define ESOCKTNOSUPPORT -306 /* Socket type not supported */
#define EOPNOTSUPP -307      /* Operation not supported */
#define EPFNOSUPPORT -308    /* Protocol family not supported */
#define EAFNOSUPPORT -309    /* Address family not supported by protocol */
#define EADDRINUSE -310      /* Address already in use */
#define EADDRNOTAVAIL -311   /* Cannot assign requested address */
#define ENETDOWN -312        /* Network is down */
#define ENETUNREACH -313     /* Network is unreachable */
#define ENETRESET -314       /* Network dropped connection because of reset */
#define ECONNABORTED -315    /* Software caused connection abort */
#define ECONNRESET -316      /* Connection reset by peer */
#define EISCONN -317         /* Socket is already connected */
#define ENOTCONN -318        /* Socket is not connected */
#define ESHUTDOWN -319       /* Cannot send after shutdown */
#define ETIMEDOUT -320       /* Connection timed out */
#define ECONNREFUSED -321    /* Connection refused */
#define EHOSTDOWN -322       /* Host is down */
#define EHOSTUNREACH -323    /* No route to host */
#define EALREADY -324        /* Operation already in progress */
#define EINPROGRESS -325     /* Operation now in progress */
#define EAGAIN -326          /* Operation would block */
#define EWOULDBLOCK EAGAIN   /* see EAGAIN */
#define ENOBUFS -327         /* No buffer space available */
#define ETOOMANYREFS -328    /* Too many references */

#endif /* LIBC_ERRNO_H */
