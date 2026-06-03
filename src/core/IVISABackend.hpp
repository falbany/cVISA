#ifndef CVISA_IVISA_BACKEND_HPP
#define CVISA_IVISA_BACKEND_HPP

#include <cstdint>
#include <string>
#include <vector>

// Include VISA types from internal folder to ensure compatibility with the actual VISA SDK
#include "../internal/visa.h"

namespace cvisa {

    /**
     * @brief Abstract interface for the VISA C API.
     * 
     * This interface allows mocking the VISA C API for unit testing.
     */
    class IVISABackend {
    public:
        virtual ~IVISABackend() = default;

        virtual ViStatus visaOpenDefaultRM(ViSession* sesn) = 0;
        virtual ViStatus visaOpen(ViSession sesn, const char* name, ViUInt32 mode, ViUInt32 timeout, ViSession* vi) = 0;
        virtual ViStatus visaClose(ViObject vi) = 0;
        virtual ViStatus visaSetAttribute(ViObject vi, ViAttr attr, ViAttrState attrState) = 0;
        virtual ViStatus visaGetAttribute(ViObject vi, ViAttr attr, void* attrState) = 0;
        virtual ViStatus visaWrite(ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount) = 0;
        virtual ViStatus visaRead(ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount) = 0;
        virtual ViStatus visaClear(ViSession vi) = 0;
        virtual ViStatus visaReadSTB(ViSession vi, ViPUInt16 status) = 0;
        virtual ViStatus visaFindRsrc(ViSession sesn, const char* expr, void* findList, ViPUInt32 retCount, char* instrDesc) = 0;
        virtual ViStatus visaFindNext(void* findList, char* instrDesc) = 0;
        virtual ViStatus visaStatusDesc(ViObject vi, ViStatus status, char* desc) = 0;
    };

} // namespace cvisa

#endif // CVISA_IVISA_BACKEND_HPP
