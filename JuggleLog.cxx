#include "JuggleLog.h"

#include <iostream>

void JuggleLog::PrintInternal(Severity sev, const std::string& str)
{
    (void)sev;
    std::cerr << str << std::endl;    
}
