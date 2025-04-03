#pragma once

#include <Arduino.h>

namespace rlc
{
    class Console
    {
    public:
        static void setVerbose(bool isOn);
        static void setInfo(bool isOn);
        static void setError(bool isOn);
        static void Verbose(const char *msg);
        static void Verbose(const String &msg);
        static void Info(const char *msg);
        static void Info(const String &msg);
        static void Error(const char *err);
        static void Error(const String &err);

    private:
        static bool _isInfo;
        static bool _isVerbose;
        static bool _isError;
    };
}
