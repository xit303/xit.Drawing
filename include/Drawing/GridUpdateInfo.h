#pragma once
#include <cstddef>

namespace xit::Drawing
{
    struct GridUpdateInfo
    {
    public:
        size_t NumberOfCells = 0;
        bool UpdateFixed = false;
        bool UpdateAuto = false;
        bool UpdateStar = false;

        bool NeedUpdate();

        void SetAll(bool value);

        void UpdateAutoStar();
    };
}
