#ifndef BVH_H
#define BVH_H

#include "Core.h"
#include "Hittable.h"
#include "HittableList.h"
#include "AABB.h"
#include "Vec3.h"

#include <algorithm>

class BVHNode : public Hittable
{
public:
    BVHNode() = default;

    BVHNode(HittableList& list, double time0, double time1)
        : BVHNode(list.objects(), 0, list.objects().size(), time0, time1)
    {}

    BVHNode(std::vector<std::shared_ptr<Hittable>>& objects,
    size_t start, size_t end, double time0, double time1);

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const override;
    virtual bool boundingBox(double t0, double t1,  AABB& outputBox) const override;

private:
    std::shared_ptr<Hittable> m_Left;
    std::shared_ptr<Hittable> m_Right;
    AABB m_Box;
};

inline bool boxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis);

inline bool boxXCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
inline bool boxYCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
inline bool boxZCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);

#endif