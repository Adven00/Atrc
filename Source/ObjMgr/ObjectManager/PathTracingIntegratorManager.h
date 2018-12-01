#pragma once

#include "../Common.h"

AGZ_NS_BEG(ObjMgr)

using PathTracingIntegratorCreator = ObjectCreator<Atrc::PathTracingIntegrator>;
using PathTracingIntegratorManager = ObjectManager<Atrc::PathTracingIntegrator>;

// background = Spectrum
// entity     = Spectrum
class PureColorIntegratorCreator : public PathTracingIntegratorCreator, public AGZ::Singleton<PureColorIntegratorCreator>
{
public:

    Str8 GetName() const override { return "PureColorIntegrator"; }

    Atrc::PathTracingIntegrator *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// maxDepth = uint32_t
class PathTracerCreator : public PathTracingIntegratorCreator, public AGZ::Singleton<PathTracerCreator>
{
public:

    Str8 GetName() const override { return "PathTracer"; }

    Atrc::PathTracingIntegrator *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// maxDepth = uint32_t
class VolumetricPathTracerCreator : public PathTracingIntegratorCreator, public AGZ::Singleton<VolumetricPathTracerCreator>
{
public:

    Str8 GetName() const override { return "VolumetricPathTracer"; }

    Atrc::PathTracingIntegrator *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// maxOccuT = Real
// background = Spectrum
// object = Spectrum
class AmbientOcclusionIntegratorCreator : public PathTracingIntegratorCreator, public AGZ::Singleton<AmbientOcclusionIntegratorCreator>
{
public:

    Str8 GetName() const override { return "AmbientOcclusionIntegrator"; }

    Atrc::PathTracingIntegrator *Create(const ConfigGroup &params, ObjArena<> &arena) const override;
};

// SHEntityProjector��SHLightProjector��������;��Integrator�����Ǽ���Ĳ���radiance����SH coefficients
// û�дӽű��ļ��������ǵ����ɣ��������ﲻΪ֮׼��Creator

AGZ_NS_END(ObjMgr)
