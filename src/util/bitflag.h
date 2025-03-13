#ifndef VCP_BITFLAG_H
#define VCP_BITFLAG_H

#define BITFLAG(v) (1 << (v))
#define HASFLAG(f, v) (((f) & (v)) == (v))
#define ANYFLAG(f, v) (((f) & (v)) >  (0))

//#define BIT_CHK_FLAG(f, v) (((f) & (v)) == (v))
//#define BIT_CHK_FLAG(f, v) (((f) & (v)) >  (0))
//
//#define BIT_SET(v, b) ((value) |=  (1L << (bit)))
//#define BIT_CLR(v, b) ((value) &= ~(1L << (bit)))
//#define BIT_CHK(b, reg) ((reg >> (bit)) & 1)
//#define BIT_LSB(reg) ((reg)&1)

#endif