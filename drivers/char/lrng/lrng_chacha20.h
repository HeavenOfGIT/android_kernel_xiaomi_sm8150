
/* SPDX-License-Identifier: GPL-2.0 OR BSD-2-Clause */
/*
 * LRNG ChaCha20 definitions
 *
 * Copyright (C) 2016 - 2021, Stephan Mueller <smueller@chronox.de>
 */

#include <crypto/chacha.h>

/* State according to RFC 7539 section 2.3 */
struct chacha20_block {
	u32 constants[4];
	union {
#define CHACHA_KEY_SIZE_WORDS (CHACHA_KEY_SIZE / sizeof(u32))
		u32 u[CHACHA_KEY_SIZE_WORDS];
		u8  b[CHACHA_KEY_SIZE];
	} key;
	u32 counter;
	u32 nonce[3];
};

static inline void lrng_cc20_init_rfc7539(struct chacha20_block *chacha20v)
{
	/* String "expand 32-byte k" */
	chacha20v->constants[0] = 0x61707865;
	chacha20v->constants[1] = 0x3320646e;
	chacha20v->constants[2] = 0x79622d32;
	chacha20v->constants[3] = 0x6b206574;
}