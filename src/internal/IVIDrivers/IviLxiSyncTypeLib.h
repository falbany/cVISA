

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0626 */
/* at Tue Jan 19 03:14:07 2038
 */
/* Compiler settings for IviLxiSyncTypeLib.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0626 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __IviLxiSyncTypeLib_h__
#define __IviLxiSyncTypeLib_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if _CONTROL_FLOW_GUARD_XFG
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IIviLxiSync_FWD_DEFINED__
#define __IIviLxiSync_FWD_DEFINED__
typedef interface IIviLxiSync IIviLxiSync;

#endif 	/* __IIviLxiSync_FWD_DEFINED__ */


#ifndef __IIviLxiSyncArm_FWD_DEFINED__
#define __IIviLxiSyncArm_FWD_DEFINED__
typedef interface IIviLxiSyncArm IIviLxiSyncArm;

#endif 	/* __IIviLxiSyncArm_FWD_DEFINED__ */


#ifndef __IIviLxiSyncArmAlarm_FWD_DEFINED__
#define __IIviLxiSyncArmAlarm_FWD_DEFINED__
typedef interface IIviLxiSyncArmAlarm IIviLxiSyncArmAlarm;

#endif 	/* __IIviLxiSyncArmAlarm_FWD_DEFINED__ */


#ifndef __IIviLxiSyncArmAlarms_FWD_DEFINED__
#define __IIviLxiSyncArmAlarms_FWD_DEFINED__
typedef interface IIviLxiSyncArmAlarms IIviLxiSyncArmAlarms;

#endif 	/* __IIviLxiSyncArmAlarms_FWD_DEFINED__ */


#ifndef __IIviLxiSyncArmSource_FWD_DEFINED__
#define __IIviLxiSyncArmSource_FWD_DEFINED__
typedef interface IIviLxiSyncArmSource IIviLxiSyncArmSource;

#endif 	/* __IIviLxiSyncArmSource_FWD_DEFINED__ */


#ifndef __IIviLxiSyncArmSources_FWD_DEFINED__
#define __IIviLxiSyncArmSources_FWD_DEFINED__
typedef interface IIviLxiSyncArmSources IIviLxiSyncArmSources;

#endif 	/* __IIviLxiSyncArmSources_FWD_DEFINED__ */


#ifndef __IIviLxiSyncEvent_FWD_DEFINED__
#define __IIviLxiSyncEvent_FWD_DEFINED__
typedef interface IIviLxiSyncEvent IIviLxiSyncEvent;

#endif 	/* __IIviLxiSyncEvent_FWD_DEFINED__ */


#ifndef __IIviLxiSyncEventLog_FWD_DEFINED__
#define __IIviLxiSyncEventLog_FWD_DEFINED__
typedef interface IIviLxiSyncEventLog IIviLxiSyncEventLog;

#endif 	/* __IIviLxiSyncEventLog_FWD_DEFINED__ */


#ifndef __IIviLxiSyncEvents_FWD_DEFINED__
#define __IIviLxiSyncEvents_FWD_DEFINED__
typedef interface IIviLxiSyncEvents IIviLxiSyncEvents;

#endif 	/* __IIviLxiSyncEvents_FWD_DEFINED__ */


#ifndef __IIviLxiSyncTime_FWD_DEFINED__
#define __IIviLxiSyncTime_FWD_DEFINED__
typedef interface IIviLxiSyncTime IIviLxiSyncTime;

#endif 	/* __IIviLxiSyncTime_FWD_DEFINED__ */


#ifndef __IIviLxiSyncTrigger_FWD_DEFINED__
#define __IIviLxiSyncTrigger_FWD_DEFINED__
typedef interface IIviLxiSyncTrigger IIviLxiSyncTrigger;

#endif 	/* __IIviLxiSyncTrigger_FWD_DEFINED__ */


#ifndef __IIviLxiSyncTriggerAlarm_FWD_DEFINED__
#define __IIviLxiSyncTriggerAlarm_FWD_DEFINED__
typedef interface IIviLxiSyncTriggerAlarm IIviLxiSyncTriggerAlarm;

#endif 	/* __IIviLxiSyncTriggerAlarm_FWD_DEFINED__ */


#ifndef __IIviLxiSyncTriggerAlarms_FWD_DEFINED__
#define __IIviLxiSyncTriggerAlarms_FWD_DEFINED__
typedef interface IIviLxiSyncTriggerAlarms IIviLxiSyncTriggerAlarms;

#endif 	/* __IIviLxiSyncTriggerAlarms_FWD_DEFINED__ */


#ifndef __IIviLxiSyncTriggerSource_FWD_DEFINED__
#define __IIviLxiSyncTriggerSource_FWD_DEFINED__
typedef interface IIviLxiSyncTriggerSource IIviLxiSyncTriggerSource;

#endif 	/* __IIviLxiSyncTriggerSource_FWD_DEFINED__ */


#ifndef __IIviLxiSyncTriggerSources_FWD_DEFINED__
#define __IIviLxiSyncTriggerSources_FWD_DEFINED__
typedef interface IIviLxiSyncTriggerSources IIviLxiSyncTriggerSources;

#endif 	/* __IIviLxiSyncTriggerSources_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_IviLxiSyncTypeLib_0000_0000 */
/* [local] */ 

#pragma external_header(push)
#pragma external_header(push)
#pragma once
#pragma warning(push)
#pragma warning(disable:4668) 
#pragma external_header(push)
#pragma once
#pragma region Input Buffer SAL 1 compatibility macros
#pragma endregion Input Buffer SAL 1 compatibility macros
#pragma external_header(push)
#pragma once
#pragma external_header(pop)
#pragma external_header(pop)
#pragma external_header(push)
#pragma external_header(pop)
#pragma external_header(push)
#pragma once
#pragma external_header(pop)
#pragma warning(pop)
#pragma external_header(pop)
#pragma external_header(pop)


extern RPC_IF_HANDLE __MIDL_itf_IviLxiSyncTypeLib_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IviLxiSyncTypeLib_0000_0000_v0_0_s_ifspec;


#ifndef __IviLxiSyncLib_LIBRARY_DEFINED__
#define __IviLxiSyncLib_LIBRARY_DEFINED__

/* library IviLxiSyncLib */
/* [helpfile][helpstring][version][uuid] */ 
















