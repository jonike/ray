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
#ifndef _H_GAME_OBJECT_MANAGER_H_
#define _H_GAME_OBJECT_MANAGER_H_

#include <stack>
#include <ray/game_features.h>

_NAME_BEGIN

struct EXPORT RaycastHit
{
	RaycastHit() noexcept;

	GameObject* object;
	std::size_t mesh;
	float distance;
};

class EXPORT GameObjectManager final
{
	__DeclareSingleton(GameObjectManager)
public:
	GameObjectManager() noexcept;
	~GameObjectManager() noexcept;

	GameObjectPtr findObject(const util::string& name) noexcept;
	GameObjectPtr findActiveObject(const util::string& name) noexcept;

	GameObjectPtr instantiate(const util::string& name) noexcept;

	std::size_t raycastHit(const Raycast3& ray, RaycastHit& hit, std::function<bool(GameObject*)> comp = nullptr) noexcept;
	std::size_t raycastHit(const Vector3& orgin, const Vector3& end, RaycastHit& hit, std::function<bool(GameObject*)> comp = nullptr) noexcept;

	bool activeObject(const util::string& name) noexcept;

	void onFrameBegin() noexcept;
	void onFrame() noexcept;
	void onFrameEnd() noexcept;

private:
	friend GameObject;

	void _instanceObject(GameObject* entity, std::size_t& instanceID) noexcept;
	void _unsetObject(GameObject* entity) noexcept;
	void _activeObject(GameObject* entity, bool active) noexcept;

private:
	bool _hasEmptyActors;

	std::stack<std::size_t> _emptyLists;
	std::vector<GameObject*> _instanceLists;
	std::vector<GameObject*> _activeActors;
};

_NAME_END

#endif
