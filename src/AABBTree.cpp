#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
        const std::vector<std::shared_ptr<Object> > &objects,
        int a_depth) :
        depth(std::move(a_depth)),
        num_leaves(objects.size()) {
    ////////////////////////////////////////////////////////////////////////////

    for (int i = 0; i < objects.size(); i++)
        insert_box_into_box(objects[i]->box, this->box);

    int longest_axis = -1;
    double longest_distance;

    for (int i = 0; i < 3; i++) {
        double dis = this->box.max_corner(0) - this->box.min_corner(0);
        if (dis > longest_distance || longest_axis < 0) {
            longest_axis = i;
            longest_distance = dis;
        }
    }

    double mid_point = this->box.center()(longest_axis);

    std::vector<std::shared_ptr<Object>> leftObjects;
    std::vector<std::shared_ptr<Object>> rightObjects;


    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->box.center()(longest_axis) >=  mid_point)
            leftObjects.push_back(objects[i]);
        else
            rightObjects.push_back(objects[i]);
    }

    left = leftObjects.size() > 0 ? NULL: std::make_shared<AABBTree>(leftObjects, depth+1);
    right = leftObjects.size() > 0 ? NULL: std::make_shared<AABBTree>(rightObjects, depth+1);




    ////////////////////////////////////////////////////////////////////////////
}

bool AABBTree::ray_intersect(
        const Ray &ray,
        const double min_t,
        const double max_t,
        double &t,
        std::shared_ptr<Object> &descendant) const {
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:












    return false;
    ////////////////////////////////////////////////////////////////////////////
}
