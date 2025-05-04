#pragma once

namespace xit::Drawing
{
    enum class TextWrapping
    {
        //
        // Summary:
        //     Line-breaking occurs if the line overflows beyond the available block width.
        //     However, a line may overflow beyond the block width if the line breaking algorithm
        //     cannot determine a line break opportunity, as in the case of a very long word
        //     constrained in a fixed-width container with no scrolling allowed.
        WrapWithOverflow,
        //
        // Summary:
        //     No line wrapping is performed.
        NoWrap,
        //
        // Summary:
        //     Line-breaking occurs if the line overflows beyond the available block width,
        //     even if the standard line breaking algorithm cannot determine any line break
        //     opportunity, as in the case of a very long word constrained in a fixed-width
        //     container with no scrolling allowed.
        Wrap
    };
}
using namespace xit::Drawing;