typedef /* [helpcontext][helpstring] */ 
enum IviLxiSyncErrorCodesEnum
    {
        E_IVILXISYNC_ALARM_TIME_INVALID	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209215 ) ),
        E_IVILXISYNC_EVENT_SOURCE_EXISTS	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209214 ) ),
        E_IVILXISYNC_OUT_OF_EVENT_RESOURCES	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209213 ) ),
        E_IVILXISYNC_EVENT_SOURCE_DOES_NOT_EXIST	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209212 ) ),
        E_IVILXISYNC_EVENT_SOURCE_NOT_SET	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209211 ) ),
        E_IVILXISYNC_INVALID_EVENT_SOURCE	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209210 ) ),
        E_IVILXISYNC_ALARM_EXISTS	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209209 ) ),
        E_IVILXISYNC_ALARM_DOES_NOT_EXIST	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209208 ) ),
        E_IVILXISYNC_WIRED_OR_MODE_INVALID	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209207 ) ),
        E_IVILXISYNC_CANT_REMOVE_RESERVED_REPEATED_CAPABILITY	= ( HRESULT  )(( ( ( ( unsigned long  )1 << 31 )  | ( ( unsigned long  )4 << 16 )  )  | ( unsigned long  )-2147209200 ) )
    } 	IviLxiSyncErrorCodesEnum;

typedef /* [helpcontext][helpstring][v1_enum][public] */ 
enum IviLxiSyncSourceSlopeEnum
    {
        IviLxiSyncSourceSlopeRise	= 0,
        IviLxiSyncSourceSlopeFall	= 1
    } 	IviLxiSyncSourceSlopeEnum;

typedef /* [helpcontext][helpstring][v1_enum][public] */ 
enum IviLxiSyncArmSourceDetectionEnum
    {
        IviLxiSyncArmSourceDetectionRise	= 0,
        IviLxiSyncArmSourceDetectionFall	= 1,
        IviLxiSyncArmSourceDetectionHigh	= 2,
        IviLxiSyncArmSourceDetectionLow	= 3
    } 	IviLxiSyncArmSourceDetectionEnum;

typedef /* [helpcontext][helpstring][v1_enum][public] */ 
enum IviLxiSyncEventDriveModeEnum
    {
        IviLxiSyncEventDriveModeDriven	= 0,
        IviLxiSyncEventDriveModeOff	= 1,
        IviLxiSyncEventDriveModeWiredOr	= 2
    } 	IviLxiSyncEventDriveModeEnum;

typedef /* [helpcontext][helpstring][v1_enum][public] */ 
enum IviLxiSyncTriggerSourceDetectionEnum
    {
        IviLxiSyncTriggerSourceDetectionRise	= 0,
        IviLxiSyncTriggerSourceDetectionFall	= 1
    } 	IviLxiSyncTriggerSourceDetectionEnum;


EXTERN_C const IID LIBID_IviLxiSyncLib;

#ifndef __IIviLxiSync_INTERFACE_DEFINED__
#define __IIviLxiSync_INTERFACE_DEFINED__

