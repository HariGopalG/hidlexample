# Sample Android 15 HIDL Native Service and Client

This repository contains a small binderized HIDL sample that you can drop into an AOSP-style tree to learn how a native HAL service and a native client talk over `hwbinder`.

HIDL is legacy on modern Android releases and stable AIDL is preferred for new production HALs. This sample is still useful for understanding existing vendor stacks and for bring-up on devices that already rely on HIDL.

## Layout

```text
vendor/example/hardware/interfaces/
|-- Android.bp
`-- hellohidl/
    |-- 1.0/
    |   |-- Android.bp
    |   |-- IHello.hal
    |   `-- default/
    |       |-- Android.bp
    |       |-- Hello.cpp
    |       |-- Hello.h
    |       |-- service.cpp
    |       |-- vendor.example.hellohidl@1.0-service.rc
    |       `-- vendor.example.hellohidl@1.0-service.xml
    |-- client/
    |   |-- Android.bp
    |   `-- main.cpp
    `-- sepolicy/vendor/
        |-- file_contexts
        |-- hal_hellohidl.te
        |-- hal_hellohidl_default.te
        `-- hwservice_contexts
```

## What the sample does

The HIDL interface exposes three methods:

- `sayHello(string name)` logs the client name in the service process
- `add(int32_t left, int32_t right)` returns the sum through HIDL
- `getRequestCount()` returns how many service calls have been processed

The service registers itself as `vendor.example.hellohidl@1.0::IHello/default`, and the client discovers it with `IHello::getService()`.

## Important source files

- `vendor/example/hardware/interfaces/hellohidl/1.0/IHello.hal`: HIDL contract
- `vendor/example/hardware/interfaces/hellohidl/1.0/default/Hello.cpp`: service implementation
- `vendor/example/hardware/interfaces/hellohidl/1.0/default/service.cpp`: service registration and RPC threadpool startup
- `vendor/example/hardware/interfaces/hellohidl/client/main.cpp`: native client

## Build steps inside AOSP

1. Copy the `vendor/example/hardware/interfaces` tree into your Android source checkout under the same path.
2. Add the service and client modules to your device product makefile if needed:

```make
PRODUCT_PACKAGES += \
    vendor.example.hellohidl@1.0-service \
    hellohidl-client
```

3. Include the SELinux snippets in your device/vendor sepolicy if your device policy tree does not already have equivalent rules.
4. Build the modules:

```bash
source build/envsetup.sh
lunch <target>
m vendor.example.hellohidl@1.0-service hellohidl-client
```

## Running the sample

After flashing or syncing the artifacts to the device:

```bash
adb shell start vendor.example.hellohidl-1-0
adb shell /vendor/bin/hellohidl-client
adb logcat -s vendor.example.hellohidl@1.0-service vendor.example.hellohidl@1.0-impl hellohidl-client
```

Expected client-side result:

```text
Service add(7, 35) returned 42
Service request count is now 2
```

Expected service-side logs include the greeting and the add request.

## Notes for Android 15

- The sample uses `unstable: true` in `hidl_interface` so you can iterate without freezing the HIDL hash. For production, freeze the interface and remove `unstable: true`.
- New Android platform work should prefer stable AIDL. Use this sample mainly for compatibility, learning, or maintaining an existing HIDL stack.
- Real devices usually need additional SELinux allow rules for specific client domains that call into the HAL.
