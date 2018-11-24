#pragma once

#include "../Common.h"

AGZ_NS_BEG(ObjMgr)

using LightCreator = ObjectCreator<Atrc::Light>;
using LightManager = ObjectManager<Atrc::Light>;

// posX = filename
// posY = filename
// posZ = filename
// negX = filename
// negY = filename
// negZ = filename
class CubeEnvironmentLightCreator : public LightCreator, public AGZ::Singleton<CubeEnvironmentLightCreator>
{
public:

    Str8 GetName() const override { return "CubeEnvironmentLight"; }

    Atrc::Light *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// direction = Vec3
// radiance = Spectrum
class DirectionalLightCreator : public LightCreator, public AGZ::Singleton<DirectionalLightCreator>
{
public:

    Str8 GetName() const override { return "DirectionalLight"; }

    Atrc::Light *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// top    = Spectrum
// bottom = Spectrum
class SkyLightCreator : public LightCreator, public AGZ::Singleton<SkyLightCreator>
{
public:

    Str8 GetName() const override { return "SkyLight"; }

    Atrc::Light *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// tex = filename
class SphereEnvironmentLightCreator : public LightCreator, public AGZ::Singleton<SphereEnvironmentLightCreator>
{
public:

    Str8 GetName() const override { return "SphereEnvironmentLight"; }

    Atrc::Light *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

AGZ_NS_END(ObjMgr)
