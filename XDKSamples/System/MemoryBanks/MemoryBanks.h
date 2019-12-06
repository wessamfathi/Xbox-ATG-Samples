//--------------------------------------------------------------------------------------
// MemoryBanks.h
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include "MemoryDemo.h"

// A basic sample implementation that creates a D3D11 device with a render loop.
// The sample can run five different tests of the memory bank code showing various ways to create and interact with memory
class Sample
{
public:

    Sample();

    // Initialization and management
    void Initialize(IUnknown* window);

    // Basic game loop
    void Tick();

    // Messages
    void OnSuspending();
    void OnResuming();

private:

    void Update(DX::StepTimer const& timer);
    void Render();
    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Main class driving the demo code
    ATG::MemoryDemo m_memoryBankDemo;
    enum class TestStatus
    {
        TEST_NOT_RUN,
        TEST_SUCCESS,
        TEST_FAILURE,
    };
    TestStatus m_randomBankStatus;
    TestStatus m_fixedBankStatus;
    TestStatus m_readOnlyBankStatus;
    TestStatus m_bankSwitchingStatus;
    TestStatus m_sharedAddressStatus;

    void DrawStatusString(const std::wstring& button, const std::wstring& testName, TestStatus status, DirectX::XMFLOAT2& pos);
    void DrawHelpText(DirectX::XMFLOAT2& pos, ATG::MemoryBankDemoTests);

    // Device resources.
    std::unique_ptr<DX::DeviceResources>        m_deviceResources;

    // Rendering loop timer.
    uint64_t                                    m_frame;
    DX::StepTimer                               m_timer;

    // Input devices.
    std::unique_ptr<DirectX::GamePad>           m_gamePad;

    DirectX::GamePad::ButtonStateTracker        m_gamePadButtons;

    // DirectXTK objects.
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;
    std::unique_ptr<DirectX::GraphicsMemory>    m_graphicsMemory;
    std::unique_ptr<DirectX::SpriteBatch>       m_spriteBatch;
    std::unique_ptr<DirectX::SpriteFont>        m_font;
    std::unique_ptr<DirectX::SpriteFont>        m_ctrlFont;
};
