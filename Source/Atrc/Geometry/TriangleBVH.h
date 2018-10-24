#pragma once

#include <Atrc/Core/Core.h>

AGZ_NS_BEG(Atrc)

// TriangleBVH�����д��������ݣ������ݴ洢�ֳ���������instancing
class TriangleBVHCore
{
public:

    struct Vertex
    {
        Vec3 pos;
        Vec3 nor;
        Vec2 uv;
    };

    struct Node
    {
        bool isLeaf;
        union
        {
            struct
            {
                const AABB *bound;
                uint32_t rightChild;
            } internal;

            struct
            {
                uint32_t start;
                uint32_t end;
            } leaf;
        };
    };

    struct InternalTriangle
    {
        Vec3 A, B_A, C_A;
        Vec3 nA, nB_nA, nC_nA;
        Vec2 tA, tB_tA, tC_tA;
        Real surfaceArea;
    };

    TriangleBVHCore(const Vertex *vertices, uint32_t triangleCount);

    bool HasIntersection(const Ray &r) const;

    bool EvalIntersection(const Ray &r, SurfacePoint *sp) const;

    AABB LocalBound() const;

    Real SurfaceArea() const;

private:

    void InitBVH(const Vertex *vertices, uint32_t triangleCount);

    // ����Bound�õ�arena
    AGZ::SmallObjArena<AABB> boundArena_;

    // triangles_�������ǰ׺�ͣ��������ֲ����Խ���ȫ���������ϵ�������Ȳ���
    std::vector<Real> areaPrefixSum_;

    std::vector<InternalTriangle> triangles_;
    std::vector<Node> nodes_;
};

class TriangleBVH : public Geometry
{
public:

    bool HasIntersection(const Ray &r) const;

    bool FindIntersection(const Ray &r, SurfacePoint *sp) const override;

    Real SurfaceArea() const override;

    AABB LocalBound() const override;

    GeometrySampleResult Sample() const override;

    Real SamplePDF(const Vec3 &pos) const override;

    GeometrySampleResult Sample(const Vec3 &dst) const;

    Real SamplePDF(const Vec3 &pos, const Vec3 &dst) const;
};

AGZ_NS_END(Atrc)
