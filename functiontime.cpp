#include "includes.hpp"
#include "globalobjects.hpp"


#ifdef TFP_DEBUG
void tfp::FunctionTimeClass::CreateFunctionTimer(std::string FunctionName)
{
    TimeList.resize(TimeList.size() + 1);
    unsigned TmpIndex = TimeList.size() - 1;
    TimeList[TmpIndex].Name = FunctionName;
    TimeList[TmpIndex].Time.restart();
    TimeList[TmpIndex].ShortestTime = std::numeric_limits<int64_t>::max();
    TimeList[TmpIndex].LongestTime = 0;
}

void tfp::FunctionTimeClass::StartFunctionTimer(std::string FunctionName)
{
    for(unsigned i = 0; i < TimeList.size(); i++)
    {
        if(TimeList[i].Name == FunctionName)
        {
            TimeList[i].Time.restart();
            return;
        }
    }
    CreateFunctionTimer(FunctionName);
    // StartFunctionTimer(FunctionName);
}

void tfp::FunctionTimeClass::StopFunctionTimer(std::string FunctionName)
{
    for(unsigned i = 0; i < TimeList.size(); i++)
    {
        if(TimeList[i].Name == FunctionName)
        {
            float MeasuredTime = TimeList[i].Time.getElapsedTime().asMicroseconds();
            if(MeasuredTime > TimeList[i].LongestTime)
                TimeList[i].LongestTime = MeasuredTime;
            if(MeasuredTime < TimeList[i].ShortestTime)
                TimeList[i].ShortestTime = MeasuredTime;
            break;
        }
    }
}

void tfp::FunctionTimeClass::PrintFunctionTimes()
{
    Debug.Command("---[ Function Times ]---");
    for(unsigned i = 0; i < TimeList.size(); i++)
    {
        Debug.Command("\tFunction name: " + TimeList[i].Name);
        Debug.Command("\tFunction shortest time: " + tfp::Int64ToString(TimeList[i].ShortestTime) + " microseconds");
        Debug.Command("\tFunction longest time: " + tfp::Int64ToString(TimeList[i].LongestTime) + + " microseconds");
        Debug.Command("");
    }
    Debug.Command("------------------------");
}

void tfp::FunctionTimeClass::ResetFunctionTimes()
{
    for(unsigned i = 0; i < TimeList.size(); i++)
    {
        TimeList[i].Time.restart();
        TimeList[i].ShortestTime = std::numeric_limits<int64_t>::max();
        TimeList[i].LongestTime = 0;
    }
}


#elif defined(TFP_RELEASE)
void tfp::FunctionTimeClass::CreateFunctionTimer(std::string FunctionName)
{

}

void tfp::FunctionTimeClass::StartFunctionTimer(std::string FunctionName)
{

}

void tfp::FunctionTimeClass::StopFunctionTimer(std::string FunctionName)
{

}

void tfp::FunctionTimeClass::PrintFunctionTimes()
{
    Debug.Command("FunctionTimes: Counting time is disabled in release mode");
}

void tfp::FunctionTimeClass::ResetFunctionTimes()
{
    Debug.Command("FunctionTimes: Counting time is disabled in release mode");
}


#else
    #error Missing TFP_DEBUG or TFP_RELEASE
#endif // TFP_DEBUG
