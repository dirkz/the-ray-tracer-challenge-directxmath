#include "Matrix.h"

namespace zrt
{

XMMATRIX XM_CALLCONV ViewTransform(FXMVECTOR from, FXMVECTOR to, FXMVECTOR up)
{
    XMVECTOR forward = XMVector4Normalize(XMVectorSubtract(to, from));
    XMVECTOR backward = XMVectorScale(forward, -1);
    XMVECTOR upn = XMVector4Normalize(up);
    XMVECTOR left = XMVector3Cross(forward, upn);
    XMVECTOR trueUp = XMVector3Cross(left, forward);

    XMVECTOR lastRow = XMVECTOR{0, 0, 0, 1};
    XMMATRIX orientation = XMMATRIX{left, trueUp, backward, lastRow};

    XMFLOAT4 fromF;
    XMStoreFloat4(&fromF, XMVectorScale(from, -1));
    XMMATRIX translation = Translation(fromF.x, fromF.y, fromF.z);

    XMMATRIX transform = XMMatrixMultiply(translation, orientation);

    return transform;
}

} // namespace zrt