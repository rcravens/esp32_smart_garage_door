#include "Console.h"

namespace rlc
{
    bool Console::_isVerbose = false;
    bool Console::_isInfo = false;
    bool Console::_isError = true;

    void Console::setVerbose(bool isOn)
    {
        Console::_isVerbose = isOn;
    }

    void Console::setInfo(bool isOn)
    {
        Console::_isInfo = isOn;
    }

    void Console::setError(bool isOn)
    {
        Console::_isError = isOn;
    }

    void Console::Verbose(const char *msg)
    {
        if (Console::_isVerbose)
        {
            Serial.println(msg);
        }
    }

    void Console::Verbose(const String &msg)
    {
        if (Console::_isVerbose)
        {
            Serial.println(msg);
        }
    }

    void Console::Info(const char *msg)
    {
        if (Console::_isInfo)
        {
            Serial.println(msg);
        }
    }

    void Console::Info(const String &msg)
    {
        if (Console::_isInfo)
        {
            Serial.println(msg);
        }
    }

    void Console::Error(const char *msg)
    {
        if (Console::_isError)
        {
            Serial.println("ERROR: " + String(msg));
        }
    }

    void Console::Error(const String &msg)
    {
        if (Console::_isError)
        {
            Serial.println("ERROR: " + msg);
        }
    }
}