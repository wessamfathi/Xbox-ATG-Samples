//--------------------------------------------------------------------------------------
// ISACRenderer.h
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include <Windows.h>
#include "SpatialAudioClient.h"
#include "mmdeviceapi.h"

#pragma once
	// Primary ISAC Renderering Class
	class ISACRenderer :
		public Microsoft::WRL::RuntimeClass< Microsoft::WRL::RuntimeClassFlags< Microsoft::WRL::ClassicCom >, Microsoft::WRL::FtmBase, IActivateAudioInterfaceCompletionHandler >
	{
	public:
		ISACRenderer();

		HRESULT InitializeAudioDeviceAsync();
		bool	IsActive() { return m_ISACDeviceActive; };
		STDMETHOD(ActivateCompleted)( IActivateAudioInterfaceAsyncOperation *operation );

		Microsoft::WRL::ComPtr<ISpatialAudioObjectRenderStream>		m_SpatialAudioStream;
		HANDLE														m_bufferCompletionEvent;

	private:
		~ISACRenderer();

		Platform::String^		m_DeviceIdString;
		bool					m_ISACDeviceActive;
		
		Microsoft::WRL::ComPtr<ISpatialAudioClient>					m_AudioClient;
	};



