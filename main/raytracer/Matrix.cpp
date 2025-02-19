#include "Matrix.h"

namespace zrt
{

XMMATRIX XM_CALLCONV ViewTransform(FXMVECTOR from, FXMVECTOR to, FXMVECTOR up)
{
    return XMMatrixIdentity();
}

} // namespace zrt