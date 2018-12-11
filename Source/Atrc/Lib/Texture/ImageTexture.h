#pragma once

#include <Utils/Texture.h>

#include <Atrc/Lib/Core/Texture.h>

AGZ_NS_BEG(Atrc)

class ImageTexture : public Texture
{
    using TexCoordWrapper = Real(*)(Real);
    using Sampler = Spectrum(*)(const AGZ::Texture2D<Color3b>&, const Vec2&);

    const AGZ::Texture2D<Color3b> &tex_;

    TexCoordWrapper texCoordWrapper_;
    Sampler sampler_;

public:

    enum SampleStrategy
    {
        Nearest,
        Linear,
    };

    enum WrapStrategy
    {
        Clamp,
    };

    ImageTexture(
        const AGZ::Texture2D<Color3b> &tex,
        SampleStrategy sampleStrategy, WrapStrategy wrapStrategy) noexcept;

    Spectrum Sample(const Vec2 &uv) const noexcept override;
};

AGZ_NS_END(Atrc)
