//
// Created by ikasa on 2026/10/28.
//

#pragma once
#include <algorithm>
#include <execution>
#include <functional>
#include <string>

#include "Address.h"

class SigScanner
{
    struct ScanTask
    {
        Address& mDest;
        std::string_view mSignature;
        std::function<Address(Address)> mCallback;
    };
    std::vector<ScanTask> mTasks;

    static SigScanner* getInstance()
    {
        static SigScanner inst;
        return &inst;
    };
    static void push()
    {

    }

    static void execute()
    {
        const auto instance = getInstance();
        std::for_each(std::execution::par, instance->mTasks.begin(), instance->mTasks.end(), [](const ScanTask& task)
        {
            const std::string_view signature = task.mSignature;
            Address& dest = task.mDest;
            dest =
            const auto callback = task.mCallback;
            dest = callback(dest);
            //do something
        });
    }
};
