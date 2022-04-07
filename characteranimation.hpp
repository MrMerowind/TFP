#ifndef CHARACTERANIMATION_HPP_INCLUDED
#define CHARACTERANIMATION_HPP_INCLUDED

namespace tfp
{
    class CharacterAnimation
    {
    private:
        std::string SkinName;
        tfp::Animation Animation;
        sf::Vector2f Position;
        sf::Vector2f CurrentPosition;
        sf::Vector2f DestinationPosition;
        tfp::Direction LookingDirection;
        int AttackAnimation;
        bool Dying;
        bool Dead;

    public:
        CharacterAnimation();
        ~CharacterAnimation();
        void SetSkinName(std::string Name);
        void SetPosition(sf::Vector2f Position);
        void SetPosition(float PositionX, float PositionY);
        void SetCurrentPosition(sf::Vector2f Position);
        void SetCurrentPosition(float PositionX, float PositionY);
        void SetDestinationPosition(sf::Vector2f Position);
        void SetDestinationPosition(float PositionX, float PositionY);
        void SetLookingDirection(tfp::Direction LookingDirection);
        void SetAttackAnimation(int AnimationIndex);
        void DrawCharacter(tfp::Game *GameHandle, float DeltaTime = 0.0f, float MovementSpeed = 1.0f, float AttackSpeed = 1.0f);
        void DrawCharacter(tfp::Game *GameHandle, tfp::Player &PlayerRef, float DeltaTime = 0.0f);
        std::string &GetSkinName();
        sf::Vector2f GetPosition();
        sf::Vector2f &GetCurrentPosition();
        sf::Vector2f &GetDestinationPosition();
        tfp::Direction &GetLookingDirection();
        int &GetAttackAnimationIndex();
        float GetWidth();
        float GetHeight();
    };
}

#endif // CHARACTERANIMATION_HPP_INCLUDED
