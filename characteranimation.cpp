#include "includes.hpp"
#include "globalobjects.hpp"

/// Ostream bind

std::ostream &operator<<(std::ostream &Stream, sf::Vector2f &Right)
{
    Stream << Right.x << ":" << Right.y;
    return Stream;
}

/// Ostream End

tfp::CharacterAnimation::CharacterAnimation()
    :SkinName("Unknown"), Position({0.0f, 0.0f}), CurrentPosition({0.0f, 0.0f}), DestinationPosition({0.0f, 0.0f}),
    LookingDirection(tfp::Direction::DirDown), AttackAnimation(0), Dying(false), Dead(false) {}

tfp::CharacterAnimation::~CharacterAnimation() {}

void tfp::CharacterAnimation::SetSkinName(std::string Name)
{
    SkinName = Name;
}

void tfp::CharacterAnimation::SetPosition(sf::Vector2f Position_)
{
    Position = Position_;
}

void tfp::CharacterAnimation::SetPosition(float PositionX, float PositionY)
{
    Position.x = PositionX;
    Position.y = PositionY;
}

void tfp::CharacterAnimation::SetDestinationPosition(sf::Vector2f Position)
{
    DestinationPosition = Position;
}

void tfp::CharacterAnimation::SetDestinationPosition(float PositionX, float PositionY)
{
    DestinationPosition.x = PositionX;
    DestinationPosition.y = PositionY;
}

void tfp::CharacterAnimation::SetCurrentPosition(sf::Vector2f Position)
{
    CurrentPosition = Position;
}

void tfp::CharacterAnimation::SetCurrentPosition(float PositionX, float PositionY)
{
    CurrentPosition.x = PositionX;
    CurrentPosition.y = PositionY;
}

void tfp::CharacterAnimation::SetLookingDirection(tfp::Direction LookingDirection_)
{
    LookingDirection = LookingDirection_;
}

void tfp::CharacterAnimation::SetAttackAnimation(int AnimationIndex)
{
    AttackAnimation = AnimationIndex;
}

void tfp::CharacterAnimation::DrawCharacter(tfp::Game *GameHandle, tfp::Player &PlayerRef, float DeltaTime)
{
    DestinationPosition = PlayerRef.GetDestination();
    CurrentPosition = PlayerRef.GetPosition();
    DrawCharacter(GameHandle, DeltaTime, PlayerRef.MovementSpeed, PlayerRef.AttackSpeed);
}

