#ifndef CVISA_MOCK_VISA_BACKEND_HPP
#define CVISA_MOCK_VISA_BACKEND_HPP

#include "core/IVISABackend.hpp"
#include <gmock/gmock.h>

namespace cvisa {

    class MockVISABackend : public IVISABackend {
    public:
        MOCK_METHOD(ViStatus, visaOpenDefaultRM, (ViSession* sesn), (override));
        MOCK_METHOD(ViStatus, visaOpen, (ViSession sesn, const char* name, ViUInt32 mode, ViUInt32 timeout, ViSession* vi), (override));
        MOCK_METHOD(ViStatus, visaClose, (ViObject vi), (override));
        MOCK_METHOD(ViStatus, visaSetAttribute, (ViObject vi, ViAttr attr, ViAttrState attrState), (override));
        MOCK_METHOD(ViStatus, visaGetAttribute, (ViObject vi, ViAttr attr, void* attrState), (override));
        MOCK_METHOD(ViStatus, visaWrite, (ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount), (override));
        MOCK_METHOD(ViStatus, visaRead, (ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount), (override));
        MOCK_METHOD(ViStatus, visaClear, (ViSession vi), (override));
        MOCK_METHOD(ViStatus, visaReadSTB, (ViSession vi, ViPUInt16 status), (override));
        MOCK_METHOD(ViStatus, visaFindRsrc, (ViSession sesn, const char* expr, void* findList, ViPUInt32 retCount, char* instrDesc), (override));
        MOCK_METHOD(ViStatus, visaFindNext, (void* findList, char* instrDesc), (override));
        MOCK_METHOD(ViStatus, visaStatusDesc, (ViObject vi, ViStatus status, char* desc), (override));
    };

} // namespace cvisa

#endif // CVISA_MOCK_VISA_BACKEND_HPP
