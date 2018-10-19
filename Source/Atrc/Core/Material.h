#pragma once

#include <Atrc/Core/Common.h>
#include <Atrc/Core/SurfacePoint.h>

AGZ_NS_BEG(Atrc)

class Material
{
public:

    virtual ~Material() = default;

    // ����sp����shdLocal������ʵ����bump mapping�ȼ���������һ����հ�geoLocal
    virtual void ComputeShadingLocal(SurfacePoint *sp) const;

    virtual void Shade(const SurfacePoint &sp, ShadingPoint *dst) const = 0;
};

AGZ_NS_END(Atrc)
