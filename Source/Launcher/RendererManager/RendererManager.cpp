#include "RendererManager.h"

Atrc::Renderer *ParallelRendererCreator::Create(const ConfigGroup &params, ObjArena<> &arena) const
{
    auto workerCount = params["workerCount"].AsValue().Parse<int32_t>();
    return arena.Create<Atrc::ParallelRenderer>(workerCount);
}

Atrc::Renderer *SerialRendererCreator::Create(const ConfigGroup &params, ObjArena<> &arena) const
{
    return arena.Create<Atrc::SerialRenderer>();
}

Atrc::SubareaRenderer *JitteredSubareaRendererCreator::Create(const ConfigGroup &params, ObjArena<> &arena) const
{
    auto spp = params["spp"].AsValue().Parse<uint32_t>();
    if(spp < 1)
        throw std::runtime_error("JitteredSubareaRendererCreator: invalid spp");
    return arena.Create<Atrc::JitteredSubareaRenderer>(spp);
}
