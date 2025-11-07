#ifndef LIBC_MINT_BASEPAGE_H
#define LIBC_MINT_BASEPAGE_H

/*
 * Minimal BASEPAGE layout derived from mintlib.
 */
typedef struct basepage {
  char *p_lowtpa;
  char *p_hitpa;
  char *p_tbase;
  long p_tlen;
  char *p_dbase;
  long p_dlen;
  char *p_bbase;
  long p_blen;
  char *p_dta;
  struct basepage *p_parent;
  char *p_reserved;
  char *p_env;
  char p_junk[8];
  long p_undef[18];
  unsigned char p_cmdlin[128];
} BASEPAGE;

extern BASEPAGE *_base;

#endif /* LIBC_MINT_BASEPAGE_H */
