#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
        const Eigen::RowVector3d &query,
        const std::shared_ptr<AABBTree> &root,
        const double min_sqrd,
        const double max_sqrd,
        double &sqrd,
        std::shared_ptr<Object> &descendant) {
    ////////////////////////////////////////////////////////////////////////////

    auto cmp = [](std::pair<double, std::shared_ptr<AABBTree>> left,
                  std::pair<double, std::shared_ptr<AABBTree>> right) { return (left.first) > (right.first); };


    std::priority_queue<std::pair<double, std::shared_ptr<AABBTree>>, std::vector<std::pair<double, std::shared_ptr<AABBTree>>>, decltype(cmp)> q(
            cmp);

    sqrd = std::numeric_limits<double>::infinity();
    q.emplace(std::make_pair(point_box_squared_distance(query, root->box), root));


    std::shared_ptr<Object> temp_descendant;
    double temp_sqrd;

    auto &aabb_ptr = *root;

    while (!q.empty()) {

        double distance = q.top().first;
        std::shared_ptr<AABBTree> curr = q.top().second;
        q.pop();

        if (distance < sqrd && distance >= min_sqrd && distance <= max_sqrd) {
            if (curr->left) {
                auto &left_node = *(curr->left);

                if (typeid(left_node) != typeid(aabb_ptr)) {
                    if (curr->left->point_squared_distance(query, min_sqrd, max_sqrd, temp_sqrd, temp_descendant) &&
                        temp_sqrd < sqrd) {
                        sqrd = temp_sqrd;
                        descendant = curr->left;
                    }
                } else {
                    q.emplace(std::make_pair(point_box_squared_distance(query, curr->left->box),
                                             std::static_pointer_cast<AABBTree>(curr->left)));
                }
            }

            if (curr->right) {
                auto &right_node = *(curr->right);
                if (typeid(right_node) != typeid(aabb_ptr)) {
                    if (curr->right->point_squared_distance(query, min_sqrd, max_sqrd, temp_sqrd,
                                                            temp_descendant) && temp_sqrd < sqrd) {
                        sqrd = temp_sqrd;
                        descendant = curr->right;
                    }
                } else {
                    q.emplace(std::make_pair(point_box_squared_distance(query, curr->right->box),
                                             std::static_pointer_cast<AABBTree>(curr->right)));
                }
            }
        }

    }

    return sqrd < std::numeric_limits<double>::infinity();



    ////////////////////////////////////////////////////////////////////////////
}
