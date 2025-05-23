/////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Tencent is pleased to support the open source community by making tgfx available.
//
//  Copyright (C) 2023 THL A29 Limited, a Tencent company. All rights reserved.
//
//  Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
//  in compliance with the License. You may obtain a copy of the License at
//
//      https://opensource.org/licenses/BSD-3-Clause
//
//  unless required by applicable law or agreed to in writing, software distributed under the
//  license is distributed on an "as is" basis, without warranties or conditions of any kind,
//  either express or implied. see the license for the specific language governing permissions
//  and limitations under the license.
//
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "gpu/Texture.h"
#include "tgfx/gpu/opengl/qt/QGLDevice.h"
#ifdef __APPLE__
#include "gpu/opengl/cgl/CGLHardwareTexture.h"
#endif
#include "tgfx/platform/HardwareBuffer.h"

namespace tgfx {
#ifdef __APPLE__

bool HardwareBufferAvailable() {
  return true;
}

std::shared_ptr<Texture> Texture::MakeFrom(Context* context, HardwareBufferRef hardwareBuffer,
                                           YUVColorSpace) {
  if (!HardwareBufferCheck(hardwareBuffer)) {
    return nullptr;
  }
  auto qglDevice = static_cast<QGLDevice*>(context->device());
  if (qglDevice == nullptr) {
    return nullptr;
  }
  auto textureCache = qglDevice->getTextureCache();
  return CGLHardwareTexture::MakeFrom(context, hardwareBuffer, textureCache);
}

#else

bool HardwareBufferAvailable() {
  return false;
}

std::shared_ptr<Texture> Texture::MakeFrom(Context*, HardwareBufferRef, YUVColorSpace) {
  return nullptr;
}

#endif
}  // namespace tgfx