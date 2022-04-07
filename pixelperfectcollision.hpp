/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef PIXELPERFECTCOLLISION_HPP_INCLUDED
#define PIXELPERFECTCOLLISION_HPP_INCLUDED

// Return the a float rect as an int rect.
inline sf::IntRect FToIRect(const sf::FloatRect& f);

/// Sprawdza kolizje miedzy dwoma sprajtami
bool PixelPerfectCollision(const sf::Sprite& a, const sf::Sprite& b, const sf::Image& imgA, const sf::Image& imgB);

/// Sprawdzan kolizje sprajta z punktem
bool PointCollision(const sf::Sprite &Sp, const sf::Vector2f Point);
#endif // PIXELPERFECTCOLLISION_HPP_INCLUDED
