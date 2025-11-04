#ifndef GEMDOS_INET_H
#define GEMDOS_INET_H

#include "../include/stdint.h"
#include "./syscall.h"

/* Forward declarations for networking structures supplied elsewhere. */
struct iovec;
struct msghdr;
struct sockaddr;

// Fwritev - Write data from multiple buffers.
static inline int32_t Fwritev(int16_t handle, struct iovec *iov, int32_t niov) {
  return (int32_t)trap_1_wwll(0x15B, handle, (long)iov, (long)niov);
}

// Freadv - Read data into multiple buffers.
static inline int32_t Freadv(int16_t handle, struct iovec *iov, int32_t niov) {
  return (int32_t)trap_1_wwll(0x15C, handle, (long)iov, (long)niov);
}

// Fsocket - Create an endpoint for communication.
static inline int32_t Fsocket(int32_t domain, int32_t type, int32_t protocol) {
  return (int32_t)trap_1_wlll(0x160, (long)domain, (long)type, (long)protocol);
}

// Fsocketpair - Create a pair of connected sockets.
static inline int32_t Fsocketpair(int32_t domain, int32_t type,
                                  int32_t protocol, int16_t fds[2]) {
  return (int32_t)trap_1_wllll(0x161, (long)domain, (long)type, (long)protocol,
                               (long)fds);
}

// Faccept - Accept a connection on a socket.
static inline int32_t Faccept(int16_t fd, struct sockaddr *name,
                              uint32_t *anamelen) {
  return (int32_t)trap_1_wwll(0x162, fd, (long)name, (long)anamelen);
}

// Fconnect - Initiate a connection on a socket.
static inline int32_t Fconnect(int16_t fd, struct sockaddr *name,
                               uint32_t anamelen) {
  return (int32_t)trap_1_wwll(0x163, fd, (long)name, (long)anamelen);
}

// Fbind - Bind a name to a socket.
static inline int32_t Fbind(int16_t fd, const struct sockaddr *name,
                            uint32_t anamelen) {
  return (int32_t)trap_1_wwll(0x164, fd, (long)name, (long)anamelen);
}

// Flisten - Listen for connections on a socket.
static inline int32_t Flisten(int16_t fd, int32_t backlog) {
  return (int32_t)trap_1_wwl(0x165, fd, (long)backlog);
}

// Frecvmsg - Receive a message from a socket.
static inline int32_t Frecvmsg(int16_t fd, struct msghdr *msg, int32_t flags) {
  return (int32_t)trap_1_wwll(0x166, fd, (long)msg, (long)flags);
}

// Fsendmsg - Send a message on a socket.
static inline int32_t Fsendmsg(int16_t fd, const struct msghdr *msg,
                               int32_t flags) {
  return (int32_t)trap_1_wwll(0x167, fd, (long)msg, (long)flags);
}

// Frecvfrom - Receive a message from a socket.
static inline int32_t Frecvfrom(int16_t fd, void *buf, int32_t buflen,
                                int32_t flags, struct sockaddr *to,
                                uint32_t *addrlen) {
  return (int32_t)trap_1_wwlllll(0x168, fd, (long)buf, (long)buflen,
                                 (long)flags, (long)to, (long)addrlen);
}

// Fsendto - Send a message on a socket.
static inline int32_t Fsendto(int16_t fd, const void *buf, int32_t buflen,
                              int32_t flags, const struct sockaddr *to,
                              uint32_t addrlen) {
  return (int32_t)trap_1_wwlllll(0x169, fd, (long)buf, (long)buflen,
                                 (long)flags, (long)to, (long)addrlen);
}

// Fsetsockopt - Set options on sockets.
static inline int32_t Fsetsockopt(int16_t fd, int32_t level, int32_t name,
                                  const void *val, uint32_t valsize) {
  return (int32_t)trap_1_wwllll(0x16A, fd, (long)level, (long)name, (long)val,
                                (long)valsize);
}

// Fgetsockopt - Get options on sockets.
static inline int32_t Fgetsockopt(int16_t fd, int32_t level, int32_t name,
                                  void *val, uint32_t *valsize) {
  return (int32_t)trap_1_wwllll(0x16B, fd, (long)level, (long)name, (long)val,
                                (long)valsize);
}

// Fgetpeername - Get name of connected peer socket.
static inline int32_t Fgetpeername(int16_t fd, struct sockaddr *asa,
                                   uint32_t *alen) {
  return (int32_t)trap_1_wwll(0x16C, fd, (long)asa, (long)alen);
}

// Fgetsockname - Get socket name.
static inline int32_t Fgetsockname(int16_t fd, struct sockaddr *asa,
                                   uint32_t *alen) {
  return (int32_t)trap_1_wwll(0x16D, fd, (long)asa, (long)alen);
}

// Fshutdown - Shut down part of a full-duplex connection.
static inline int32_t Fshutdown(int16_t fd, int32_t how) {
  return (int32_t)trap_1_wwl(0x16E, fd, (long)how);
}

#endif /* GEMDOS_INET_H */
