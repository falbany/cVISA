#ifndef CVISA_REAL_VISA_BACKEND_HPP
#define CVISA_REAL_VISA_BACKEND_HPP

#include "IVISABackend.hpp"
#include <visa.h>

namespace cvisa {

    /**
     * @brief Real implementation of the IVISABackend interface calling the actual VISA C library.
     */
    class RealVISABackend : public IVISABackend {
    public:
        ViStatus visaOpenDefaultRM(ViSession* sesn) override {
            return ::viOpenDefaultRM(sesn);
        }

        ViStatus visaOpen(ViSession sesn, const char* name, ViUInt32 mode, ViUInt32 timeout, ViSession* vi) override {
            return ::viOpen(sesn, const_cast<char*>(name), mode, timeout, vi);
        }

        ViStatus visaClose(ViObject vi) override {
            return ::viClose(vi);
        }

        ViStatus visaSetAttribute(ViObject vi, ViAttr attr, ViAttrState attrState) override {
            return ::viSetAttribute(vi, attr, attrState);
        }

        ViStatus visaGetAttribute(ViObject vi, ViAttr attr, void* attrState) override {
            return ::viGetAttribute(vi, attr, attrState);
        }

        ViStatus visaWrite(ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount) override {
            return ::viWrite(vi, const_cast<ViBuf>(buf), count, retCount);
        }

        ViStatus visaRead(ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount) override {
            return ::viRead(vi, buf, count, retCount);
        }

        ViStatus visaClear(ViSession vi) override {
            return ::viClear(vi);
        }

        ViStatus visaReadSTB(ViSession vi, ViPUInt16 status) override {
            return ::viReadSTB(vi, status);
        }

        ViStatus visaFindRsrc(ViSession sesn, const char* expr, void* findList, ViPUInt32 retCount, char* instrDesc) override {
            return ::viFindRsrc(sesn, const_cast<char*>(expr), reinterpret_cast<ViFindList*>(findList), retCount, instrDesc);
        }

        ViStatus visaFindNext(void* findList, char* instrDesc) override {
            return ::viFindNext(*reinterpret_cast<ViFindList*>(findList), instrDesc);
        }

        ViStatus visaStatusDesc(ViObject vi, ViStatus status, char* desc) override {
            return ::viStatusDesc(vi, status, desc);
        }
    };

} // namespace cvisa

#endif // CVISA_REAL_VISA_BACKEND_HPP
