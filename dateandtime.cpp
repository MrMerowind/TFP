/*************************************
*                                    *
*          TFP Game Engine           *
*   Copyright © 2018 Ernest Mężyk    *
*                                    *
*************************************/
#include "includes.hpp"


time_t tfp::Seconds()
{
    return time(nullptr);
}

std::string tfp::Date(std::string Format, time_t Time)
{
    tm *ltm = localtime(&Time);

    std::string Return;
    bool Skip = false;
    for(int i = 0; tfp::NotBelowZero(i) < Format.size(); i++)
    {
        if(Skip == true)
        {
            Return += Format[i];
            Skip = false;
        }
        else if(Format[i] == '\\') Skip = true;
        else if(Format[i] == 'Y') Return += tfp::IntToString(1900 + ltm->tm_year, 4);
        else if(Format[i] == 'M') Return += tfp::IntToString(1 + ltm->tm_mon, 2);
        else if(Format[i] == 'D') Return += tfp::IntToString(ltm->tm_mday, 2);
        else if(Format[i] == 'h') Return += tfp::IntToString(0 + ltm->tm_hour, 2);
        else if(Format[i] == 'm') Return += tfp::IntToString(1 + ltm->tm_min, 2);
        else if(Format[i] == 's') Return += tfp::IntToString(1 + ltm->tm_sec, 2);
        else Return += Format[i];
    }
    return Return;
}
