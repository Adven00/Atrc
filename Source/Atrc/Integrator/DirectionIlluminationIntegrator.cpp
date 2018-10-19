#include <Atrc/Integrator/DirectIlluminationIntegrator.h>

AGZ_NS_BEG(Atrc)

Spectrum DirectIlluminationIntegrator::IlluminationBetween(
    const Scene &scene, const Light &light, const SurfacePoint &sp, const ShadingPoint &shd) const
{
    // TODO
    return Spectrum();
}

DirectIlluminationIntegrator::DirectIlluminationIntegrator(const Spectrum &background)
    : background_(background)
{

}

Spectrum DirectIlluminationIntegrator::GetRadiance(const Scene &scene, const Ray &r) const
{
    Spectrum ret = SPECTRUM::BLACK;

    SurfacePoint inct;
    if(!scene.FindCloestIntersection(r, &inct))
    {
        // ��Щû��ʵ��Ĺ�Դ
        for(auto light : scene.GetLights())
            ret += light->Le(r);
        return ret;
    }

    // ȡ�ñ������

    auto mat = inct.entity->GetMaterial(inct);
    mat->ComputeShadingLocal(&inct);
    
    ShadingPoint shdPnt;
    mat->Shade(inct, &shdPnt);

    // �Է���

    auto selfLight = inct.entity->AsLight();
    if(selfLight)
        ret += selfLight->AreaLe(inct);

    // MIS����Դֱ�Ӳ��� & BSDF����

    auto [light, lightPDF] = scene.SampleLight();
    if(light)
        ret += IlluminationBetween(scene, *light, inct, shdPnt) / lightPDF;

    return ret;
}

AGZ_NS_END(Atrc)
