#ifndef CVISA_MOCK_VISA_BACKEND_HPP
#define CVISA_MOCK_VISA_BACKEND_HPP

#include "core/IVISABackend.hpp"
#include <gmock/gmock.h>

namespace cvisa {

    /**
     * @brief Mock implementation of IVISABackend for unit testing.
     * 
     * This mock class uses IVI Foundation VISA types and functions,
     * allowing tests to verify VISACom behavior without a real VISA library.
     */
    class MockVISABackend : public IVISABackend {
    public:
        // IVI Foundation VISA method mocks with proper types
        MOCK_METHOD(ViStatus, visaOpenDefaultRM, (ViSession* sesn), (override));
        
        MOCK_METHOD(ViStatus, visaOpen, 
                   (ViSession sesn, const ViRsrc name, ViAccessMode mode, ViUInt32 timeout, ViPSession vi), 
                   (override));
        
        MOCK_METHOD(ViStatus, visaClose, (ViObject vi), (override));
        
        MOCK_METHOD(ViStatus, visaSetAttribute, 
                   (ViObject vi, ViAttr attr, ViAttrState attrState), 
                   (override));
        
        MOCK_METHOD(ViStatus, visaGetAttribute, 
                   (ViObject vi, ViAttr attr, void* attrState), 
                   (override));
        
        MOCK_METHOD(ViStatus, visaWrite, 
                   (ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount), 
                   (override));
        
        MOCK_METHOD(ViStatus, visaRead, 
                   (ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount), 
                   (override));
        
        MOCK_METHOD(ViStatus, visaClear, (ViSession vi), (override));
        
        MOCK_METHOD(ViStatus, visaReadSTB, (ViSession vi, ViPUInt16 status), (override));
        
        MOCK_METHOD(ViStatus, visaFindRsrc, 
                   (ViSession sesn, ViConstRsrc expr, ViPFindList findList, ViPUInt32 retCount, ViRsrc instrDesc), 
                   (override));
        
        MOCK_METHOD(ViStatus, visaFindNext, 
                   (ViFindList findList, ViRsrc instrDesc), 
                   (override));
        
        MOCK_METHOD(ViStatus, visaStatusDesc, 
                   (ViObject vi, ViStatus status, ViChar desc[]), 
                   (override));
    };

} // namespace cvisa

#endif // CVISA_MOCK_VISA_BACKEND_HPP
