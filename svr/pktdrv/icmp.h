#if !defined(_ICMP_H)
#define _ICMP_H

#include "nettypes.h"
#include <stddef.h>

int icmp_probe(const void* frame, unsigned int frame_len);
int icmp_dispatch(const void* frame,
                  size_t frame_len);

#endif /* _ICMP_H defined? */
