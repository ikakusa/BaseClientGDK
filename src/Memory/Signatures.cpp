//
// Created by ikasa on 2026/10/28.
//

#include "Signatures.h"
#include "SigScanner.h"
#include "../Utility/cryptStr.h"

void Signatures::initialize()
{
    //bgfxのフックからID3D12Device*などを取得してhookします
    //1.26.44
    //bgfx
    {
        const auto vtable_pattern = protect("48 8D 05 ?? ?? ?? ?? 48 89 01 0F 57 F6 0F 11 71 08 0F 11 71 18 0F 11 71 28");
        add(vtable_pattern, Signs::bgfx::renderContext_d3d12_submit, [](const Address addr) { return addr.rip()[50]; });
        add(vtable_pattern, Signs::bgfx::renderContext_d3d12_updateResolution, [](const Address addr) { return addr.rip()[60]; });
    }

    //
    execute();//スキャンします
}
