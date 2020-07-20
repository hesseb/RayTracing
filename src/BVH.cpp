#include "BVH.h"

BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>>& objects, size_t start, size_t end, double time0, double time1)
{
    int axis = randomInt(0, 2);

    auto compareFunction = (axis == 0) ? boxXCompare
                         : (axis == 1) ? boxYCompare
                                       : boxZCompare;

    size_t objectSpan = end - start;

    if (objectSpan == 1)
    {
        m_Left = objects[start];
        m_Right = objects[start];
    }
    else if (objectSpan == 2)
    {
        if (compareFunction(objects[start], objects[start+1]))
        {
            m_Left = objects[start];
            m_Right = objects[start+1];
        }
        else
        {
            m_Left = objects[start+1];
            m_Right = objects[start];
        }
    }
    else
    {
        std::sort(objects.begin() + start, objects.begin() + end, compareFunction);

        size_t mid = start + objectSpan / 2;
        m_Left = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
        m_Right = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB boxLeft, boxRight;

    if (    !m_Left->boundingBox(time0, time1, boxLeft)
        ||  !m_Right->boundingBox(time0, time1, boxRight))
    {
        std::cerr << "No bounding box in BVHNode constructor.\n";
    }

    m_Box = surroundingBox(boxLeft, boxRight);    
}

bool BVHNode::boundingBox(double t0, double t1, AABB& outputBox) const
{
    outputBox = m_Box;
    return true;
}

bool BVHNode::hit(const Ray& r, double tMin, double tMax, HitRecord& record) const
{
    if (!m_Box.hit(r, tMin, tMax)) return false;

    bool hitLeft = m_Left->hit(r, tMin, tMax, record);
    bool hitRight = m_Right->hit(r, tMin, hitLeft ? record.t : tMax, record);

    return hitLeft || hitRight;
}

inline bool boxCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b, int axis)
{
    AABB boxA, boxB;

    if (!a->boundingBox(0, 0, boxA) || !b->boundingBox(0, 0, boxB))
    {
        std::cerr << "No bounding box in BVHNode constructor.\n";
    }

    return boxA.min()[axis] < boxB.min()[axis];
}

inline bool boxXCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
    return boxCompare(a, b, 0);
}

inline bool boxYCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
    return boxCompare(a, b, 1);
}

inline bool boxZCompare(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
    return boxCompare(a, b, 2);
}