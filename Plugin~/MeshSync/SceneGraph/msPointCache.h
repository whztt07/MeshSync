#pragma once
#include "msIdentifier.h"
#include "msEntity.h"

namespace ms {

// Points
struct PointsDataFlags
{
    uint32_t unchanged : 1;
    uint32_t topology_unchanged : 1;
    uint32_t has_points : 1;
    uint32_t has_rotations : 1;
    uint32_t has_scales : 1;
    uint32_t has_colors : 1;
    uint32_t has_velocities : 1;
    uint32_t has_ids : 1;

    PointsDataFlags()
    {
        *(uint32_t*)this = 0;
    }
};

class Points : public Transform
{
using super = Transform;
public:
    // on Points, Transform::reference refers Mesh object for source mesh

    // serializable
    PointsDataFlags pd_flags;
    SharedVector<float3> points;
    SharedVector<quatf>  rotations;
    SharedVector<float3> scales;
    SharedVector<float4> colors;
    SharedVector<float3> velocities;
    SharedVector<int>    ids;

    // non-serializable
    Bounds bounds{};

protected:
    Points();
    ~Points() override;
public:
    msDefinePool(Points);
    Type getType() const override;
    bool isGeometry() const override;

    void serialize(std::ostream& os) const override;
    void deserialize(std::istream& is) override;
    bool isUnchanged() const override;
    bool isTopologyUnchanged() const override;

    void clear() override;
    uint64_t hash() const override;
    uint64_t checksumGeom() const override;
    bool lerp(const Entity& src1, const Entity& src2, float t) override;
    EntityPtr clone(bool detach = false) override;

    void updateBounds();
    void setupPointsDataFlags();
};
msSerializable(Points);
msDeclPtr(Points);

} // namespace ms
