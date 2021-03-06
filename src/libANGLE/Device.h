//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// Device.h: Implements the egl::Device class, representing the abstract
// device. Implements EGLDevice.

#ifndef LIBANGLE_DEVICE_H_
#define LIBANGLE_DEVICE_H_

#include "common/angleutils.h"
#include "libANGLE/Error.h"
#include "libANGLE/Display.h"

#include <memory>

namespace rx
{
class DeviceImpl;
}

namespace egl
{
class Device final : angle::NonCopyable
{
  public:
    Device(Display *owningDisplay, rx::DeviceImpl *impl);
    virtual ~Device();

    Error getDevice(EGLAttrib *value);
    Display *getOwningDisplay() { return mOwningDisplay; };
    EGLint getType();

    const DeviceExtensions &getExtensions() const;
    const std::string &getExtensionString() const;

    rx::DeviceImpl *getImplementation() { return mImplementation.get(); }

    static egl::Error CreateDevice(EGLint deviceType, void *nativeDevice, Device **outDevice);
    static bool IsValidDevice(Device *device);

  private:
    void initDeviceExtensions();

    Display *mOwningDisplay;
    std::unique_ptr<rx::DeviceImpl> mImplementation;

    DeviceExtensions mDeviceExtensions;
    std::string mDeviceExtensionString;
};

}

#endif   // LIBANGLE_DEVICE_H_
