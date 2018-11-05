#pragma once

#include <Atrc/Core/Medium.h>

AGZ_NS_BEG(Atrc)

class HomogeneousMedium : public Medium
{
	// ����
	Spectrum sigmaA_;

	// ɢ��
	Spectrum sigmaS_;

	// ˥���� = sigmaA_ + sigmaS_��
	Spectrum sigmaT_;

	// �Է���
	Spectrum le_;

	// ���Գ�ϵ��
	Real g_;

public:

	HomogeneousMedium(const Spectrum &sigmaA, const Spectrum &sigmaS, const Spectrum &le, Real g);

	Spectrum Tr(const Vec3 &a, const Vec3 &b) const override;

	Either<MediumSampleLsResult, Real> SampleLs(const Ray &r) const override;

	void Shade(const MediumPoint &medPnt, MediumShadingPoint *shdPnt, AGZ::ObjArena<> &arena) const override;
};

AGZ_NS_END(Atrc)