void tfp::CharacterAnimation::DrawCharacter(tfp::Game *GameHandle, float DeltaTime, float MovementSpeed, float AttackSpeed)
{
    if(SkinName == "Unknown") return;

    /// Obliczanie wektora przesuniecia
    sf::Vector2f MoveVector = DestinationPosition - Position;/*CurrentPosition;*/

    /// Ustalanie kierunku patrzenia
    if(MoveVector.x == 0.0f && MoveVector.y == 0.0f)
    {

    }
    else if(std::abs(MoveVector.x) > std::abs(MoveVector.y))
    {
        if(MoveVector.x > 0)
        {
            LookingDirection = tfp::DirRight;
        }
        else
        {
            LookingDirection = tfp::DirLeft;
        }
    }
    else
    {
        if(MoveVector.y > 0)
        {
            LookingDirection = tfp::DirDown;
        }
        else
        {
            LookingDirection = tfp::DirTop;
        }
    }

    sf::Vector2f NormalizedMoveVector = tfp::NormalizeVector(MoveVector);

    sf::Vector2f FinalMoveVector = NormalizedMoveVector * _BasicMovementSpeed * MovementSpeed;

    /// Sprawdzanie czy wyliczone przesuniecie jest wieksze niz maksymalne przesuniecie
    if(MoveVector.x >= 0)
    {
        if(FinalMoveVector.x > MoveVector.x) FinalMoveVector.x = MoveVector.x;
    }
    else
    {
        if(FinalMoveVector.x < MoveVector.x) FinalMoveVector.x = MoveVector.x;
    }

    if(MoveVector.y >= 0)
    {
        if(FinalMoveVector.y > MoveVector.y) FinalMoveVector.y = MoveVector.y;
    }
    else
    {
        if(FinalMoveVector.y < MoveVector.y) FinalMoveVector.y = MoveVector.y;
    }

    // Position = DestinationPosition;
    Position += FinalMoveVector;

    /// Ustalenie aktywnej animacji
    std::string NewAnimationName = "Unknown";
    if(Dead)
    {
        NewAnimationName = SkinName + "_Dead";
    }
    else if(Dying)
    {
        NewAnimationName = SkinName + "_Death";
    }
    else if(AttackAnimation == 0)
    {
        if(LookingDirection == tfp::Direction::DirDown)
        {
            NewAnimationName = SkinName + "_Walk_Down";
        }
        else if(LookingDirection == tfp::Direction::DirTop)
        {
            NewAnimationName = SkinName + "_Walk_Up";
        }
        else if(LookingDirection == tfp::Direction::DirLeft)
        {
            NewAnimationName = SkinName + "_Walk_Left";
        }
        else if(LookingDirection == tfp::Direction::DirRight)
        {
            NewAnimationName = SkinName + "_Walk_Right";
        }
        else
        {
            Debug.Error("CharacterAnimation: Unknown Direction");
        }
    }
    else
    {
        NewAnimationName = SkinName + "_Attack_" + tfp::IntToString(AttackAnimation);
        if(LookingDirection == tfp::Direction::DirDown)
        {
            NewAnimationName += "_Down";
        }
        else if(LookingDirection == tfp::Direction::DirTop)
        {
            NewAnimationName += "_Up";
        }
        else if(LookingDirection == tfp::Direction::DirLeft)
        {
            NewAnimationName += "_Left";
        }
        else if(LookingDirection == tfp::Direction::DirRight)
        {
            NewAnimationName += "_Right";
        }
        else
        {
            Debug.Error("CharacterAnimation: Unknown Direction");
        }
    }

    if(NewAnimationName == "Unknown")
    {
        Debug.Error("CharacterAnimation: Can not estimate animation name");
    }
    else if(Animation.Name != NewAnimationName)
    {
        Animation.LoadAnimation(NewAnimationName, tfp::Animation::CharacterAnimation);
    }

    if(Dying || Dead)
    {
        GameHandle->GameScreen.Draw(Sprite.Create(Animation.GetTexture(DeltaTime, 1.0f), Position.x - GameHandle->GameCamera.GetPosition().x - Animation.Size.x / 2, Position.y - GameHandle->GameCamera.GetPosition().y - Animation.Size.y));
    }
    else if(AttackAnimation <= 0)
    {
        GameHandle->GameScreen.Draw(Sprite.Create(Animation.GetTexture(DeltaTime, MovementSpeed), Position.x  - GameHandle->GameCamera.GetPosition().x - Animation.Size.x / 2, Position.y  - GameHandle->GameCamera.GetPosition().y - Animation.Size.y));
    }
    else // AttackAnimation >0
    {
        GameHandle->GameScreen.Draw(Sprite.Create(Animation.GetTexture(DeltaTime, AttackSpeed), Position.x  - GameHandle->GameCamera.GetPosition().x - Animation.Size.x / 2, Position.y  - GameHandle->GameCamera.GetPosition().y - Animation.Size.y));
    }
}

std::string &tfp::CharacterAnimation::GetSkinName()
{
    return SkinName;
}

sf::Vector2f tfp::CharacterAnimation::GetPosition()
{
    return {std::floor(Position.x), std::floor(Position.y)};
}

sf::Vector2f &tfp::CharacterAnimation::GetCurrentPosition()
{
    return CurrentPosition;
}

sf::Vector2f &tfp::CharacterAnimation::GetDestinationPosition()
{
    return DestinationPosition;
}

tfp::Direction &tfp::CharacterAnimation::GetLookingDirection()
{
    return LookingDirection;
}

int &tfp::CharacterAnimation::GetAttackAnimationIndex()
{
    return AttackAnimation;
}

float tfp::CharacterAnimation::GetWidth()
{
    return Animation.GetColiderImage(0.0f, 0.0f, 0).getSize().x;
}

float tfp::CharacterAnimation::GetHeight()
{
    return Animation.GetColiderImage(0.0f, 0.0f, 0).getSize().y;
}
