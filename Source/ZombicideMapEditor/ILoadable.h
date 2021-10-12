#pragma once

class ILoadable
{
public:
    virtual ~ILoadable()
    {
    }

    virtual void Load() = 0;
};
