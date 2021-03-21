#include <stdio.h>
#include <string.h>
#include <iostream>

#include "SHCrypt.h"
#include "AES.h"

SHCrypt::SHCrypt() {}

SHCrypt::SHCrypt(uint8_t key[]) {
	memcpy(this->key, key, AES_KEYLEN);
}

SHCrypt::~SHCrypt() {}

void SHCrypt::Encrypt(uint8_t* in, uint32_t size, uint8_t* out) {
	memcpy(out, in, size);
	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_encrypt_buffer(&ctx, out, size);
}

void SHCrypt::Encrypt(uint8_t* data, uint32_t size) {
	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_encrypt_buffer(&ctx, data, size);
}

void SHCrypt::Decrypt(uint8_t *in, uint32_t size, uint8_t* result) {
	memcpy(result, in, size);
	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, result, size);
}

void SHCrypt::Decrypt(uint8_t* data, uint32_t size) {
	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, data, size);
}
