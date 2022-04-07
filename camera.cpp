/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"
#include "globalobjects.hpp"

tfp::Camera::Camera()
    :CameraPosition({0.0f, 0.0f}), CameraBorders({0.0f, 0.0f, 0.0f, 0.0f}), Borders(true), LockedOnPlayer(false),  GameHandle(nullptr), CameraShakePosition({0.0f, 0.0f}), CameraShakeBufferTime(0.0f), CameraShake(false) {}

tfp::Camera::~Camera() {}

void tfp::Camera::SetGameHandle(tfp::Game *Handle)
{
    GameHandle = Handle;
}

sf::Vector2f &tfp::Camera::GetPosition()
{
    /// Prawdziwa pozycja
    /*
    if(CameraShake)
    {
        ReturnedCameraPosition.x = CameraPosition.x + CameraShakePosition.x;
        ReturnedCameraPosition.y = CameraPosition.y + CameraShakePosition.y;
    }
    else
    {
        ReturnedCameraPosition.x = CameraPosition.x;
        ReturnedCameraPosition.y = CameraPosition.y;
    }
    return ReturnedCameraPosition;
    */
    /// Zaokraglona pozycja
    if(CameraShake)
    {
        ReturnedCameraPosition.x = std::floor(CameraPosition.x + CameraShakePosition.x);
        ReturnedCameraPosition.y = std::floor(CameraPosition.y + CameraShakePosition.y);
    }
    else
    {
        ReturnedCameraPosition.x = std::floor(CameraPosition.x);
        ReturnedCameraPosition.y = std::floor(CameraPosition.y);
    }

    return ReturnedCameraPosition;
}

void tfp::Camera::Lock()
{
    Borders = true;
    CheckBorders();
}

void tfp::Camera::Unlock()
{
    Borders = false;
}

const bool tfp::Camera::IsLocked()
{
    return Borders;
}

void tfp::Camera::LockOnPlayer(bool State)
{
    LockedOnPlayer = State;
}

bool tfp::Camera::IsLockedOnPlayer()
{
    return LockedOnPlayer;
}

void tfp::Camera::ShakeCamera()
{
    CameraShakePosition = {0.0f, 0.0f};
    CameraShakeBufferTime = 0.0f;
    CameraShakeBufferTimeSecond = 0.0f;
    CameraShake = true;

}

void tfp::Camera::CalculateShake()
{
    CameraShakeBufferTime += Clock.GetDeltaTime();
    CameraShakeBufferTimeSecond += Clock.GetDeltaTime();
    if(CameraShakeBufferTime > 1.0f)
    {
        CameraShake = false;
    }

    if(CameraShakeBufferTimeSecond >= 0.04f)
    {
        CameraShakeBufferTimeSecond -= 0.04f;
        CameraShakePosition = {(float) (Generator.RandomInt(0, 50) - 25)/* * Clock.GetDeltaTime()*/, (float) (Generator.RandomInt(0, 50) - 25)/* * Clock.GetDeltaTime()*/};
    }

}

void tfp::Camera::CheckBorders()
{
    if(GameHandle == nullptr)
    {
        return;
    }
    if(CameraBorders.width < 0.0f || CameraBorders.height < 0.0f) Borders = false;
    if(Borders)
    {
        if(CameraPosition.x > (CameraBorders.left + CameraBorders.width) - GameHandle->GameScreen.GetViewSize().x)
            CameraPosition.x = (CameraBorders.left + CameraBorders.width) - GameHandle->GameScreen.GetViewSize().x;
        if(CameraPosition.y > (CameraBorders.top + CameraBorders.height) - GameHandle->GameScreen.GetViewSize().y)
            CameraPosition.y = (CameraBorders.top + CameraBorders.height) - GameHandle->GameScreen.GetViewSize().y;
        if(CameraPosition.x < CameraBorders.left)
            CameraPosition.x = CameraBorders.left;
        if(CameraPosition.y < CameraBorders.top)
            CameraPosition.y = CameraBorders.top;
    }
}

void tfp::Camera::SetPosition(float PositionX, float PositionY)
{
    CameraPosition.x = PositionX;
    CameraPosition.y = PositionY;
    CheckBorders();
}

void tfp::Camera::SetPosition(sf::Vector2f Coordinates)
{
    CameraPosition.x = Coordinates.x;
    CameraPosition.y = Coordinates.y;
    CheckBorders();
}

void tfp::Camera::Move(float PositionX, float PositionY)
{
    SetPosition(CameraPosition.x + PositionX, CameraPosition.y + PositionY);
    CheckBorders();
}

void tfp::Camera::SmoothMove(float PositionX, float PositionY)
{
    float EstimatedMoveX = PositionX * Clock.GetDeltaTime() * 2.0f;
    float EstimatedMoveY = PositionY * Clock.GetDeltaTime() * 2.0f;

    if(PositionX >= 0 && EstimatedMoveX > PositionX) EstimatedMoveX = PositionX;
    else if(PositionX < 0 && EstimatedMoveX < PositionX) EstimatedMoveX = PositionX;

    if(PositionY >= 0 && EstimatedMoveY > PositionY) EstimatedMoveY = PositionY;
    else if(PositionY < 0 && EstimatedMoveY < PositionY) EstimatedMoveY = PositionY;

    Move(EstimatedMoveX, EstimatedMoveY);
}


void tfp::Camera::Move(sf::Vector2f Coordinates)
{
    SetPosition(CameraPosition.x + Coordinates.x, CameraPosition.y + Coordinates.y);
    CheckBorders();
}

void tfp::Camera::SetBorders(sf::Rect<float> CameraBorders_)
{
    CameraBorders = CameraBorders_;
}

void tfp::Camera::SetBorders(float PositionX, float PositionY, float Width, float Height)
{
    CameraBorders.left = PositionX;
    CameraBorders.top = PositionY;
    CameraBorders.width = Width;
    CameraBorders.height = Height;
}


