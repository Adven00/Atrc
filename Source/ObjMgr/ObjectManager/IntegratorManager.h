#pragma once

#include "../Common.h"

AGZ_NS_BEG(ObjMgr)

using IntegratorCreator = ObjectCreator<Atrc::Integrator>;
using IntegratorManager = ObjectManager<Atrc::Integrator>;

// background = Spectrum
// entity     = Spectrum
class PureColorIntegratorCreator : public IntegratorCreator, public AGZ::Singleton<PureColorIntegratorCreator>
{
public:

    Str8 GetName() const override { return "PureColorIntegrator"; }

    Atrc::Integrator *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// maxDepth = uint32_t
class PathTracerCreator : public IntegratorCreator, public AGZ::Singleton<PathTracerCreator>
{
public:

    Str8 GetName() const override { return "PathTracer"; }

    Atrc::Integrator *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// maxDepth = uint32_t
class VolumetricPathTracerCreator : public IntegratorCreator, public AGZ::Singleton<VolumetricPathTracerCreator>
{
public:

    Str8 GetName() const override { return "VolumetricPathTracer"; }

    Atrc::Integrator *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// maxOccuT = Real
// background = Spectrum
// object = Spectrum
class AmbientOcclusionIntegratorCreator : public IntegratorCreator, public AGZ::Singleton<AmbientOcclusionIntegratorCreator>
{
public:

    Str8 GetName() const override { return "AmbientOcclusionIntegrator"; }

    Atrc::Integrator *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// SHEntityProjector��SHLightProjector��������;��Integrator�����Ǽ���Ĳ���radiance����SH coefficients
// û�дӽű��ļ��������ǵ����ɣ��������ﲻΪ֮׼��Creator

AGZ_NS_END(ObjMgr)
