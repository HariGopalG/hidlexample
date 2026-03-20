#define LOG_TAG "hellohidl-client"

#include <log/log.h>

#include <vendor/example/hellohidl/1.0/IHello.h>

using ::android::hardware::Return;
using ::android::sp;
using vendor::example::hellohidl::V1_0::IHello;

int main() {
    sp<IHello> service = IHello::getService();
    if (service == nullptr) {
        ALOGE("Unable to find vendor.example.hellohidl@1.0::IHello/default");
        return 1;
    }

    Return<void> helloStatus = service->sayHello("Android 15 native client");
    if (!helloStatus.isOk()) {
        ALOGE("sayHello transaction failed: %s", helloStatus.description().c_str());
        return 1;
    }

    Return<int32_t> addResult = service->add(7, 35);
    if (!addResult.isOk()) {
        ALOGE("add transaction failed: %s", addResult.description().c_str());
        return 1;
    }

    Return<uint32_t> countResult = service->getRequestCount();
    if (!countResult.isOk()) {
        ALOGE("getRequestCount transaction failed: %s", countResult.description().c_str());
        return 1;
    }

    ALOGI("Service add(7, 35) returned %d", static_cast<int32_t>(addResult));
    ALOGI("Service request count is now %u", static_cast<uint32_t>(countResult));
    return 0;
}
