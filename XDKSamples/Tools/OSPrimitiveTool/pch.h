//--------------------------------------------------------------------------------------
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

#include <xdk.h>
#if _XDK_VER < 0x295A0401 /* XDK Edition 151100 */
#error This sample requires the November 2015 XDK or later
#endif
#include <wrl.h>
#include <d3d11_x.h>
#include <pix.h>

#ifndef _CONSOLE
#include <DirectXMath.h>
#include <DirectXColors.h>
#endif

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>
#include <string>

#include <stdio.h>

#ifndef _CONSOLE
#include "GamePad.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "DDSTextureLoader.h"
#include "GraphicsMemory.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "SimpleMath.h"
#endif

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
