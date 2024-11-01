#pragma once

namespace ly {
    class HealthComponent {
    public:
        HealthComponent(float health, float maxHealth);
        void changeHealth(float health);
        float getHealth() const{return mHealth;}
        float getMaxHealth() const{return mMaxHealth;}

    private:
        float mHealth;
        float mMaxHealth;
        void TakenDamage(float amt);
        void HealthEmpty();
        void HealthRegen(float amt);

    };

}
