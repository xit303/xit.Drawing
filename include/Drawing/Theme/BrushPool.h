#pragma once

#include <unordered_map>
#include <memory>
#include <Drawing/Brushes/SolidColorBrush.h>

namespace xit::Drawing
{
    class BrushPool
    {
    private:
        static std::unordered_map<uint32_t, SolidColorBrush*>& GetSolidColorBrushesMap();
        
    public:
        static SolidColorBrush* GetSolidColorBrush(uint32_t color);
        static void Clear();
        static size_t GetPoolSize();
    };
}
