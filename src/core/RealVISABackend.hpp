#ifndef CVISA_REAL_VISA_BACKEND_HPP
#define CVISA_REAL_VISA_BACKEND_HPP

#include "IVISABackend.hpp"
#include "../internal/visa.h"

namespace cvisa {

    /**
     * @brief Real implementation of the IVISABackend interface using IVI Foundation VISA library.
     * 
     * This class wraps the IVI Foundation VISA C API, providing thread-safe access to
     * VISA operations. It forwards calls directly to the underlying VISA library functions.
     * 
     * @note This backend requires the IVI Foundation VISA library to be installed and
     * linked into the final executable.
     */
    class RealVISABackend : public IVISABackend {
      public:
        /**
         * @brief Opens the default VISA resource manager using IVI Foundation VISA.
         */
        ViStatus visaOpenDefaultRM(ViSession* sesn) override { return ::viOpenDefaultRM(sesn); }

        /**
         * @brief Opens a VISA session to a specific instrument using IVI Foundation VISA.
         */
        ViStatus visaOpen(ViSession sesn, const ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi) override {
            return ::viOpen(sesn, name, mode, timeout, vi);
        }

        /**
         * @brief Closes a VISA session using IVI Foundation VISA.
         */
        ViStatus visaClose(ViObject vi) override { return ::viClose(vi); }

        /**
         * @brief Sets an attribute on a VISA session using IVI Foundation VISA.
         */
        ViStatus visaSetAttribute(ViObject vi, ViAttr attr, ViAttrState attrState) override { return ::viSetAttribute(vi, attr, attrState); }

        /**
         * @brief Gets an attribute from a VISA session using IVI Foundation VISA.
         */
        ViStatus visaGetAttribute(ViObject vi, ViAttr attr, void* attrState) override { return ::viGetAttribute(vi, attr, attrState); }

        /**
         * @brief Writes data to a VISA session using IVI Foundation VISA.
         */
        ViStatus visaWrite(ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount) override { return ::viWrite(vi, buf, count, retCount); }

        /**
         * @brief Reads data from a VISA session using IVI Foundation VISA.
         */
        ViStatus visaRead(ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount) override { return ::viRead(vi, buf, count, retCount); }

        /**
         * @brief Clears a VISA session using IVI Foundation VISA.
         */
        ViStatus visaClear(ViSession vi) override { return ::viClear(vi); }

        /**
         * @brief Reads the service request status byte using IVI Foundation VISA.
         */
        ViStatus visaReadSTB(ViSession vi, ViPUInt16 status) override { return ::viReadSTB(vi, status); }

        /**
         * @brief Finds VISA resources matching an expression using IVI Foundation VISA.
         */
        ViStatus visaFindRsrc(ViSession sesn, ViConstRsrc expr, ViPFindList findList, ViPUInt32 retCount, ViRsrc instrDesc) override {
            return ::viFindRsrc(sesn, expr, findList, retCount, instrDesc);
        }

        /**
         * @brief Gets the next VISA resource from a find list using IVI Foundation VISA.
         */
        ViStatus visaFindNext(ViFindList findList, ViRsrc instrDesc) override { return ::viFindNext(findList, instrDesc); }

        /**
         * @brief Gets the status description for a VISA status code using IVI Foundation VISA.
         */
        ViStatus visaStatusDesc(ViObject vi, ViStatus status, ViChar desc[]) override { return ::viStatusDesc(vi, status, desc); }
    };

}    // namespace cvisa

#endif    // CVISA_REAL_VISA_BACKEND_HPP
