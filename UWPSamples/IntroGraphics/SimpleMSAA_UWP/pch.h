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

#pragma warning(push)
#pragma warning(disable : 4467)
#include <wrl.h>
#pragma warning(pop)

#include <d3d11_3.h>
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <algorithm>
#include <exception>
#include <memory>
#include <stdexcept>

#include <stdio.h>
#include <pix.h>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include "CommonStates.h"
#include "Effects.h"
#include "GamePad.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "SpriteBatch.h"
#include "SimpleMath.h"
#include "SpriteFont.h"

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