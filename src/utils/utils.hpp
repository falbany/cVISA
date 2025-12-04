#ifndef CVISA_UTILS_HPP
#define CVISA_UTILS_HPP

#include <sstream>
#include <string>

namespace cvisa {
    namespace utils {

        template <typename T>
        std::string to_string(T value) {
            std::ostringstream os;
            os << value;
            return os.str();
        }

    }    // namespace utils
}    // namespace cvisa

#endif    // CVISA_UTILS_HPP