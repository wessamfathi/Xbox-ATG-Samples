//--------------------------------------------------------------------------------------
// Common.h
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once
#include <Windows.h>
#include <wrl\implements.h>
#include <mmreg.h>
#include <mfapi.h>

//using namespace Microsoft::WRL;

// GUID to ensure both WASAPI clients share a session
static const GUID AUDIOSESSIONGUID =
{ 0xb3954ae8, 0xc3c3, 0x4094,{ 0x82, 0x1c, 0xc7, 0xbd, 0xf4, 0xab, 0x15, 0x8a } };

// release and zero out a possible nullptr pointer. note this will
// do the release on a temp copy to avoid reentrancy issues that can result from
// callbacks durring the release
template <class T> void SafeRelease( __deref_inout_opt T **ppT )
{
    T *pTTemp = *ppT;    // temp copy
    *ppT = nullptr;      // zero the input
    if (pTTemp)
    {
        pTTemp->Release();
    }
}

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { SafeRelease(&x); }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { delete x; x = nullptr; }
#endif

#ifndef SAFE_ARRAYDELETE
#define SAFE_ARRAYDELETE(x) { delete[] x; x = nullptr; }
#endif

#ifndef METHODASYNCCALLBACK
#define METHODASYNCCALLBACK(Parent, AsyncCallback, pfnCallback) \
class Callback##AsyncCallback :\
    public IMFAsyncCallback \
{ \
public: \
    Callback##AsyncCallback() : \
        _parent(((Parent*)((BYTE*)this - offsetof(Parent, m_x##AsyncCallback)))), \
        _dwQueueID( MFASYNC_CALLBACK_QUEUE_MULTITHREADED ) \
    { \
    } \
\
    STDMETHOD_( ULONG, AddRef )() \
    { \
        return _parent->AddRef(); \
    } \
    STDMETHOD_( ULONG, Release )() \
    { \
        return _parent->Release(); \
    } \
    STDMETHOD( QueryInterface )( REFIID riid, void **ppvObject ) \
    { \
        if (riid == IID_IMFAsyncCallback || riid == IID_IUnknown) \
        { \
            (*ppvObject) = this; \
            AddRef(); \
            return S_OK; \
        } \
        *ppvObject = nullptr; \
        return E_NOINTERFACE; \
    } \
    STDMETHOD( GetParameters )( \
        /* [out] */ __RPC__out DWORD *pdwFlags, \
        /* [out] */ __RPC__out DWORD *pdwQueue) \
    { \
        *pdwFlags = 0; \
        *pdwQueue = _dwQueueID; \
        return S_OK; \
    } \
    STDMETHOD( Invoke )( /* [out] */ __RPC__out IMFAsyncResult * pResult ) \
    { \
        _parent->pfnCallback( pResult ); \
        return S_OK; \
    } \
    void SetQueueID( DWORD dwQueueID ) { _dwQueueID = dwQueueID; } \
\
protected: \
    Parent* _parent; \
    DWORD   _dwQueueID; \
           \
} m_x##AsyncCallback;
#endif

//
// CAsyncState
//
// Used to maintain state during MF Work Item callbacks
class CAsyncState : 
    public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>, IUnknown>
{  
public:  
    CAsyncState( Platform::Array<int,1>^ data, uint32_t size ) :
        m_Data(data), 
        m_Size(size)
    {  
    };  

public:
    Platform::Array<int,1>^  m_Data;
    uint32_t                   m_Size;

private:
    virtual ~CAsyncState() {};
}; 

struct RenderBuffer
{
    uint32_t          BufferSize;
    uint32_t          BytesFilled;
    BYTE           *Buffer;
    RenderBuffer   *Next;

    RenderBuffer() :
        BufferSize(0),
        BytesFilled(0),
        Buffer( nullptr ),
        Next( nullptr )
    {
    }

    ~RenderBuffer()
    {
        SAFE_ARRAYDELETE( Buffer );
    }
};

enum RenderSampleType
{
    SampleTypeUnknown,
    SampleTypeFloat,
    SampleType16BitPCM,
};

//
//  CalculateMixFormatType()
//
//  Determine IEEE Float or PCM samples based on media type
//
inline RenderSampleType CalculateMixFormatType( WAVEFORMATEX *wfx )
{
    if ( (wfx->wFormatTag == WAVE_FORMAT_PCM) ||
         (  (wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) &&
            (reinterpret_cast<WAVEFORMATEXTENSIBLE *>(wfx)->SubFormat == KSDATAFORMAT_SUBTYPE_PCM) ) )
    {
        if (wfx->wBitsPerSample == 16)
        {
            return RenderSampleType::SampleType16BitPCM;
        }
    }
    else if ( (wfx->wFormatTag == WAVE_FORMAT_IEEE_FLOAT) ||
              ( (wfx->wFormatTag == WAVE_FORMAT_EXTENSIBLE) &&
                (reinterpret_cast<WAVEFORMATEXTENSIBLE *>(wfx)->SubFormat == KSDATAFORMAT_SUBTYPE_IEEE_FLOAT) ) )
    {
        return RenderSampleType::SampleTypeFloat;
    }

    return RenderSampleType::SampleTypeUnknown;
}
