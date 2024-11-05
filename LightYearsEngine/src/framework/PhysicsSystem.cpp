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

   void PhysicsSystem::ProcessPendingRemoveListeners() {
       for (auto listener : mPendingRemoveListeners) {
           mPhysicsWorld.DestroyBody(listener);
       }
   }


   void PhysicsContactListener::BeginContact(b2Contact* contact) {

       Actor* actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
       Actor* actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

       if(actorA && !actorA->IsPendingDestroy()) {
           actorA->OnBeginOverlap(actorB);
       }

       if(actorB && !actorB->IsPendingDestroy()) {
           actorB->OnBeginOverlap(actorA);
       }
    }

    void PhysicsContactListener::EndContact(b2Contact* contact) {

       Actor* actorA = nullptr;
       Actor* actorB = nullptr;

       if(contact->GetFixtureA() && contact->GetFixtureA()->GetBody()) {
           actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
       }

       if(contact->GetFixtureB() && contact->GetFixtureB()->GetBody()) {
           actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

       }

       if(actorA && !actorA->IsPendingDestroy()) {
           actorA->OnEndOverlap(actorB);
       }
       if(actorB && !actorB->IsPendingDestroy()) {
           actorB->OnEndOverlap(actorA);
       }
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
        ProcessPendingRemoveListeners();
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

    void PhysicsSystem::Cleanup() {
        physicsSystem = std::move(unique<PhysicsSystem>{new PhysicsSystem});
    }
}
