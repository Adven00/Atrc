#pragma once

#include <Atrc/Core/Core.h>

// �ⲿ��ʵ�ֲο���PBRT-3rd

AGZ_NS_BEG(Atrc)

// ��Ե��Fresnel�����
float FresnelDielectric(float etaI, float etaT, float cosThetaT);

// ����Fresnel�����
Spectrum FresnelConductor(const Spectrum &etaI, const Spectrum &etaT, const Spectrum &k, float cosThetaI);

AGZ_NS_END(Atrc)
