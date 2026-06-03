#ifndef CVISA_IVISA_BACKEND_HPP
#define CVISA_IVISA_BACKEND_HPP

#include <cstdint>
#include <string>
#include <vector>

// Include IVI Foundation VISA types from internal folder
#include "../internal/visatype.h"
#include "../internal/visa.h"

namespace cvisa {

    /**
     * @brief Abstract interface for the IVI Foundation VISA C API.
     * 
     * This interface provides abstraction over the VISA C API, allowing for mocking
     * and testing without requiring an actual VISA library. It implements the IVI
     * Foundation VISA standard.
     * 
     * @see https://www.ivifoundation.org/
     */
    class IVISABackend {
    public:
        virtual ~IVISABackend() = default;

        /**
         * @brief Opens the default VISA resource manager.
         * @param sesn Pointer to store the resource manager session handle.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaOpenDefaultRM(ViSession* sesn) = 0;

        /**
         * @brief Opens a VISA session to a specific resource.
         * @param sesn Resource manager session handle.
         * @param name Resource descriptor string (e.g., "GPIB0::1::INSTR").
         * @param mode VISA open mode (typically VI_NULL).
         * @param timeout Timeout in milliseconds.
         * @param vi Pointer to store the instrument session handle.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaOpen(ViSession sesn, const ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi) = 0;

        /**
         * @brief Closes a VISA session.
         * @param vi Session handle to close.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaClose(ViObject vi) = 0;

        /**
         * @brief Sets an attribute on a VISA session.
         * @param vi Session handle.
         * @param attr Attribute ID.
         * @param attrState Attribute value.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaSetAttribute(ViObject vi, ViAttr attr, ViAttrState attrState) = 0;

        /**
         * @brief Gets an attribute from a VISA session.
         * @param vi Session handle.
         * @param attr Attribute ID.
         * @param attrState Pointer to store the attribute value.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaGetAttribute(ViObject vi, ViAttr attr, void* attrState) = 0;

        /**
         * @brief Writes data to a VISA session.
         * @param vi Session handle.
         * @param buf Data buffer to send.
         * @param count Number of bytes to write.
         * @param retCount Pointer to store the number of bytes written.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaWrite(ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount) = 0;

        /**
         * @brief Reads data from a VISA session.
         * @param vi Session handle.
         * @param buf Buffer to store the read data.
         * @param count Maximum number of bytes to read.
         * @param retCount Pointer to store the number of bytes read.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaRead(ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount) = 0;

        /**
         * @brief Clears a VISA session.
         * @param vi Session handle.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaClear(ViSession vi) = 0;

        /**
         * @brief Reads the service request status byte.
         * @param vi Session handle.
         * @param status Pointer to store the status byte.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaReadSTB(ViSession vi, ViPUInt16 status) = 0;

        /**
         * @brief Finds VISA resources matching an expression.
         * @param sesn Resource manager session handle.
         * @param expr Expression to match resources.
         * @param findList Pointer to store the find list handle.
         * @param retCount Pointer to store the count of matching resources.
         * @param instrDesc Buffer to store the first resource descriptor.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaFindRsrc(ViSession sesn, ViConstRsrc expr, ViPFindList findList, ViPUInt32 retCount, ViRsrc instrDesc) = 0;

        /**
         * @brief Gets the next VISA resource from a find list.
         * @param findList Find list handle.
         * @param instrDesc Buffer to store the resource descriptor.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaFindNext(ViFindList findList, ViRsrc instrDesc) = 0;

        /**
         * @brief Gets the status description for a VISA status code.
         * @param vi Session handle (or VI_NULL).
         * @param status VISA status code.
         * @param desc Buffer to store the status description.
         * @return VI_SUCCESS on success, otherwise a VISA error code.
         */
        virtual ViStatus visaStatusDesc(ViObject vi, ViStatus status, ViChar desc[]) = 0;
    };

} // namespace cvisa

#endif // CVISA_IVISA_BACKEND_HPP
