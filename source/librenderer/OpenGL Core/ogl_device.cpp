// +---------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#include "ogl_device.h"
#include "ogl_device_context.h"
#include "ogl_canvas.h"
#include "ogl_state.h"
#include "ogl_shader.h"
#include "ogl_texture.h"
#include "ogl_framebuffer.h"
#include "ogl_layout.h"
#include "ogl_vbo.h"
#include "ogl_ibo.h"
#include "ogl_dibo.h"
#include "ogl_commandlist.h"
#include "ogl_sampler.h"

_NAME_BEGIN

OGLDevice::OGLDevice() noexcept
{
}

OGLDevice::~OGLDevice() noexcept
{
}

GraphicsContextPtr
OGLDevice::createGraphicsContext(WindHandle win) noexcept
{
	auto context = std::make_shared<OGLDeviceContext>();
	if (context->open(win))
		return context;
	return nullptr;
}

GraphicsStatePtr
OGLDevice::createGraphicsState(const GraphicsStateDesc& desc) noexcept
{
	auto state = std::make_shared<OGLGraphicsState>();
	if (state->setup(desc))
		return state;
	return nullptr;
}

GraphicsLayoutPtr
OGLDevice::createGraphicsLayout(const GraphicsLayoutDesc& desc) noexcept
{
	auto layout = std::make_shared<OGLGraphicsLayout>();
	if (layout->open(desc))
		return layout;
	return nullptr;
}

GraphicsDataPtr
OGLDevice::createGraphicsData(const GraphicsDataDesc& desc) noexcept
{
	auto type = desc.getType();

	if (type == GraphicsStream::VBO)
		return std::make_shared<OGLVertexBuffer>(desc);
	else if (type == GraphicsStream::IBO)
		return std::make_shared<OGLIndexBuffer>(desc);
	else if (type == GraphicsStream::DIBO)
		return std::make_shared<OGLDrawIndirectBuffer>(desc);

	return nullptr;
}

GraphicsTexturePtr
OGLDevice::createGraphicsTexture(const GraphicsTextureDesc& desc) noexcept
{
	auto texture = std::make_shared<OGLTexture>();
	if (texture->setup(desc))
		return texture;
	return nullptr;
}

GraphicsSamplerPtr
OGLDevice::createGraphicsSampler(const GraphicsSamplerDesc& desc) noexcept
{
	return std::make_shared<OGLSampler>();
}

GraphicsRenderTexturePtr
OGLDevice::createRenderTexture(const GraphicsRenderTextureDesc& desc) noexcept
{
	auto texture = std::make_shared<OGLRenderTexture>();
	if (texture->setup(desc))
		return texture;
	return nullptr;
}

GraphicsMultiRenderTexturePtr
OGLDevice::createMultiRenderTexture(const GraphicsMultiRenderTextureDesc& desc) noexcept
{
	auto texture = std::make_shared<OGLMultiRenderTexture>();
	if (texture->setup(desc))
		return texture;
	return nullptr;
}

ShaderPtr
OGLDevice::createShader() noexcept
{
	return std::make_shared<OGLShader>();
}

ShaderObjectPtr
OGLDevice::createShaderObject() noexcept
{
	return std::make_shared<OGLShaderObject>();
}

_NAME_END