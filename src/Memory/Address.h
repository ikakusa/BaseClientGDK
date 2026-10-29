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
    [[nodiscard]] RawType raw() const noexcept
    {
        assert(mRaw > 0 && "Address is zero");
        return mRaw;
    };

    //アドレスを先頭にオブジェクトがある場合に使います
    //関数ポインターを扱うときに使います
    template <typename T>
    [[nodiscard]] T* as() const noexcept
    {
        assert(mRaw > 0 && "Address is zero");
        return reinterpret_cast<T*>(mRaw);
    }

    //ポインターがそのアドレスに格納されている場合に使います
    //対応するアドレスにあるメモリを読みます
    template <typename T>
    [[nodiscard]] T read() const noexcept
    {
        assert(mRaw > 0 && "Address is zero");
        return *reinterpret_cast<T*>(mRaw);
    }

    //lea命令を例にすると
    //48 8d 05 ? ? ? ?, lea rax, [bin.exe+0xXXXXX]
    //offsetは3なので
    //48を先頭に3足して????の部分を取る
    //int32_t*でキャストしてでリファレンスすることで+0xXXXXX(displacementと呼ばれる)を取ることができる
    //lea命令のアドレス+instruction_lengthで次の命令のアドレスを取得する
    //この取得した次の命令のアドレス+displacementで対応するポインターのアドレスが取得できる
    //(rip相対アドレスは次の命令のアドレスを先頭とするオフセットになるため)
    [[nodiscard]] Address rip(const int instruction_length = 7, const int offset = 3) const noexcept
    {
        const std::int32_t disp = *reinterpret_cast<std::int32_t*>(mRaw + offset);
        return Address(static_cast<uintptr_t>(disp + instruction_length + disp));
    }

    //vTableのポインターの中身のアドレスを整数として計算してインデックスに対応したアドレスを返します
    //関数は通常ポインターのサイズ(8バイト)刻みで配置されます
    //今回はvtableの中身のアドレスを扱っているのでvtableの中身のアドレスはuintptr_tとなります
    //アドレス+(8*index)で取得した関数ポインターをデリファレンスして関数ポインターの中身の先頭アドレスを返しています。
    [[nodiscard]] Address operator[](const int index) const noexcept
    {
        const uintptr_t calcIndex = static_cast<uintptr_t>(index) * sizeof(uintptr_t);
        return Address(*reinterpret_cast<uintptr_t*>(mRaw + calcIndex));
    }

    Address() noexcept = default;
    Address(const RawType raw) noexcept
    {
        mRaw = raw;
    }

    [[nodiscard]]
    explicit constexpr operator bool() const noexcept
    {
        return mRaw != 0;
    }
};
