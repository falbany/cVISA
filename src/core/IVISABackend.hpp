#ifndef CVISA_IVISA_BACKEND_HPP
#define CVISA_IVISA_BACKEND_HPP

#include <cstdint>
#include <string>
#include <vector>

// Forward-declare VISA types to avoid including visa.h in a public header.
using ViSession = unsigned long;
using ViStatus  = long;
using ViObject  = unsigned long;
using ViAttr    = unsigned int;
using ViAttrState = unsigned long;
using ViPUInt32 = unsigned int*;
using ViUInt16  = unsigned short;
using ViPUInt16 = unsigned short*;
using ViPBuf    = unsigned char*;
using ViBuf     = unsigned char*;
using ViUInt32  = unsigned int;

// Support for basic status codes without requiring visa.h
#ifndef VI_SUCCESS
#define VI_SUCCESS           (0L)
#define VI_NULL              (0)
#define VI_ERROR_TMO         (-1073807339L)
#define VI_ERROR_RSRC_NFOUND (-1073807343L)
#define VI_ERROR_RSRC_LOCKED (-1073807342L)
#define VI_ERROR_CONN_LOST   (-1073807198L)
#define VI_ERROR_INV_EXPR    (-1073807313L)
#define VI_ERROR_NLISTENERS  (-1073807295L)
#define VI_ERROR_SYSTEM_ERROR (-1073807360L)
#endif

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
