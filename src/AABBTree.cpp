#include "AABBTree.h"
#include "insert_box_into_box.h"

#include <iostream>

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
        double dis = this->box.max_corner(i) - this->box.min_corner(i);
        if (longest_axis < 0 || dis > longest_distance) {
            longest_axis = i;
            longest_distance = dis;
        }
    }

    double mid_point = this->box.center()(longest_axis);

    std::vector<std::shared_ptr<Object>> leftObjects;
    std::vector<std::shared_ptr<Object>> rightObjects;

    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->box.center()(longest_axis) >= mid_point)
            leftObjects.push_back(objects[i]);
        else
            rightObjects.push_back(objects[i]);
    }

    if (leftObjects.empty() || rightObjects.empty()) {

        if (leftObjects.empty()) {
            leftObjects.push_back(rightObjects.back());
            rightObjects.pop_back();
        } else if (rightObjects.empty()) {
            rightObjects.push_back(leftObjects.back());
            leftObjects.pop_back();
        }
    }

    this->left = leftObjects.empty() ? NULL : (leftObjects.size() == 1 ? leftObjects[0] : std::make_shared<AABBTree>(
            leftObjects, this->depth + 1));
    this->right = rightObjects.empty() ? NULL : (rightObjects.size() == 1 ? rightObjects[0]
                                                                          : std::make_shared<AABBTree>(
                    rightObjects, this->depth + 1));

    ////////////////////////////////////////////////////////////////////////////
}

bool AABBTree::ray_intersect(
        const Ray &ray,
        const double min_t,
        const double max_t,
        double &t,
        std::shared_ptr<Object> &descendant) const {
    ////////////////////////////////////////////////////////////////////////////

    bool result = false;

    if (ray_intersect_box(ray, this->box, min_t, max_t)) {

        double temp_t;
        std::shared_ptr<Object> temp_descendant;


        if (this->left && this->left->ray_intersect(ray, min_t, max_t, temp_t, temp_descendant)) {
            t = temp_t;
            descendant = temp_descendant ? temp_descendant : this->left;
            result = true;
            temp_descendant = NULL;
        }


        if (this->right && this->right->ray_intersect(ray, min_t, max_t, temp_t, temp_descendant) &&
            (!result || t >= temp_t)) {
            t = temp_t;
            descendant = temp_descendant ? temp_descendant : this->right;
            result = true;
        }

    }

    return result;
    ////////////////////////////////////////////////////////////////////////////
}
