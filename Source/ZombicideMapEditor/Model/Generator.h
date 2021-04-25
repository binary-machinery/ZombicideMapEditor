#pragma once
#include <memory>

#include "MapData/Map.h"

namespace Model
{
    class FGenerator : FNoncopyable
    {
    public:
        void SetMap(const std::shared_ptr<FMap> Value);
        void Generate();
    
    private:
        std::shared_ptr<FMap> Map = nullptr;
    };
}
