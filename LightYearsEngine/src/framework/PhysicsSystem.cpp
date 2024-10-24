#include "framework\PhysicsSystem.h"
#include <algorithm>

#include "box2d/b2_body.h"
#include "box2d/b2_contact.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"
#include "framework/Core.h"
#include "framework/MathUtility.h"

namespace ly{
   PhysicsSystem::PhysicsSystem()
        : mPhysicsWorld{b2Vec2{0.f, 0.f}}
        , mPhysicsScale{0.01f}
        , mVelocityIterations{8}
        , mPositionIterations{3}
        , mContactListener{}
    {
       mPhysicsWorld.SetContactListener(&mContactListener);
       mPhysicsWorld.SetAllowSleeping(false);
    }


    void PhysicsContactListener::BeginContact(b2Contact* contact) {
        LOG("PhysicsContactListener::BeginContact");

       Actor* actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
       Actor* actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
    }

    void PhysicsContactListener::EndContact(b2Contact* contact) {
        LOG("PhysicsContactListener::EndContact");
       Actor* actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    }

    unique<PhysicsSystem> PhysicsSystem::physicsSystem{nullptr};
    PhysicsSystem& PhysicsSystem::Get() {

        if(!physicsSystem) {
            physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
            return *physicsSystem;
        }
        return *physicsSystem;
    }

    void PhysicsSystem::Step(float deltaTime) {
        mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
    }

    b2Body* PhysicsSystem::AddListener(Actor* listener) {
        if(listener->IsPendingDestroy()) return nullptr;
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
        bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(), listener->GetActorLocation().y * GetPhysicsScale());
        bodyDef.angle = DegreesToRadians(listener->GetActorRotation());
        b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);
        b2PolygonShape shape;
        auto bounds = listener->GetActorGlobalBounds();
        shape.SetAsBox(bounds.width/2.f * GetPhysicsScale(), bounds.height/2.f * GetPhysicsScale());
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.isSensor = true;

        body->CreateFixture(&fixtureDef);

        return body;

    }

    float PhysicsSystem::GetPhysicsScale() const {
        return mPhysicsScale;
    }

    void PhysicsSystem::RemoveListener(b2Body* bodyToRemove) {
        //todo remove listener

    }
}
