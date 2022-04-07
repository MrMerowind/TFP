/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef DEFINES_HPP_INCLUDED
#define DEFINES_HPP_INCLUDED

//////////////////////////
/// System operacyjny
//////////////////////////

/// Platforma Windows
#define SYSTEM_WINDOWS 1

/// Platforma Linux
#define SYSTEM_LINUX 0

/// Platforma iOS
#define SYSTEM_IOS 0

/// Enables view configuration in Screen.config (Only for testing)
#define VIEW_TEST 0

// Wylaczamy testy w relase mode
#if TFP_RELEASE == 1
    #define VIEW_TEST 0
#endif // TFP_RELEASE

#ifdef TFP_DEBUG
    #define WRITE_IN_CONSOLE 1
#elif defined(TFP_RELEASE)
    #define WRITE_IN_CONSOLE 0
#else
    #error Missing TFP_DEBUG or TFP_RELEASE
#endif // TFP_DEBUG

const float _BasicMovementSpeed = 2.0f;

//////////////////////////
/// Temporary
//////////////////////////

#define FONT_SMOOTHING 1

#define TEST 1

/// Jesli sie wlaczy to pojawiaja sie paski na ekranie :c
#define GRAPHICBOOST 0

#endif // DEFINES_HPP_INCLUDED
