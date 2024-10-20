#pragma once
#include "Core.h"
#include "box2d/b2_world.h"
#include "Actor.h"
namespace  ly {
    class Actor;
    class PhysicsContactListener : public b2ContactListener {
        virtual void BeginContact(b2Contact* contact) override;
        virtual void EndContact(b2Contact* contact) override;
    };
    class PhysicsSystem {
    public:
        static PhysicsSystem& Get();
        void Step(float deltaTime);
        b2Body* AddListener(Actor* listener);
        float GetPhysicsScale() const;

        void RemoveListener(b2Body* bodyToRemove);

    protected:
        PhysicsSystem();
    private:
        static unique<PhysicsSystem> physicsSystem;
        b2World mPhysicsWorld;
        float mPhysicsScale;
        int mVelocityIterations;
        int mPositionIterations;
        PhysicsContactListener mContactListener;
    };
}
