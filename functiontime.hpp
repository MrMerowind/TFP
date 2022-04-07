#ifndef FUNCTIONTIME_HPP_INCLUDED
#define FUNCTIONTIME_HPP_INCLUDED

namespace tfp
{
    class FunctionTimeClass
    {
    private:
        struct FunctionNode
        {
            std::string Name;
            sf::Clock Time;
            int64_t ShortestTime;
            int64_t LongestTime;
        };
        std::vector<tfp::FunctionTimeClass::FunctionNode> TimeList;
        void CreateFunctionTimer(std::string FunctionName);
    public:
        void StartFunctionTimer(std::string FunctionName);
        void StopFunctionTimer(std::string FunctionName);
        void PrintFunctionTimes();
        void ResetFunctionTimes();
    };
}


#endif // FUNCTIONTIME_HPP_INCLUDED
