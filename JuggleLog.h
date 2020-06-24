/**
 * @class JuggleLog
 * @brief The class that  exports errors or warnings.
*/

#ifndef JUGGLELOG_H
#define JUGGLELOG_H

#include <sstream>
#include <string>

class JuggleLog
{
public:
    enum class Severity : unsigned char
    {
      Info,
      Warning,
      Error
    };
    
    template<typename... Args>
    static void Print(Severity sev, Args... args)
    {
      std::stringstream ss;
      AppendArg(ss, args...);
      PrintInternal(sev, ss.str());
    }
    
protected:
    static void AppendArg(std::stringstream&) {}
        
    template<typename T, typename... Args>
    static void AppendArg(std::stringstream& ss, T value, Args... args)
    {
      ss << value;
      AppendArg(ss, args...);
    }
    
    static void PrintInternal(Severity sev, const std::string& msg);
};

#endif // JUGGLELOG_H
