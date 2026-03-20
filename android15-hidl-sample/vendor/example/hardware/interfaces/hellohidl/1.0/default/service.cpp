#define LOG_TAG "vendor.example.hellohidl@1.0-service"

#include <hidl/HidlTransportSupport.h>
#include <log/log.h>
#include <utils/Errors.h>

#include "Hello.h"

using ::android::OK;
using ::android::hardware::configureRpcThreadpool;
using ::android::hardware::joinRpcThreadpool;
using ::android::sp;
using vendor::example::hellohidl::V1_0::implementation::Hello;

int main() {
    configureRpcThreadpool(1, true);

    sp<Hello> service = new Hello();
    const auto status = service->registerAsService();
    if (status != OK) {
        ALOGE("Failed to register vendor.example.hellohidl@1.0::IHello: %d", status);
        return 1;
    }

    ALOGI("vendor.example.hellohidl@1.0-service is ready");
    joinRpcThreadpool();
    return 0;
}
