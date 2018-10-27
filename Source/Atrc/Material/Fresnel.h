#pragma once

#include <Atrc/Core/Core.h>

// �ⲿ��ʵ�ֲο���PBRT-3rd

AGZ_NS_BEG(Atrc)

// ��Ե��Fresnel�����
float ComputeFresnelDielectric(float etaI, float etaT, float cosThetaT);

// ����Fresnel�����
Spectrum ComputeFresnelConductor(const Spectrum &etaI, const Spectrum &etaT, const Spectrum &k, float cosThetaI);

// Schlick��ʽ
float ComputeSchlickApproximation(float etaI, float etaT, float cosThetaI);

class Fresnel
{
public:

    virtual ~Fresnel() = default;

    virtual Spectrum Eval(float cosThetaI) const = 0;
};

class FresnelConductor : public Fresnel
{
    Spectrum etaI, etaT, k;

public:

    FresnelConductor(const Spectrum &etaI, const Spectrum &etaT, const Spectrum &k);

    Spectrum Eval(float cosThetaI) const override;
};

class Dielectric : public Fresnel
{
protected:

    float etaI, etaT;

public:

    Dielectric(float etaI, float etaT) : etaI(etaI), etaT(etaT) { }

    float GetEtaI() const { return etaI; }

    float GetEtaT() const { return etaT; }
};

class FresnelDielectric : public Dielectric
{
public:

    FresnelDielectric(float etaI, float etaT);

    Spectrum Eval(float cosThetaI) const override;
};

class SchlickApproximation : public Dielectric
{
public:

    SchlickApproximation(float etaI, float etaT);

    Spectrum Eval(float cosThetaI) const override;
};

AGZ_NS_END(Atrc)
