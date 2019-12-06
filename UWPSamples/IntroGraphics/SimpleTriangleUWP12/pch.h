﻿//--------------------------------------------------------------------------------------
// pch.h
//
// Header for standard system include files.
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

// Use the C++ standard templated min/max
#define NOMINMAX

#include <wrl.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include "d3dx12.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>

#include <stdio.h>

// To use graphics and CPU markup events with the latest version of PIX, change this to include <pix3.h> 
// then add the NuGet package WinPixEventRuntime to the project. 
#include <pix.h>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include "GamePad.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"

namespace DX
{
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) : result(hr) {}

        virtual const char* what() const override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", result);
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr)
    {
        if (FAILED(hr))
        {
            throw com_exception(hr);
        }
    }
}