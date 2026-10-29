//
// Created by ikasa on 2026/10/28.
//

#pragma once
#include "Address.h"
#include <string_view>
#include <functional>
#include "SigScanner.h"

namespace Signs
{
    namespace bgfx
    {
        static inline Address renderContext_d3d12_submit;
        static inline Address renderContext_d3d12_updateResolution;
    }
}

class Signatures
{
public:
    static void add(const std::string_view _sig, Address& _dest, const SigScanner::callback_t& _callback = std::nullopt)
    {
        SigScanner::push(_dest, _sig, _callback);
    };
    static void execute()
    {
        SigScanner::execute();
    };
    static void initialize();
};