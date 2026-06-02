#include "Logger.hpp"

namespace cvisa {

    // Initialize the static output stream vector.
    std::vector<std::ostream*> Logger::s_outputStreams;

}    // namespace cvisa
