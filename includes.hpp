/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef INCLUDES_HPP_INCLUDED
#define INCLUDES_HPP_INCLUDED


/// Standardowe
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>
#include <stdexcept>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
#include <clocale>
#include <dirent.h>
#include <limits>

#ifdef TFP_DEBUG
    #include <cfenv>
#endif // TFP_DEBUG


#include "defines.hpp"

#if SYSTEM_WINDOWS == 1
#include <windows.h>
#include <conio.h>
#endif // SYSTEM_WINDOWS

#if SYSTEM_LINUX == 1
#include <ncurses.h>
#include <unistd.h>
#endif // SYSTEM_LINUX

#if SYSTEM_IOS == 1
// :c
#endif // SYSTEM_MAC

/// SFML
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

/// Kody innych ludzi
#include "pixelperfectcollision.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
//#include "rapidxml_iterators.hpp"



/// Predeklaracje klas
#include "classpredeclaration.hpp"
#include "datatypes.hpp"

/// System
#include "tfpstl.hpp"
#include "textmanipulation.hpp"
#include "dateandtime.hpp"
#include "popupwindow.hpp"
#include "filesystem.hpp"
#include "debug.hpp"
#include "clock.hpp"
#include "functiontime.hpp"
#include "keyconfiguration.hpp"
#include "generator.hpp"


#include "language.hpp"

#include "loading.hpp"
#include "backgroundimage.hpp"
#include "screen.hpp"
#include "mouse.hpp"
#include "sprite.hpp"
#include "font.hpp"
#include "text.hpp"
#include "area.hpp"
#include "button.hpp"
#include "camera.hpp"

/// Special effets
#include "interfaceffects.hpp"

/// GameObjects
#include "window.hpp"
#include "animation.hpp"
#include "characteranimation.hpp"
#include "terrain.hpp"
#include "item.hpp"
#include "map.hpp"
#include "character.hpp"
#include "chat.hpp"
#include "interface.hpp"

/// Network
#include "client.hpp"
#include "server.hpp"

/// Menedzer gier
#include "commandblock.hpp"
#include "game.hpp"
#include "gamemanager.hpp"

#endif // INCLUDES_HPP_INCLUDED
