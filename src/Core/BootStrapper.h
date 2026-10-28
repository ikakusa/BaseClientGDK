//
// Created by ikasa on 2026/10/28.
//

#pragma once
#include <Windows.h>

class BootStrapper {
public:
    HMODULE mModule;
    static BootStrapper* getInstance()
    {
        static BootStrapper theInstance;
        return &theInstance;
    }
};