#include "items.h"

namespace Tmpl8
{
    Item::Item(int x, int y, int frame, bool hidden)
        : x(x), y(y), frame(frame), pickedUp(false), used(false), hidden(hidden)
    {
    }

} // namespace Tmpl8