#include "base64_hmac.h"
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <iostream>

namespace qffixlib {

    std::string base64_encode(const unsigned char* input, int length) {
        BIO *bmem = BIO_new(BIO_s_mem());
        BIO *b64 = BIO_new(BIO_f_base64());
        b64 = BIO_push(b64, bmem);

        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);  // No newlines
        BIO_write(b64, input, length);
        BIO_flush(b64);
        
        BUF_MEM *bptr;
        BIO_get_mem_ptr(b64, &bptr);
        
        std::string encoded(bptr->data, bptr->length);
        BIO_free_all(b64);

        std::cout << "input(" << input << ")base64" << encoded << std::endl;
        
        return encoded;
    }

    std::vector<unsigned char> base64_decode(const std::string& encoded) {
        BIO* bio = BIO_new_mem_buf(encoded.data(), encoded.size());
        BIO* b64 = BIO_new(BIO_f_base64());
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); // No newlines

        bio = BIO_push(b64, bio);

        std::vector<unsigned char> decoded(encoded.size()); // Allocate output buffer
        int decodedLen = BIO_read(bio, decoded.data(), encoded.size());

        BIO_free_all(bio);

        if (decodedLen <= 0) return {}; // Decoding failed

        decoded.resize(decodedLen); // Adjust to actual decoded size
        return decoded;
    }

    std::string hmac_sha256_base64(const std::string& key, const std::string& bEncodedKey, const std::string& data) {
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hash_len = 0;

        std::cout << "k[" << key << "]data[" << data << std::endl;

        auto b_key = base64_decode(bEncodedKey);

        std::cout << std::string(b_key.begin(), b_key.end()) << std::endl;

        HMAC(EVP_sha256(), b_key.data(), b_key.size(),
            (unsigned char*)data.c_str(), data.length(),
            hash, &hash_len);

        return base64_encode(hash, hash_len);
    }
}

