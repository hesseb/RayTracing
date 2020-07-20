#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "Hittable.h"
#include "AABB.h"

#include <memory>
#include <vector>

class HittableList: public Hittable
{
public:
    HittableList() = default;
    HittableList(std::shared_ptr<Hittable> object) { add(object); }

    void clear() { m_Objects.clear(); }
    void add(std::shared_ptr<Hittable> object) { m_Objects.push_back(object); }

    virtual bool hit(const Ray& r, double tMin, double tMax, HitRecord& record) const;
    virtual bool boundingBox(double t0, double t1, AABB& outputBox) const override;

    std::vector<std::shared_ptr<Hittable>>& objects() { return m_Objects; }

private:
    std::vector<std::shared_ptr<Hittable>> m_Objects;
};

#endif