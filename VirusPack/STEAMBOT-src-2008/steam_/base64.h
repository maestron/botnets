#include <string>

//http://www.adp-gmbh.ch/cpp/common/base64.html
//the creator of STEAMBOT takes no credit for this

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);