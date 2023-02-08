﻿#ifndef SERVICEINJECTOR_H
#define SERVICEINJECTOR_H

#include <application/service/UserService.h>
#include <infrastructure/injection/dependencyinjector.h>

using namespace QInjection;

class ServiceInjector
{
public:
    static UserService* userService()
    {
        return new UserService();
    }

    static void init()
    {
        QInjection::addSingleton(userService);
    }
};

#endif  // SERVICEINJECTOR_H
