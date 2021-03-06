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
#include <ray/physics_mesh_component.h>
#include <ray/physics_shape_mesh.h>
#include <ray/mesh_component.h>

_NAME_BEGIN

__ImplementSubClass(PhysicsMeshComponent, PhysicsShapeComponent, "PhysicsMesh")

PhysicsMeshComponent::PhysicsMeshComponent() noexcept
	: _onCollisionChange(std::bind(&PhysicsMeshComponent::onMeshChange, this))
{
}

PhysicsMeshComponent::~PhysicsMeshComponent() noexcept
{
}

GameComponentPtr
PhysicsMeshComponent::clone() const noexcept
{
	auto shape = std::make_shared<PhysicsMeshComponent>();
	return shape;
}

void
PhysicsMeshComponent::onAttachComponent(const GameComponentPtr& component) noexcept
{
	if (component->isInstanceOf<MeshComponent>())
		component->downcast<MeshComponent>()->addMeshChangeListener(&_onCollisionChange);
}

void
PhysicsMeshComponent::onDetachComponent(const GameComponentPtr& component) noexcept
{
	if (component->isInstanceOf<MeshComponent>())
		component->downcast<MeshComponent>()->removeMeshChangeListener(&_onCollisionChange);
}

void
PhysicsMeshComponent::onActivate() noexcept
{
	_buildShapeMesh();
}

void
PhysicsMeshComponent::onDeactivate() noexcept
{
	_shape.reset();
}

void
PhysicsMeshComponent::onMeshChange() noexcept
{
	_buildShapeMesh();
}

PhysicsShapePtr
PhysicsMeshComponent::getCollisionShape() noexcept
{
	return _shape;
}

void
PhysicsMeshComponent::_buildShapeMesh() noexcept
{
	auto component = this->getGameObject()->getComponent<ray::MeshComponent>();
	if (component)
	{
		auto mesh = component->getMesh();
		if (!mesh)
			return;

		if (mesh->getNumVertices() > 0)
		{
			auto meshShape = std::make_shared<PhysicsShapeMesh>();
			meshShape->setup(mesh->getVertexArray(), mesh->getIndicesArray(), mesh->getBoundingBox().aabb());
			_shape = meshShape;

			this->needUpdate();
		}
	}
}

_NAME_END