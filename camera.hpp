/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

namespace tfp
{
    class Camera
    {
    private:
        sf::Vector2f CameraPosition;
        sf::Vector2f ReturnedCameraPosition;
        sf::Rect<float> CameraBorders;
        bool Borders;
        bool LockedOnPlayer;
        void CheckBorders();
        tfp::Game *GameHandle;
        sf::Vector2f CameraShakePosition;
        float CameraShakeBufferTime;
        float CameraShakeBufferTimeSecond;
        bool CameraShake;

    public:
        /// Konstruktor
        Camera();
        /// Destruktor
        ~Camera();
        /// Ustawienie uchwytu gry
        void SetGameHandle(tfp::Game *Handle);
        /// Zwraca pozycje kamery
        sf::Vector2f &GetPosition();
        /// Ustawia pozycje kamery
        void SetPosition(float PositionX, float PositionY);
        /// Ustawia pozycje kamery
        void SetPosition(sf::Vector2f Coordinates);
        /// Przesuwa pozycje kamery
        void Move(float PositionX, float PositionY);
        /// Przesuwa pozycje kamery
        void SmoothMove(float PositionX, float PositionY);
        /// Przesuwa pozycje kamery
        void Move(sf::Vector2f Coordinates);
        /// Ustawia granice przesuwania kamery
        void SetBorders(sf::Rect<float> CameraBorders);
        /// Ustawia granice przesuwania kamery
        void SetBorders(float PositionX, float PositionY, float Width, float Height);
        /// Blokuje kamere na postaci i w granicach przesuwania
        void Lock();
        /// Pozycja kamery moze byc dowolna
        void Unlock();
        /// Zwraca czy kamera jest zablokowana
        const bool IsLocked();
        /// Shakes camera
        void ShakeCamera();
        /// Calculates camera shake
        void CalculateShake();
        /// Blokuje kamere na graczu
        void LockOnPlayer(bool State);
        /// Zwraca czy kamera jest zablokowana na graczu
        bool IsLockedOnPlayer();
    };
}

#endif // CAMERA_HPP_INCLUDED
