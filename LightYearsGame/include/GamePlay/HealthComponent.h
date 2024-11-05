#pragma once
#include "framework/Delegate.h"

namespace ly {
    class HealthComponent {
    public:
        HealthComponent(float health, float maxHealth);
        void changeHealth(float health);
        float getHealth() const{return mHealth;}
        float getMaxHealth() const{return mMaxHealth;}
        Delegate<float, float, float> onHealthChanged;
        Delegate<float, float, float> onTakenDamages;
        Delegate<> onHealthEmpty;

    private:
        float mHealth;
        float mMaxHealth;
        void TakenDamage(float amt);
        void HealthEmpty();


    };

}
