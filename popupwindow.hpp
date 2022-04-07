/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#ifndef POPUPWINDOW_HPP_INCLUDED
#define POPUPWINDOW_HPP_INCLUDED

namespace tfp
{
    /// Wyswietla okno do wyboru pliku i zwraca do niego sciezke
    std::string OpenFileName(tfp::Game *GameHandle, std::string Filter = "\0*.*\0", std::string Directory = ".\\");
    /// Przykladowy Filter = "Text files\0*.TXT\0All files\0*.*\0"
    /// Wyswietla okno do wyboru pliku do zapisu i zwraca do niego sciezke
    std::string SaveFileName(tfp::Game *GameHandle, std::string Filter = "\0*.*\0", std::string Directory = ".\\");
}

#endif // POPUPWINDOW_HPP_INCLUDED
