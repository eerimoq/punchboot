#ifndef __PB_IO_H_
#define __PB_IO_H_

#include <pb_types.h>

static inline u32 pb_readl(void * addr)
{
	return *(( u32 *)addr);
}

static inline void pb_writel(u32 data, void * addr)
{
	*(( u32 *)addr) = data;
}


static inline void pb_write(u16 data, void * addr)
{
	*(( u16 *)addr) = data;
}


#define REG(base, reg) ( (void *) base+reg)

#endif

