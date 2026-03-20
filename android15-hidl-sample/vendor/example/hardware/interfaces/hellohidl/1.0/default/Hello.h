#pragma once

#include <atomic>

#include <vendor/example/hellohidl/1.0/IHello.h>

namespace vendor::example::hellohidl::V1_0::implementation {

using ::android::hardware::Return;
using ::android::hardware::hidl_string;

struct Hello : public IHello {
    Return<void> sayHello(const hidl_string& name) override;
    Return<int32_t> add(int32_t left, int32_t right) override;
    Return<uint32_t> getRequestCount() override;

private:
    std::atomic<uint32_t> mRequestCount{0};
};

}  // namespace vendor::example::hellohidl::V1_0::implementation
