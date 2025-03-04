
#include <string>

namespace qffixlib {

std::string base64_encode(const unsigned char* input, int length);
std::string hmac_sha256_base64(const std::string& bEncodedkey, const std::string& data);

}