#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <iostream>
#include <string.h>
#include <libconfig.h++>

class Configuration
{
    public:
        Configuration(const std::string& file);
        virtual ~Configuration();

        template <class T>   T       get(const char* path)
        {
             T value;
            _config.lookupValue(path, value);
            return value;
        }

        template <class T>   void    set(const char* path, T& value)
        {
            libconfig::Setting& setting = _config.lookup(path);
            setting = value;
        }

    private:

        std::string         _filename;
        libconfig::Config   _config;


};

#endif // CONFIGURATION_H
