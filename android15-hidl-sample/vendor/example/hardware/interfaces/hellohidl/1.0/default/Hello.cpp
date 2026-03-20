#define LOG_TAG "vendor.example.hellohidl@1.0-impl"

#include "Hello.h"

#include <log/log.h>

namespace vendor::example::hellohidl::V1_0::implementation {

Return<void> Hello::sayHello(const hidl_string& name) {
    ++mRequestCount;
    ALOGI("Hello from HIDL service, client name=%s", name.c_str());
    return {};
}

Return<int32_t> Hello::add(int32_t left, int32_t right) {
    ++mRequestCount;
    const int32_t sum = left + right;
    ALOGI("add(%d, %d) = %d", left, right, sum);
    return sum;
}

Return<uint32_t> Hello::getRequestCount() {
    return mRequestCount.load();
}

}  // namespace vendor::example::hellohidl::V1_0::implementation
