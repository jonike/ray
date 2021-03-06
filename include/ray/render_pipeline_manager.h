// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
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
#ifndef _H_RENDER_PIPELINE_MANAGER_H_
#define _H_RENDER_PIPELINE_MANAGER_H_

#include <ray/render_setting.h>

_NAME_BEGIN

class RenderPipelineManager final : public rtti::Interface
{
	__DeclareSubClass(RenderPipelineManager, rtti::Interface)
public:
	RenderPipelineManager() noexcept;
	RenderPipelineManager(const RenderSetting& setting) except;
	~RenderPipelineManager() noexcept;

	void setup(const RenderSetting& setting) except;
	void close() noexcept;

	void setRenderPipeline(const RenderPipelinePtr& pipeline) noexcept;
	const RenderPipelinePtr& getRenderPipeline() const noexcept;

	void setRenderPipelineDevice(const RenderPipelineDevicePtr& device) noexcept;
	const RenderPipelineDevicePtr& getRenderPipelineDevice() const noexcept;

	void setWindowResolution(std::uint32_t w, std::uint32_t h) noexcept;
	void getWindowResolution(std::uint32_t& w, std::uint32_t& h) const noexcept;

	void setFramebufferSize(std::uint32_t w, std::uint32_t h) noexcept;
	void getFramebufferSize(std::uint32_t& w, std::uint32_t& h) const noexcept;

	bool setRenderSetting(const RenderSetting& setting) noexcept;
	const RenderSetting& getRenderSetting() const noexcept;

	void addPostProcess(RenderPostProcessPtr postprocess) noexcept;
	void removePostProcess(RenderPostProcessPtr postprocess) noexcept;
	void destroyPostProcess() noexcept;

	void renderBegin() noexcept;
	void render(const RenderScene& scene) noexcept;
	void renderEnd() noexcept;

private:
	bool setupShadowRenderer(RenderPipelinePtr pipeline, const RenderSetting& setting) noexcept;
	void destroyShadowRenderer() noexcept;

private:
	RenderPipelineManager(const RenderPipelineManager&) noexcept = delete;
	RenderPipelineManager& operator = (const RenderPipelineManager&) noexcept = delete;

private:
	RenderSetting _setting;
	RenderPostProcessPtr _SSGI;
	RenderPostProcessPtr _SSDO;
	RenderPostProcessPtr _SSSS;
	RenderPostProcessPtr _atmospheric;
	RenderPostProcessPtr _SSR;
	RenderPostProcessPtr _DOF;
	RenderPostProcessPtr _fog;
	RenderPostProcessPtr _lightShaft;
	RenderPostProcessPtr _PostProcessHDR;
	RenderPostProcessPtr _FXAA;
	RenderPostProcessPtr _colorGrading;

	RenderPipelinePtr _pipeline;
	RenderPipelineDevicePtr _pipelineDevice;
	RenderPipelineControllerPtr _forward;
	RenderPipelineControllerPtr _lightProbeGen;
	RenderPipelineControllerPtr _deferredLighting;
	RenderPipelineControllerPtr _shadowMapGen;
};

_NAME_END

#endif