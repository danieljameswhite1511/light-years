#include "framework\PhysicsSystem.h"

#include <algorithm>

#include "framework/Core.h"

namespace ly{

    unique<PhysicsSystem> PhysicsSystem::physicsSystem{nullptr};

    PhysicsSystem& PhysicsSystem::Get() {

        if(!physicsSystem) {
            physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
            return *physicsSystem;
        }
        return *physicsSystem;
    }

    PhysicsSystem::PhysicsSystem()
        : mPhysicsWorld{b2Vec2{0.f, 0.f}}
        , mPhysicsScale{0.01f}
    {
    }
}
