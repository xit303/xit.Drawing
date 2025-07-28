#include <Drawing/Theme/BrushPool.h>

namespace xit::Drawing
{
    std::unordered_map<uint32_t, SolidColorBrush*> BrushPool::solidColorBrushes;
    
    SolidColorBrush* BrushPool::GetSolidColorBrush(uint32_t color)
    {
        auto it = solidColorBrushes.find(color);
        if (it != solidColorBrushes.end()) {
            return it->second;
        }
        
        auto brush = new SolidColorBrush(color);
        solidColorBrushes[color] = brush;
        return brush;
    }
    
    void BrushPool::Clear()
    {
        for (auto& pair : solidColorBrushes) {
            delete pair.second;
        }
        solidColorBrushes.clear();
    }
    
    size_t BrushPool::GetPoolSize()
    {
        return solidColorBrushes.size();
    }
}
