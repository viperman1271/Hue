#include "LibHue.h"

#include <algorithm>
#include <cassert>

namespace LibHue
{
    bool g_bIsInitialized;
    std::function<void(int)> g_fRegistrationError;

    bool IsInitialized()
    {
        return g_bIsInitialized;
    }

    bool Initialize(std::function<void(int)> registrationError)
    {
        if (g_bIsInitialized)
            return false;

        g_fRegistrationError = registrationError;
        g_bIsInitialized = true;

        return true;
    }

    void RegistationError(int in_uErrorCode)
    {
        assert(IsInitialized());
        g_fRegistrationError(in_uErrorCode);
    }
}