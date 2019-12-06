//--------------------------------------------------------------------------------------
// GamepadCppWinRT_UWP.h
//
// Advanced Technology Group (ATG)
// Copyright (C) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"


// A basic sample implementation that creates a D3D11 device and
// provides a render loop.
class Sample final : public DX::IDeviceNotify
{
public:

    Sample() noexcept(false);

    // Initialization and management
    void Initialize(::IUnknown* window, int width, int height, DXGI_MODE_ROTATION rotation);

    // Basic render loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height, DXGI_MODE_ROTATION rotation);
    void ValidateDevice();

    // Properties
    void GetDefaultSize(int& width, int& height) const;

private:

    void Update(DX::StepTimer const& timer);
    void Render();
    const winrt::Windows::Gaming::Input::Gamepad* GetLastGamepad();

    void OnGamepadAdded(winrt::Windows::Foundation::IInspectable const & sender, winrt::Windows::Gaming::Input::Gamepad const & args);
    void OnGamepadRemoved(winrt::Windows::Foundation::IInspectable const & sender, winrt::Windows::Gaming::Input::Gamepad const & args);
    void RefreshCachedGamepads();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

    // Render objects.
    std::unique_ptr<DirectX::SpriteBatch>   m_spriteBatch;
    std::unique_ptr<DirectX::SpriteFont>    m_font;
    std::unique_ptr<DirectX::SpriteFont>    m_ctrlFont;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_background;

    //Gamepad states
    std::vector<winrt::Windows::Gaming::Input::Gamepad> m_localCollection;
    winrt::Windows::Gaming::Input::GamepadReading       m_reading;
    const winrt::Windows::Gaming::Input::Gamepad*       m_currentGamepad;

    bool                    m_currentGamepadNeedsRefresh;
    std::wstring            m_buttonString;
    double                  m_leftTrigger;
    double                  m_rightTrigger;
    double                  m_leftStickX;
    double                  m_leftStickY;
    double                  m_rightStickX;
    double                  m_rightStickY;

    // Device resources.
    std::unique_ptr<DX::DeviceResources>    m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                           m_timer;
};