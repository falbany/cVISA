#include "PowerSupply.hpp"

#include "../core/exceptions.hpp"

#include <map>
#include <string>

namespace cvisa {
    namespace drivers {

        // --- High-Level Methods ---
        // All methods now use the static command definition methods.

        void PowerSupply::setVoltage(double voltage) { executeCommand(Commands::SET_VOLTAGE(), voltage); }

        void PowerSupply::setCurrent(double current) { executeCommand(Commands::SET_CURRENT(), current); }

        double PowerSupply::getVoltage() { return queryAndParse<double>(Commands::GET_VOLTAGE()); }

        double PowerSupply::getCurrent() { return queryAndParse<double>(Commands::GET_CURRENT()); }

        void PowerSupply::setOutput(bool enabled) { executeCommand(Commands::SET_OUTPUT(), enabled ? 1 : 0); }

        bool PowerSupply::isOutputEnabled() { return queryAndParse<bool>(Commands::GET_OUTPUT()); }

    }    // namespace drivers
}    // namespace cvisa
