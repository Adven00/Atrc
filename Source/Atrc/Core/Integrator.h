#pragma once

#include <Atrc/Core/Common.h>
#include <Atrc/Core/Ray.h>
#include <Atrc/Core/Scene.h>

AGZ_NS_BEG(Atrc)

class Integrator
{
public:

    virtual ~Integrator() = default;

    // ������-r.dir�������r.ori��radiance
    virtual Spectrum GetRadiance(const Scene &scene, const Ray &r) const = 0;
};

AGZ_NS_END(Atrc)
