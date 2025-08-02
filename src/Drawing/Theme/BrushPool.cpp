#include <Drawing/Theme/BrushPool.h>

namespace xit::Drawing
{
    // Use Meyer's singleton pattern to avoid static destruction order issues
    std::unordered_map<uint32_t, SolidColorBrush *> &BrushPool::GetSolidColorBrushesMap()
    {
        static std::unordered_map<uint32_t, SolidColorBrush *> solidColorBrushes;
        return solidColorBrushes;
    }

    SolidColorBrush *BrushPool::GetSolidColorBrush(uint32_t color)
    {
        auto it = GetSolidColorBrushesMap().find(color);
        if (it != GetSolidColorBrushesMap().end())
        {
            return it->second;
        }

        auto brush = new SolidColorBrush(color);
        GetSolidColorBrushesMap()[color] = brush;
        return brush;
    }

    void BrushPool::Clear()
    {
        for (const auto &pair : GetSolidColorBrushesMap())
        {
            delete pair.second;
        }
        GetSolidColorBrushesMap().clear();
    }

    size_t BrushPool::GetPoolSize()
    {
        return GetSolidColorBrushesMap().size();
    }
}
