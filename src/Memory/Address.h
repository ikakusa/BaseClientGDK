//
// Created by ikasa on 2026/10/28.
//

#pragma once
#include <assert.h>
#include <cstdint>

struct Address
{
private:
    using RawType = uintptr_t;
    RawType mRaw = 0;
public:
    RawType raw()
    {
        assert(mRaw > 0 && "Address is zero");
        return mRaw;
    };
    template <typename T>
    T as()
    {
        assert(mRaw > 0 && "Address is zero");
        return *reinterpret_cast<T*>(this);
    }

    Address() = default;
    Address(const RawType raw)
    {
        mRaw = raw;
    }
};
