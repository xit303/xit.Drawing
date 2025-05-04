#include <Drawing/GridUpdateInfo.h>

namespace xit::Drawing
{
    bool GridUpdateInfo::NeedUpdate()
    {
        return UpdateFixed || UpdateAuto || UpdateStar || (NumberOfCells == 0);
    }

    void GridUpdateInfo::SetAll(bool value)
    {
        UpdateFixed = value;
        UpdateAuto = value;
        UpdateStar = value;
    }

    void GridUpdateInfo::UpdateAutoStar()
    {
        UpdateAuto = true;
        UpdateStar = true;
    }
}