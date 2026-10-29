//
// Created by ikasa on 2026/10/28.
//

#pragma once
#include <algorithm>
#include <execution>
#include <functional>
#include <map>

#include "Address.h"
#include <libhat/process.hpp>
#include <libhat/scanner.hpp>
#include <libhat/signature.hpp>
#include <utility>

class SigScanner
{
public:
    using callback_t = std::optional<std::function<Address(const Address)>>;
private:
    using parsed_t = hat::result<hat::signature, hat::signature_error>;
    struct ScanTask
    {
        Address& mDest;
        parsed_t mSignature;
        std::string_view mSignatureView;
        callback_t mCallback;
        ScanTask(Address& _dest, parsed_t _signature, const std::string_view _signatureView, const callback_t& _callback) : mDest(_dest), mSignature(std::move(_signature)), mSignatureView(_signatureView), mCallback(_callback) {};
    };
    std::vector<ScanTask> mTasks;
    uintptr_t mBase;
    std::map<std::string_view, Address> mCached{};
public:
    SigScanner()
    {
        mBase = hat::process::get_process_module().address();
    };
    SigScanner(const SigScanner&) = delete;
    ~SigScanner() = default;
    SigScanner& operator=(const SigScanner&) = delete;

    static SigScanner* getInstance()
    {
        static SigScanner inst;
        return &inst;
    };
    static void push(Address& _address, const std::string_view _signature, const callback_t& _callback)
    {
        parsed_t parsed = hat::parse_signature(_signature);
        assert(parsed.has_value() && "Failed to parse signature");
        getInstance()->mTasks.emplace_back(_address, parsed, _signature, _callback);
    }

    static void execute()
    {
        for (auto& task : getInstance()->mTasks) {
            Address& dest = task.mDest;
            const hat::scan_result scan = hat::find_pattern(task.mSignature.value(), ".text");
            assert(scan.has_value() && "Signature is invalid");
            dest = reinterpret_cast<uintptr_t>(scan.get());
            if (task.mCallback.has_value())
                dest = task.mCallback.value()(dest);
            getInstance()->mCached[task.mSignatureView] = dest;
        };
    }
};
