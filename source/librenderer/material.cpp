// +----------------------------------------------------------------------
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
#include <ray/material.h>

_NAME_BEGIN

Material::Material() noexcept
{
}

Material::~Material() noexcept
{
	this->close();
}

void
Material::setup() except
{
	for (auto& technique : _techniques)
	{
		auto& passList = technique->getPassList();
		for (auto& pass : passList)
			pass->setup(*this);
	}
}

void
Material::close() noexcept
{
	for (auto& technique : _techniques)
	{
		auto& passList = technique->getPassList();
		for (auto& pass : passList)
			pass->close();
	}

	_techniques.clear();
	_parameters.clear();
}

void
Material::addTech(MaterialTechPtr technique) noexcept
{
	assert(technique);
	assert(std::find(_techniques.begin(), _techniques.end(), technique) == _techniques.end());
	_techniques.push_back(technique);
}

void
Material::removeTech(MaterialTechPtr technique) noexcept
{
	assert(technique);
	auto it = std::find(_techniques.begin(), _techniques.end(), technique);
	if (it != _techniques.end())
	{
		_techniques.erase(it);
	}
}

MaterialTechPtr
Material::getTech(RenderQueue queue) noexcept
{
	for (auto& it : _techniques)
	{
		if (it->getRenderQueue() == queue)
			return it;
	}

	return nullptr;
}

MaterialTechniques&
Material::getTechs() noexcept
{
	return _techniques;
}

void
Material::addParameter(MaterialParamPtr parameter) noexcept
{
	assert(parameter);
	assert(std::find(_parameters.begin(), _parameters.end(), parameter) == _parameters.end());
	_parameters.push_back(parameter);
}

void
Material::removeParameter(MaterialParamPtr parameter) noexcept
{
	assert(parameter);
	auto it = std::find(_parameters.begin(), _parameters.end(), parameter);
	if (it != _parameters.end())
	{
		_parameters.erase(it);
	}
}

MaterialParamPtr
Material::getParameter(const std::string& name) const noexcept
{
	assert(!name.empty());
	for (auto& it : _parameters)
	{
		if (it->getName() == name)
			return it;
	}

	return nullptr;
}

MaterialParams&
Material::getParameters() noexcept
{
	return _parameters;
}

const MaterialParams&
Material::getParameters() const noexcept
{
	return _parameters;
}

_NAME_END