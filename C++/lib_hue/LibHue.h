#pragma once

#include <functional>

namespace LibHue
{
    bool IsInitialized();
    bool Initialize(std::function<void(int)> registrationError);
    void RegistationError(int in_uErrorCode);
};