/* interface IIviLxiSync */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSync;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5346-A398-11D4-BA58-000064657374")
    IIviLxiSync : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Arm( 
            /* [retval][out] */ IIviLxiSyncArm **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EventLog( 
            /* [retval][out] */ IIviLxiSyncEventLog **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Events( 
            /* [retval][out] */ IIviLxiSyncEvents **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Time( 
            /* [retval][out] */ IIviLxiSyncTime **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Trigger( 
            /* [retval][out] */ IIviLxiSyncTrigger **val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSync * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSync * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSync * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSync, get_Arm)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Arm )( 
            IIviLxiSync * This,
            /* [retval][out] */ IIviLxiSyncArm **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSync, get_EventLog)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EventLog )( 
            IIviLxiSync * This,
            /* [retval][out] */ IIviLxiSyncEventLog **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSync, get_Events)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Events )( 
            IIviLxiSync * This,
            /* [retval][out] */ IIviLxiSyncEvents **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSync, get_Time)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Time )( 
            IIviLxiSync * This,
            /* [retval][out] */ IIviLxiSyncTime **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSync, get_Trigger)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Trigger )( 
            IIviLxiSync * This,
            /* [retval][out] */ IIviLxiSyncTrigger **val);
        
        END_INTERFACE
    } IIviLxiSyncVtbl;

    interface IIviLxiSync
    {
        CONST_VTBL struct IIviLxiSyncVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSync_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSync_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSync_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSync_get_Arm(This,val)	\
    ( (This)->lpVtbl -> get_Arm(This,val) ) 

#define IIviLxiSync_get_EventLog(This,val)	\
    ( (This)->lpVtbl -> get_EventLog(This,val) ) 

#define IIviLxiSync_get_Events(This,val)	\
    ( (This)->lpVtbl -> get_Events(This,val) ) 

#define IIviLxiSync_get_Time(This,val)	\
    ( (This)->lpVtbl -> get_Time(This,val) ) 

#define IIviLxiSync_get_Trigger(This,val)	\
    ( (This)->lpVtbl -> get_Trigger(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSync_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncArm_INTERFACE_DEFINED__
#define __IIviLxiSyncArm_INTERFACE_DEFINED__

/* interface IIviLxiSyncArm */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncArm;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5347-A398-11D4-BA58-000064657374")
    IIviLxiSyncArm : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Sources( 
            /* [retval][out] */ IIviLxiSyncArmSources **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ArmCount( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ArmCount( 
            /* [in] */ long val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Delay( 
            /* [retval][out] */ double *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Delay( 
            /* [in] */ double val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Alarms( 
            /* [retval][out] */ IIviLxiSyncArmAlarms **val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncArmVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncArm * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncArm * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncArm * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArm, get_Sources)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sources )( 
            IIviLxiSyncArm * This,
            /* [retval][out] */ IIviLxiSyncArmSources **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArm, get_ArmCount)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ArmCount )( 
            IIviLxiSyncArm * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArm, put_ArmCount)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ArmCount )( 
            IIviLxiSyncArm * This,
            /* [in] */ long val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArm, get_Delay)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Delay )( 
            IIviLxiSyncArm * This,
            /* [retval][out] */ double *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArm, put_Delay)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Delay )( 
            IIviLxiSyncArm * This,
            /* [in] */ double val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArm, get_Alarms)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alarms )( 
            IIviLxiSyncArm * This,
            /* [retval][out] */ IIviLxiSyncArmAlarms **val);
        
        END_INTERFACE
    } IIviLxiSyncArmVtbl;

    interface IIviLxiSyncArm
    {
        CONST_VTBL struct IIviLxiSyncArmVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncArm_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncArm_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncArm_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncArm_get_Sources(This,val)	\
    ( (This)->lpVtbl -> get_Sources(This,val) ) 

#define IIviLxiSyncArm_get_ArmCount(This,val)	\
    ( (This)->lpVtbl -> get_ArmCount(This,val) ) 

#define IIviLxiSyncArm_put_ArmCount(This,val)	\
    ( (This)->lpVtbl -> put_ArmCount(This,val) ) 

#define IIviLxiSyncArm_get_Delay(This,val)	\
    ( (This)->lpVtbl -> get_Delay(This,val) ) 

#define IIviLxiSyncArm_put_Delay(This,val)	\
    ( (This)->lpVtbl -> put_Delay(This,val) ) 

#define IIviLxiSyncArm_get_Alarms(This,val)	\
    ( (This)->lpVtbl -> get_Alarms(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncArm_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncArmAlarm_INTERFACE_DEFINED__
#define __IIviLxiSyncArmAlarm_INTERFACE_DEFINED__

/* interface IIviLxiSyncArmAlarm */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncArmAlarm;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5348-A398-11D4-BA58-000064657374")
    IIviLxiSyncArmAlarm : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Configure( 
            /* [in] */ VARIANT_BOOL Enabled,
            /* [in] */ double TimeSeconds,
            /* [in] */ double TimeFraction,
            /* [in] */ double Period,
            /* [in] */ long RepeatCount) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TimeSeconds( 
            /* [retval][out] */ double *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TimeSeconds( 
            /* [in] */ double val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TimeFraction( 
            /* [retval][out] */ double *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TimeFraction( 
            /* [in] */ double val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Period( 
            /* [retval][out] */ double *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Period( 
            /* [in] */ double val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RepeatCount( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RepeatCount( 
            /* [in] */ long val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncArmAlarmVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncArmAlarm * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncArmAlarm * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncArmAlarm * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, Configure)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Configure )( 
            IIviLxiSyncArmAlarm * This,
            /* [in] */ VARIANT_BOOL Enabled,
            /* [in] */ double TimeSeconds,
            /* [in] */ double TimeFraction,
            /* [in] */ double Period,
            /* [in] */ long RepeatCount);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, get_TimeSeconds)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeSeconds )( 
            IIviLxiSyncArmAlarm * This,
            /* [retval][out] */ double *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, put_TimeSeconds)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimeSeconds )( 
            IIviLxiSyncArmAlarm * This,
            /* [in] */ double val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, get_TimeFraction)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeFraction )( 
            IIviLxiSyncArmAlarm * This,
            /* [retval][out] */ double *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, put_TimeFraction)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimeFraction )( 
            IIviLxiSyncArmAlarm * This,
            /* [in] */ double val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, get_Period)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Period )( 
            IIviLxiSyncArmAlarm * This,
            /* [retval][out] */ double *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, put_Period)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Period )( 
            IIviLxiSyncArmAlarm * This,
            /* [in] */ double val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, get_RepeatCount)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepeatCount )( 
            IIviLxiSyncArmAlarm * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, put_RepeatCount)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepeatCount )( 
            IIviLxiSyncArmAlarm * This,
            /* [in] */ long val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, get_Enabled)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IIviLxiSyncArmAlarm * This,
            /* [retval][out] */ VARIANT_BOOL *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarm, put_Enabled)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IIviLxiSyncArmAlarm * This,
            /* [in] */ VARIANT_BOOL val);
        
        END_INTERFACE
    } IIviLxiSyncArmAlarmVtbl;

    interface IIviLxiSyncArmAlarm
    {
        CONST_VTBL struct IIviLxiSyncArmAlarmVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncArmAlarm_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncArmAlarm_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncArmAlarm_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncArmAlarm_Configure(This,Enabled,TimeSeconds,TimeFraction,Period,RepeatCount)	\
    ( (This)->lpVtbl -> Configure(This,Enabled,TimeSeconds,TimeFraction,Period,RepeatCount) ) 

#define IIviLxiSyncArmAlarm_get_TimeSeconds(This,val)	\
    ( (This)->lpVtbl -> get_TimeSeconds(This,val) ) 

#define IIviLxiSyncArmAlarm_put_TimeSeconds(This,val)	\
    ( (This)->lpVtbl -> put_TimeSeconds(This,val) ) 

#define IIviLxiSyncArmAlarm_get_TimeFraction(This,val)	\
    ( (This)->lpVtbl -> get_TimeFraction(This,val) ) 

#define IIviLxiSyncArmAlarm_put_TimeFraction(This,val)	\
    ( (This)->lpVtbl -> put_TimeFraction(This,val) ) 

#define IIviLxiSyncArmAlarm_get_Period(This,val)	\
    ( (This)->lpVtbl -> get_Period(This,val) ) 

#define IIviLxiSyncArmAlarm_put_Period(This,val)	\
    ( (This)->lpVtbl -> put_Period(This,val) ) 

#define IIviLxiSyncArmAlarm_get_RepeatCount(This,val)	\
    ( (This)->lpVtbl -> get_RepeatCount(This,val) ) 

#define IIviLxiSyncArmAlarm_put_RepeatCount(This,val)	\
    ( (This)->lpVtbl -> put_RepeatCount(This,val) ) 

#define IIviLxiSyncArmAlarm_get_Enabled(This,val)	\
    ( (This)->lpVtbl -> get_Enabled(This,val) ) 

#define IIviLxiSyncArmAlarm_put_Enabled(This,val)	\
    ( (This)->lpVtbl -> put_Enabled(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncArmAlarm_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncArmAlarms_INTERFACE_DEFINED__
#define __IIviLxiSyncArmAlarms_INTERFACE_DEFINED__

/* interface IIviLxiSyncArmAlarms */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncArmAlarms;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5349-A398-11D4-BA58-000064657374")
    IIviLxiSyncArmAlarms : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DisableAll( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR AlarmName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR AlarmName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveAllCustomArmAlarms( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncArmAlarm **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncArmAlarmsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncArmAlarms * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncArmAlarms * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncArmAlarms * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarms, DisableAll)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableAll )( 
            IIviLxiSyncArmAlarms * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarms, Add)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IIviLxiSyncArmAlarms * This,
            /* [in] */ BSTR AlarmName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarms, Remove)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IIviLxiSyncArmAlarms * This,
            /* [in] */ BSTR AlarmName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarms, RemoveAllCustomArmAlarms)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllCustomArmAlarms )( 
            IIviLxiSyncArmAlarms * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarms, get_Count)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IIviLxiSyncArmAlarms * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarms, get_Item)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IIviLxiSyncArmAlarms * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncArmAlarm **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmAlarms, get_Name)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IIviLxiSyncArmAlarms * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val);
        
        END_INTERFACE
    } IIviLxiSyncArmAlarmsVtbl;

    interface IIviLxiSyncArmAlarms
    {
        CONST_VTBL struct IIviLxiSyncArmAlarmsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncArmAlarms_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncArmAlarms_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncArmAlarms_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncArmAlarms_DisableAll(This)	\
    ( (This)->lpVtbl -> DisableAll(This) ) 

#define IIviLxiSyncArmAlarms_Add(This,AlarmName)	\
    ( (This)->lpVtbl -> Add(This,AlarmName) ) 

#define IIviLxiSyncArmAlarms_Remove(This,AlarmName)	\
    ( (This)->lpVtbl -> Remove(This,AlarmName) ) 

#define IIviLxiSyncArmAlarms_RemoveAllCustomArmAlarms(This)	\
    ( (This)->lpVtbl -> RemoveAllCustomArmAlarms(This) ) 

#define IIviLxiSyncArmAlarms_get_Count(This,val)	\
    ( (This)->lpVtbl -> get_Count(This,val) ) 

#define IIviLxiSyncArmAlarms_get_Item(This,Name,val)	\
    ( (This)->lpVtbl -> get_Item(This,Name,val) ) 

#define IIviLxiSyncArmAlarms_get_Name(This,Index,val)	\
    ( (This)->lpVtbl -> get_Name(This,Index,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncArmAlarms_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncArmSource_INTERFACE_DEFINED__
#define __IIviLxiSyncArmSource_INTERFACE_DEFINED__

/* interface IIviLxiSyncArmSource */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncArmSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED534A-A398-11D4-BA58-000064657374")
    IIviLxiSyncArmSource : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Configure( 
            /* [in] */ VARIANT_BOOL Enabled,
            /* [in] */ IviLxiSyncArmSourceDetectionEnum Detection) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Detection( 
            /* [retval][out] */ IviLxiSyncArmSourceDetectionEnum *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Detection( 
            /* [in] */ IviLxiSyncArmSourceDetectionEnum val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Filter( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Filter( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EventId( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EventId( 
            /* [in] */ BSTR val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncArmSourceVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncArmSource * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncArmSource * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncArmSource * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, Configure)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Configure )( 
            IIviLxiSyncArmSource * This,
            /* [in] */ VARIANT_BOOL Enabled,
            /* [in] */ IviLxiSyncArmSourceDetectionEnum Detection);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, get_Enabled)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IIviLxiSyncArmSource * This,
            /* [retval][out] */ VARIANT_BOOL *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, put_Enabled)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IIviLxiSyncArmSource * This,
            /* [in] */ VARIANT_BOOL val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, get_Detection)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Detection )( 
            IIviLxiSyncArmSource * This,
            /* [retval][out] */ IviLxiSyncArmSourceDetectionEnum *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, put_Detection)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Detection )( 
            IIviLxiSyncArmSource * This,
            /* [in] */ IviLxiSyncArmSourceDetectionEnum val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, get_Filter)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Filter )( 
            IIviLxiSyncArmSource * This,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, put_Filter)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Filter )( 
            IIviLxiSyncArmSource * This,
            /* [in] */ BSTR val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, get_EventId)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EventId )( 
            IIviLxiSyncArmSource * This,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSource, put_EventId)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EventId )( 
            IIviLxiSyncArmSource * This,
            /* [in] */ BSTR val);
        
        END_INTERFACE
    } IIviLxiSyncArmSourceVtbl;

    interface IIviLxiSyncArmSource
    {
        CONST_VTBL struct IIviLxiSyncArmSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncArmSource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncArmSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncArmSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncArmSource_Configure(This,Enabled,Detection)	\
    ( (This)->lpVtbl -> Configure(This,Enabled,Detection) ) 

#define IIviLxiSyncArmSource_get_Enabled(This,val)	\
    ( (This)->lpVtbl -> get_Enabled(This,val) ) 

#define IIviLxiSyncArmSource_put_Enabled(This,val)	\
    ( (This)->lpVtbl -> put_Enabled(This,val) ) 

#define IIviLxiSyncArmSource_get_Detection(This,val)	\
    ( (This)->lpVtbl -> get_Detection(This,val) ) 

#define IIviLxiSyncArmSource_put_Detection(This,val)	\
    ( (This)->lpVtbl -> put_Detection(This,val) ) 

#define IIviLxiSyncArmSource_get_Filter(This,val)	\
    ( (This)->lpVtbl -> get_Filter(This,val) ) 

#define IIviLxiSyncArmSource_put_Filter(This,val)	\
    ( (This)->lpVtbl -> put_Filter(This,val) ) 

#define IIviLxiSyncArmSource_get_EventId(This,val)	\
    ( (This)->lpVtbl -> get_EventId(This,val) ) 

#define IIviLxiSyncArmSource_put_EventId(This,val)	\
    ( (This)->lpVtbl -> put_EventId(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncArmSource_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncArmSources_INTERFACE_DEFINED__
#define __IIviLxiSyncArmSources_INTERFACE_DEFINED__

/* interface IIviLxiSyncArmSources */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncArmSources;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED534B-A398-11D4-BA58-000064657374")
    IIviLxiSyncArmSources : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR SourceName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR SourceName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DisableAll( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveAllCustomArmSources( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncArmSource **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_OrEnabled( 
            /* [retval][out] */ VARIANT_BOOL *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_OrEnabled( 
            /* [in] */ VARIANT_BOOL val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncArmSourcesVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncArmSources * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncArmSources * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncArmSources * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, Add)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IIviLxiSyncArmSources * This,
            /* [in] */ BSTR SourceName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, Remove)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IIviLxiSyncArmSources * This,
            /* [in] */ BSTR SourceName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, DisableAll)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableAll )( 
            IIviLxiSyncArmSources * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, RemoveAllCustomArmSources)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllCustomArmSources )( 
            IIviLxiSyncArmSources * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, get_Count)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IIviLxiSyncArmSources * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, get_Item)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IIviLxiSyncArmSources * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncArmSource **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, get_Name)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IIviLxiSyncArmSources * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, get_OrEnabled)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OrEnabled )( 
            IIviLxiSyncArmSources * This,
            /* [retval][out] */ VARIANT_BOOL *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncArmSources, put_OrEnabled)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OrEnabled )( 
            IIviLxiSyncArmSources * This,
            /* [in] */ VARIANT_BOOL val);
        
        END_INTERFACE
    } IIviLxiSyncArmSourcesVtbl;

    interface IIviLxiSyncArmSources
    {
        CONST_VTBL struct IIviLxiSyncArmSourcesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncArmSources_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncArmSources_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncArmSources_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncArmSources_Add(This,SourceName)	\
    ( (This)->lpVtbl -> Add(This,SourceName) ) 

#define IIviLxiSyncArmSources_Remove(This,SourceName)	\
    ( (This)->lpVtbl -> Remove(This,SourceName) ) 

#define IIviLxiSyncArmSources_DisableAll(This)	\
    ( (This)->lpVtbl -> DisableAll(This) ) 

#define IIviLxiSyncArmSources_RemoveAllCustomArmSources(This)	\
    ( (This)->lpVtbl -> RemoveAllCustomArmSources(This) ) 

#define IIviLxiSyncArmSources_get_Count(This,val)	\
    ( (This)->lpVtbl -> get_Count(This,val) ) 

#define IIviLxiSyncArmSources_get_Item(This,Name,val)	\
    ( (This)->lpVtbl -> get_Item(This,Name,val) ) 

#define IIviLxiSyncArmSources_get_Name(This,Index,val)	\
    ( (This)->lpVtbl -> get_Name(This,Index,val) ) 

#define IIviLxiSyncArmSources_get_OrEnabled(This,val)	\
    ( (This)->lpVtbl -> get_OrEnabled(This,val) ) 

#define IIviLxiSyncArmSources_put_OrEnabled(This,val)	\
    ( (This)->lpVtbl -> put_OrEnabled(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncArmSources_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncEvent_INTERFACE_DEFINED__
#define __IIviLxiSyncEvent_INTERFACE_DEFINED__

/* interface IIviLxiSyncEvent */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED534C-A398-11D4-BA58-000064657374")
    IIviLxiSyncEvent : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Configure( 
            /* [in] */ IviLxiSyncEventDriveModeEnum DriveMode,
            /* [in] */ BSTR Source,
            /* [in] */ BSTR DestinationPath,
            /* [in] */ IviLxiSyncSourceSlopeEnum Slope) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Source( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Source( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DestinationPath( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DestinationPath( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Slope( 
            /* [retval][out] */ IviLxiSyncSourceSlopeEnum *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Slope( 
            /* [in] */ IviLxiSyncSourceSlopeEnum val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_DriveMode( 
            /* [retval][out] */ IviLxiSyncEventDriveModeEnum *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_DriveMode( 
            /* [in] */ IviLxiSyncEventDriveModeEnum val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncEventVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncEvent * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncEvent * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncEvent * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, Configure)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Configure )( 
            IIviLxiSyncEvent * This,
            /* [in] */ IviLxiSyncEventDriveModeEnum DriveMode,
            /* [in] */ BSTR Source,
            /* [in] */ BSTR DestinationPath,
            /* [in] */ IviLxiSyncSourceSlopeEnum Slope);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, get_Source)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Source )( 
            IIviLxiSyncEvent * This,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, put_Source)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Source )( 
            IIviLxiSyncEvent * This,
            /* [in] */ BSTR val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, get_DestinationPath)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DestinationPath )( 
            IIviLxiSyncEvent * This,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, put_DestinationPath)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DestinationPath )( 
            IIviLxiSyncEvent * This,
            /* [in] */ BSTR val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, get_Slope)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Slope )( 
            IIviLxiSyncEvent * This,
            /* [retval][out] */ IviLxiSyncSourceSlopeEnum *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, put_Slope)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Slope )( 
            IIviLxiSyncEvent * This,
            /* [in] */ IviLxiSyncSourceSlopeEnum val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, get_DriveMode)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DriveMode )( 
            IIviLxiSyncEvent * This,
            /* [retval][out] */ IviLxiSyncEventDriveModeEnum *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvent, put_DriveMode)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DriveMode )( 
            IIviLxiSyncEvent * This,
            /* [in] */ IviLxiSyncEventDriveModeEnum val);
        
        END_INTERFACE
    } IIviLxiSyncEventVtbl;

    interface IIviLxiSyncEvent
    {
        CONST_VTBL struct IIviLxiSyncEventVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncEvent_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncEvent_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncEvent_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncEvent_Configure(This,DriveMode,Source,DestinationPath,Slope)	\
    ( (This)->lpVtbl -> Configure(This,DriveMode,Source,DestinationPath,Slope) ) 

#define IIviLxiSyncEvent_get_Source(This,val)	\
    ( (This)->lpVtbl -> get_Source(This,val) ) 

#define IIviLxiSyncEvent_put_Source(This,val)	\
    ( (This)->lpVtbl -> put_Source(This,val) ) 

#define IIviLxiSyncEvent_get_DestinationPath(This,val)	\
    ( (This)->lpVtbl -> get_DestinationPath(This,val) ) 

#define IIviLxiSyncEvent_put_DestinationPath(This,val)	\
    ( (This)->lpVtbl -> put_DestinationPath(This,val) ) 

#define IIviLxiSyncEvent_get_Slope(This,val)	\
    ( (This)->lpVtbl -> get_Slope(This,val) ) 

#define IIviLxiSyncEvent_put_Slope(This,val)	\
    ( (This)->lpVtbl -> put_Slope(This,val) ) 

#define IIviLxiSyncEvent_get_DriveMode(This,val)	\
    ( (This)->lpVtbl -> get_DriveMode(This,val) ) 

#define IIviLxiSyncEvent_put_DriveMode(This,val)	\
    ( (This)->lpVtbl -> put_DriveMode(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncEvent_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncEventLog_INTERFACE_DEFINED__
#define __IIviLxiSyncEventLog_INTERFACE_DEFINED__

/* interface IIviLxiSyncEventLog */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncEventLog;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED534D-A398-11D4-BA58-000064657374")
    IIviLxiSyncEventLog : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetNextEntry( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EntryCount( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncEventLogVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncEventLog * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncEventLog * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncEventLog * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEventLog, Clear)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IIviLxiSyncEventLog * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEventLog, GetNextEntry)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNextEntry )( 
            IIviLxiSyncEventLog * This,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEventLog, get_EntryCount)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EntryCount )( 
            IIviLxiSyncEventLog * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEventLog, get_Enabled)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IIviLxiSyncEventLog * This,
            /* [retval][out] */ VARIANT_BOOL *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEventLog, put_Enabled)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IIviLxiSyncEventLog * This,
            /* [in] */ VARIANT_BOOL val);
        
        END_INTERFACE
    } IIviLxiSyncEventLogVtbl;

    interface IIviLxiSyncEventLog
    {
        CONST_VTBL struct IIviLxiSyncEventLogVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncEventLog_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncEventLog_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncEventLog_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncEventLog_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#define IIviLxiSyncEventLog_GetNextEntry(This,val)	\
    ( (This)->lpVtbl -> GetNextEntry(This,val) ) 

#define IIviLxiSyncEventLog_get_EntryCount(This,val)	\
    ( (This)->lpVtbl -> get_EntryCount(This,val) ) 

#define IIviLxiSyncEventLog_get_Enabled(This,val)	\
    ( (This)->lpVtbl -> get_Enabled(This,val) ) 

#define IIviLxiSyncEventLog_put_Enabled(This,val)	\
    ( (This)->lpVtbl -> put_Enabled(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncEventLog_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncEvents_INTERFACE_DEFINED__
#define __IIviLxiSyncEvents_INTERFACE_DEFINED__

/* interface IIviLxiSyncEvents */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED534E-A398-11D4-BA58-000064657374")
    IIviLxiSyncEvents : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DisableAll( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR EventName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR EventName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveAllCustomEvents( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncEvent **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WiredOrBiasMode( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WiredOrBiasMode( 
            /* [in] */ long val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncEventsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncEvents * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncEvents * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, DisableAll)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableAll )( 
            IIviLxiSyncEvents * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, Add)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IIviLxiSyncEvents * This,
            /* [in] */ BSTR EventName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, Remove)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IIviLxiSyncEvents * This,
            /* [in] */ BSTR EventName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, RemoveAllCustomEvents)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllCustomEvents )( 
            IIviLxiSyncEvents * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, get_Count)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IIviLxiSyncEvents * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, get_Item)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IIviLxiSyncEvents * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncEvent **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, get_Name)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IIviLxiSyncEvents * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, get_WiredOrBiasMode)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_WiredOrBiasMode )( 
            IIviLxiSyncEvents * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncEvents, put_WiredOrBiasMode)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_WiredOrBiasMode )( 
            IIviLxiSyncEvents * This,
            /* [in] */ long val);
        
        END_INTERFACE
    } IIviLxiSyncEventsVtbl;

    interface IIviLxiSyncEvents
    {
        CONST_VTBL struct IIviLxiSyncEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncEvents_DisableAll(This)	\
    ( (This)->lpVtbl -> DisableAll(This) ) 

#define IIviLxiSyncEvents_Add(This,EventName)	\
    ( (This)->lpVtbl -> Add(This,EventName) ) 

#define IIviLxiSyncEvents_Remove(This,EventName)	\
    ( (This)->lpVtbl -> Remove(This,EventName) ) 

#define IIviLxiSyncEvents_RemoveAllCustomEvents(This)	\
    ( (This)->lpVtbl -> RemoveAllCustomEvents(This) ) 

#define IIviLxiSyncEvents_get_Count(This,val)	\
    ( (This)->lpVtbl -> get_Count(This,val) ) 

#define IIviLxiSyncEvents_get_Item(This,Name,val)	\
    ( (This)->lpVtbl -> get_Item(This,Name,val) ) 

#define IIviLxiSyncEvents_get_Name(This,Index,val)	\
    ( (This)->lpVtbl -> get_Name(This,Index,val) ) 

#define IIviLxiSyncEvents_get_WiredOrBiasMode(This,val)	\
    ( (This)->lpVtbl -> get_WiredOrBiasMode(This,val) ) 

#define IIviLxiSyncEvents_put_WiredOrBiasMode(This,val)	\
    ( (This)->lpVtbl -> put_WiredOrBiasMode(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncEvents_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncTime_INTERFACE_DEFINED__
#define __IIviLxiSyncTime_INTERFACE_DEFINED__

/* interface IIviLxiSyncTime */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncTime;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED534F-A398-11D4-BA58-000064657374")
    IIviLxiSyncTime : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE GetSystemTime( 
            /* [out][in] */ double *TimeSeconds,
            /* [out][in] */ double *TimeFractional) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsMaster( 
            /* [retval][out] */ VARIANT_BOOL *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsSynchronized( 
            /* [retval][out] */ VARIANT_BOOL *val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncTimeVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncTime * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncTime * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncTime * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTime, GetSystemTime)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSystemTime )( 
            IIviLxiSyncTime * This,
            /* [out][in] */ double *TimeSeconds,
            /* [out][in] */ double *TimeFractional);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTime, get_IsMaster)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsMaster )( 
            IIviLxiSyncTime * This,
            /* [retval][out] */ VARIANT_BOOL *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTime, get_IsSynchronized)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsSynchronized )( 
            IIviLxiSyncTime * This,
            /* [retval][out] */ VARIANT_BOOL *val);
        
        END_INTERFACE
    } IIviLxiSyncTimeVtbl;

    interface IIviLxiSyncTime
    {
        CONST_VTBL struct IIviLxiSyncTimeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncTime_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncTime_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncTime_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncTime_GetSystemTime(This,TimeSeconds,TimeFractional)	\
    ( (This)->lpVtbl -> GetSystemTime(This,TimeSeconds,TimeFractional) ) 

#define IIviLxiSyncTime_get_IsMaster(This,val)	\
    ( (This)->lpVtbl -> get_IsMaster(This,val) ) 

#define IIviLxiSyncTime_get_IsSynchronized(This,val)	\
    ( (This)->lpVtbl -> get_IsSynchronized(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncTime_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncTrigger_INTERFACE_DEFINED__
#define __IIviLxiSyncTrigger_INTERFACE_DEFINED__

/* interface IIviLxiSyncTrigger */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncTrigger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5350-A398-11D4-BA58-000064657374")
    IIviLxiSyncTrigger : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Sources( 
            /* [retval][out] */ IIviLxiSyncTriggerSources **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TriggerCount( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TriggerCount( 
            /* [in] */ long val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Alarms( 
            /* [retval][out] */ IIviLxiSyncTriggerAlarms **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TriggerSource( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TriggerSource( 
            /* [in] */ BSTR val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncTriggerVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncTrigger * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncTrigger * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncTrigger * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTrigger, get_Sources)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Sources )( 
            IIviLxiSyncTrigger * This,
            /* [retval][out] */ IIviLxiSyncTriggerSources **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTrigger, get_TriggerCount)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TriggerCount )( 
            IIviLxiSyncTrigger * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTrigger, put_TriggerCount)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TriggerCount )( 
            IIviLxiSyncTrigger * This,
            /* [in] */ long val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTrigger, get_Alarms)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Alarms )( 
            IIviLxiSyncTrigger * This,
            /* [retval][out] */ IIviLxiSyncTriggerAlarms **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTrigger, get_TriggerSource)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TriggerSource )( 
            IIviLxiSyncTrigger * This,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTrigger, put_TriggerSource)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TriggerSource )( 
            IIviLxiSyncTrigger * This,
            /* [in] */ BSTR val);
        
        END_INTERFACE
    } IIviLxiSyncTriggerVtbl;

    interface IIviLxiSyncTrigger
    {
        CONST_VTBL struct IIviLxiSyncTriggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncTrigger_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncTrigger_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncTrigger_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncTrigger_get_Sources(This,val)	\
    ( (This)->lpVtbl -> get_Sources(This,val) ) 

#define IIviLxiSyncTrigger_get_TriggerCount(This,val)	\
    ( (This)->lpVtbl -> get_TriggerCount(This,val) ) 

#define IIviLxiSyncTrigger_put_TriggerCount(This,val)	\
    ( (This)->lpVtbl -> put_TriggerCount(This,val) ) 

#define IIviLxiSyncTrigger_get_Alarms(This,val)	\
    ( (This)->lpVtbl -> get_Alarms(This,val) ) 

#define IIviLxiSyncTrigger_get_TriggerSource(This,val)	\
    ( (This)->lpVtbl -> get_TriggerSource(This,val) ) 

#define IIviLxiSyncTrigger_put_TriggerSource(This,val)	\
    ( (This)->lpVtbl -> put_TriggerSource(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncTrigger_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncTriggerAlarm_INTERFACE_DEFINED__
#define __IIviLxiSyncTriggerAlarm_INTERFACE_DEFINED__

/* interface IIviLxiSyncTriggerAlarm */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncTriggerAlarm;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5351-A398-11D4-BA58-000064657374")
    IIviLxiSyncTriggerAlarm : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Configure( 
            /* [in] */ double TimeSeconds,
            /* [in] */ double TimeFraction,
            /* [in] */ double Period,
            /* [in] */ long RepeatCount) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Period( 
            /* [retval][out] */ double *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Period( 
            /* [in] */ double val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_RepeatCount( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_RepeatCount( 
            /* [in] */ long val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TimeFraction( 
            /* [retval][out] */ double *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TimeFraction( 
            /* [in] */ double val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_TimeSeconds( 
            /* [retval][out] */ double *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_TimeSeconds( 
            /* [in] */ double val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncTriggerAlarmVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncTriggerAlarm * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncTriggerAlarm * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, Configure)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Configure )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [in] */ double TimeSeconds,
            /* [in] */ double TimeFraction,
            /* [in] */ double Period,
            /* [in] */ long RepeatCount);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, get_Period)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Period )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [retval][out] */ double *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, put_Period)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Period )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [in] */ double val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, get_RepeatCount)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RepeatCount )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, put_RepeatCount)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RepeatCount )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [in] */ long val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, get_TimeFraction)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeFraction )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [retval][out] */ double *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, put_TimeFraction)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimeFraction )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [in] */ double val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, get_TimeSeconds)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimeSeconds )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [retval][out] */ double *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, put_TimeSeconds)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimeSeconds )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [in] */ double val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, get_Enabled)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Enabled )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [retval][out] */ VARIANT_BOOL *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarm, put_Enabled)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Enabled )( 
            IIviLxiSyncTriggerAlarm * This,
            /* [in] */ VARIANT_BOOL val);
        
        END_INTERFACE
    } IIviLxiSyncTriggerAlarmVtbl;

    interface IIviLxiSyncTriggerAlarm
    {
        CONST_VTBL struct IIviLxiSyncTriggerAlarmVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncTriggerAlarm_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncTriggerAlarm_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncTriggerAlarm_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncTriggerAlarm_Configure(This,TimeSeconds,TimeFraction,Period,RepeatCount)	\
    ( (This)->lpVtbl -> Configure(This,TimeSeconds,TimeFraction,Period,RepeatCount) ) 

#define IIviLxiSyncTriggerAlarm_get_Period(This,val)	\
    ( (This)->lpVtbl -> get_Period(This,val) ) 

#define IIviLxiSyncTriggerAlarm_put_Period(This,val)	\
    ( (This)->lpVtbl -> put_Period(This,val) ) 

#define IIviLxiSyncTriggerAlarm_get_RepeatCount(This,val)	\
    ( (This)->lpVtbl -> get_RepeatCount(This,val) ) 

#define IIviLxiSyncTriggerAlarm_put_RepeatCount(This,val)	\
    ( (This)->lpVtbl -> put_RepeatCount(This,val) ) 

#define IIviLxiSyncTriggerAlarm_get_TimeFraction(This,val)	\
    ( (This)->lpVtbl -> get_TimeFraction(This,val) ) 

#define IIviLxiSyncTriggerAlarm_put_TimeFraction(This,val)	\
    ( (This)->lpVtbl -> put_TimeFraction(This,val) ) 

#define IIviLxiSyncTriggerAlarm_get_TimeSeconds(This,val)	\
    ( (This)->lpVtbl -> get_TimeSeconds(This,val) ) 

#define IIviLxiSyncTriggerAlarm_put_TimeSeconds(This,val)	\
    ( (This)->lpVtbl -> put_TimeSeconds(This,val) ) 

#define IIviLxiSyncTriggerAlarm_get_Enabled(This,val)	\
    ( (This)->lpVtbl -> get_Enabled(This,val) ) 

#define IIviLxiSyncTriggerAlarm_put_Enabled(This,val)	\
    ( (This)->lpVtbl -> put_Enabled(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncTriggerAlarm_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncTriggerAlarms_INTERFACE_DEFINED__
#define __IIviLxiSyncTriggerAlarms_INTERFACE_DEFINED__

/* interface IIviLxiSyncTriggerAlarms */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncTriggerAlarms;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5352-A398-11D4-BA58-000064657374")
    IIviLxiSyncTriggerAlarms : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR AlarmName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE DisableAll( void) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR AlarmName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveAllTriggerAlarms( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncTriggerAlarm **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncTriggerAlarmsVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncTriggerAlarms * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncTriggerAlarms * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncTriggerAlarms * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarms, Add)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IIviLxiSyncTriggerAlarms * This,
            /* [in] */ BSTR AlarmName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarms, DisableAll)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *DisableAll )( 
            IIviLxiSyncTriggerAlarms * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarms, Remove)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IIviLxiSyncTriggerAlarms * This,
            /* [in] */ BSTR AlarmName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarms, RemoveAllTriggerAlarms)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllTriggerAlarms )( 
            IIviLxiSyncTriggerAlarms * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarms, get_Count)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IIviLxiSyncTriggerAlarms * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarms, get_Item)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IIviLxiSyncTriggerAlarms * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncTriggerAlarm **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerAlarms, get_Name)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IIviLxiSyncTriggerAlarms * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val);
        
        END_INTERFACE
    } IIviLxiSyncTriggerAlarmsVtbl;

    interface IIviLxiSyncTriggerAlarms
    {
        CONST_VTBL struct IIviLxiSyncTriggerAlarmsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncTriggerAlarms_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncTriggerAlarms_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncTriggerAlarms_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncTriggerAlarms_Add(This,AlarmName)	\
    ( (This)->lpVtbl -> Add(This,AlarmName) ) 

#define IIviLxiSyncTriggerAlarms_DisableAll(This)	\
    ( (This)->lpVtbl -> DisableAll(This) ) 

#define IIviLxiSyncTriggerAlarms_Remove(This,AlarmName)	\
    ( (This)->lpVtbl -> Remove(This,AlarmName) ) 

#define IIviLxiSyncTriggerAlarms_RemoveAllTriggerAlarms(This)	\
    ( (This)->lpVtbl -> RemoveAllTriggerAlarms(This) ) 

#define IIviLxiSyncTriggerAlarms_get_Count(This,val)	\
    ( (This)->lpVtbl -> get_Count(This,val) ) 

#define IIviLxiSyncTriggerAlarms_get_Item(This,Name,val)	\
    ( (This)->lpVtbl -> get_Item(This,Name,val) ) 

#define IIviLxiSyncTriggerAlarms_get_Name(This,Index,val)	\
    ( (This)->lpVtbl -> get_Name(This,Index,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncTriggerAlarms_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncTriggerSource_INTERFACE_DEFINED__
#define __IIviLxiSyncTriggerSource_INTERFACE_DEFINED__

/* interface IIviLxiSyncTriggerSource */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncTriggerSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5353-A398-11D4-BA58-000064657374")
    IIviLxiSyncTriggerSource : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Configure( 
            /* [in] */ double Delay,
            /* [in] */ IviLxiSyncTriggerSourceDetectionEnum Detection) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Delay( 
            /* [retval][out] */ double *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Delay( 
            /* [in] */ double val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Detection( 
            /* [retval][out] */ IviLxiSyncTriggerSourceDetectionEnum *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Detection( 
            /* [in] */ IviLxiSyncTriggerSourceDetectionEnum val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EventId( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EventId( 
            /* [in] */ BSTR val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Filter( 
            /* [retval][out] */ BSTR *val) = 0;
        
        virtual /* [helpcontext][helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Filter( 
            /* [in] */ BSTR val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncTriggerSourceVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncTriggerSource * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncTriggerSource * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncTriggerSource * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, Configure)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Configure )( 
            IIviLxiSyncTriggerSource * This,
            /* [in] */ double Delay,
            /* [in] */ IviLxiSyncTriggerSourceDetectionEnum Detection);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, get_Delay)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Delay )( 
            IIviLxiSyncTriggerSource * This,
            /* [retval][out] */ double *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, put_Delay)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Delay )( 
            IIviLxiSyncTriggerSource * This,
            /* [in] */ double val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, get_Detection)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Detection )( 
            IIviLxiSyncTriggerSource * This,
            /* [retval][out] */ IviLxiSyncTriggerSourceDetectionEnum *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, put_Detection)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Detection )( 
            IIviLxiSyncTriggerSource * This,
            /* [in] */ IviLxiSyncTriggerSourceDetectionEnum val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, get_EventId)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EventId )( 
            IIviLxiSyncTriggerSource * This,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, put_EventId)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_EventId )( 
            IIviLxiSyncTriggerSource * This,
            /* [in] */ BSTR val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, get_Filter)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Filter )( 
            IIviLxiSyncTriggerSource * This,
            /* [retval][out] */ BSTR *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSource, put_Filter)
        /* [helpcontext][helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Filter )( 
            IIviLxiSyncTriggerSource * This,
            /* [in] */ BSTR val);
        
        END_INTERFACE
    } IIviLxiSyncTriggerSourceVtbl;

    interface IIviLxiSyncTriggerSource
    {
        CONST_VTBL struct IIviLxiSyncTriggerSourceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncTriggerSource_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncTriggerSource_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncTriggerSource_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncTriggerSource_Configure(This,Delay,Detection)	\
    ( (This)->lpVtbl -> Configure(This,Delay,Detection) ) 

#define IIviLxiSyncTriggerSource_get_Delay(This,val)	\
    ( (This)->lpVtbl -> get_Delay(This,val) ) 

#define IIviLxiSyncTriggerSource_put_Delay(This,val)	\
    ( (This)->lpVtbl -> put_Delay(This,val) ) 

#define IIviLxiSyncTriggerSource_get_Detection(This,val)	\
    ( (This)->lpVtbl -> get_Detection(This,val) ) 

#define IIviLxiSyncTriggerSource_put_Detection(This,val)	\
    ( (This)->lpVtbl -> put_Detection(This,val) ) 

#define IIviLxiSyncTriggerSource_get_EventId(This,val)	\
    ( (This)->lpVtbl -> get_EventId(This,val) ) 

#define IIviLxiSyncTriggerSource_put_EventId(This,val)	\
    ( (This)->lpVtbl -> put_EventId(This,val) ) 

#define IIviLxiSyncTriggerSource_get_Filter(This,val)	\
    ( (This)->lpVtbl -> get_Filter(This,val) ) 

#define IIviLxiSyncTriggerSource_put_Filter(This,val)	\
    ( (This)->lpVtbl -> put_Filter(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncTriggerSource_INTERFACE_DEFINED__ */


#ifndef __IIviLxiSyncTriggerSources_INTERFACE_DEFINED__
#define __IIviLxiSyncTriggerSources_INTERFACE_DEFINED__

/* interface IIviLxiSyncTriggerSources */
/* [unique][oleautomation][helpcontext][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IIviLxiSyncTriggerSources;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47ED5354-A398-11D4-BA58-000064657374")
    IIviLxiSyncTriggerSources : public IUnknown
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR SourceName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR SourceName) = 0;
        
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE RemoveAllCustomTriggerSources( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncTriggerSource **val) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IIviLxiSyncTriggerSourcesVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IIviLxiSyncTriggerSources * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IIviLxiSyncTriggerSources * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IIviLxiSyncTriggerSources * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSources, Add)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IIviLxiSyncTriggerSources * This,
            /* [in] */ BSTR SourceName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSources, Remove)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IIviLxiSyncTriggerSources * This,
            /* [in] */ BSTR SourceName);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSources, RemoveAllCustomTriggerSources)
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveAllCustomTriggerSources )( 
            IIviLxiSyncTriggerSources * This);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSources, get_Count)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IIviLxiSyncTriggerSources * This,
            /* [retval][out] */ long *val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSources, get_Item)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IIviLxiSyncTriggerSources * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ IIviLxiSyncTriggerSource **val);
        
        DECLSPEC_XFGVIRT(IIviLxiSyncTriggerSources, get_Name)
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Name )( 
            IIviLxiSyncTriggerSources * This,
            /* [in] */ long Index,
            /* [retval][out] */ BSTR *val);
        
        END_INTERFACE
    } IIviLxiSyncTriggerSourcesVtbl;

    interface IIviLxiSyncTriggerSources
    {
        CONST_VTBL struct IIviLxiSyncTriggerSourcesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIviLxiSyncTriggerSources_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IIviLxiSyncTriggerSources_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IIviLxiSyncTriggerSources_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IIviLxiSyncTriggerSources_Add(This,SourceName)	\
    ( (This)->lpVtbl -> Add(This,SourceName) ) 

#define IIviLxiSyncTriggerSources_Remove(This,SourceName)	\
    ( (This)->lpVtbl -> Remove(This,SourceName) ) 

#define IIviLxiSyncTriggerSources_RemoveAllCustomTriggerSources(This)	\
    ( (This)->lpVtbl -> RemoveAllCustomTriggerSources(This) ) 

#define IIviLxiSyncTriggerSources_get_Count(This,val)	\
    ( (This)->lpVtbl -> get_Count(This,val) ) 

#define IIviLxiSyncTriggerSources_get_Item(This,Name,val)	\
    ( (This)->lpVtbl -> get_Item(This,Name,val) ) 

#define IIviLxiSyncTriggerSources_get_Name(This,Index,val)	\
    ( (This)->lpVtbl -> get_Name(This,Index,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIviLxiSyncTriggerSources_INTERFACE_DEFINED__ */

#endif /* __IviLxiSyncLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


