#ifndef MOCK_VISA_H
#define MOCK_VISA_H

// --- Basic VISA Data Types ---
typedef long ViStatus;
typedef unsigned long ViSession;
typedef unsigned int ViUInt32;
typedef unsigned char ViUInt8;
typedef short ViInt16;
typedef char ViInt8;
typedef ViSession ViFindList; // ViFindList is a type of session handle

// --- VISA Completion and Error Codes ---
#define VI_SUCCESS                     (0L)
#define VI_ERROR_TMO                   (-1073807339L)
#define VI_ERROR_RSRC_NFOUND           (-1073807343L)
#define VI_ERROR_RSRC_LOCKED           (-1073807342L)
#define VI_ERROR_CONN_LOST             (-1073807198L)
#define VI_ERROR_INV_EXPR              (-1073807313L)
#define VI_ERROR_NLISTENERS            (-1073807295L)

// --- VISA Constants ---
#define VI_NULL                        (0)
#define VI_TRUE                        (1)
#define VI_FALSE                       (0)
#define VI_FIND_BUFLEN                 (256)

// --- VISA Attributes ---
#define VI_ATTR_TMO_VALUE              (0x3FFF001A)
#define VI_ATTR_TERMCHAR               (0x3FFF0018)
#define VI_ATTR_TERMCHAR_EN            (0x3FFF0038)
#define VI_ATTR_SEND_END_EN            (0x3FFF0016)

// --- Mock Function Declarations ---
#ifdef __cplusplus
extern "C" {
#endif

ViStatus viOpenDefaultRM(ViSession* vi);
ViStatus viOpen(ViSession vi, char* desc, int mode, int timeout, ViSession* new_vi);
ViStatus viClose(ViSession vi);
ViStatus viWrite(ViSession vi, unsigned char* buf, ViUInt32 count, ViUInt32* retCount);
ViStatus viRead(ViSession vi, unsigned char* buf, ViUInt32 count, ViUInt32* retCount);
ViStatus viSetAttribute(ViSession vi, int attrName, int attrValue);
ViStatus viFindRsrc(ViSession vi, char* expr, ViFindList* findList, ViUInt32* retCount, char* desc);
ViStatus viFindNext(ViFindList findList, char* desc);
ViStatus viStatusDesc(ViSession vi, ViStatus status, char* desc);

#ifdef __cplusplus
}
#endif

#endif // MOCK_VISA_H