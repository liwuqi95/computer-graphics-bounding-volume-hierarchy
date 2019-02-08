#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list>


void find_all_intersecting_pairs_using_AABBTrees(
        const std::shared_ptr<AABBTree> &rootA,
        const std::shared_ptr<AABBTree> &rootB,
        std::vector<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> > > &
        leaf_pairs) {
    ////////////////////////////////////////////////////////////////////////////

    std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>>> q;

    if (box_box_intersect(rootA->box, rootB->box))
        q.emplace_back(std::make_pair(rootA, rootB));

    auto &aabb_ptr = *rootA;

    while (!q.empty()) {

        auto node_A = q.front().first;
        auto node_B = q.front().second;

        q.pop_front();

        auto &A_node = *(node_A);
        auto &B_node = *(node_B);

        bool A_is_leaf = typeid(A_node) != typeid(aabb_ptr);
        bool B_is_leaf = typeid(B_node) != typeid(aabb_ptr);


        if (A_is_leaf && B_is_leaf) {
            leaf_pairs.emplace_back(std::make_pair(node_A, node_B));
        } else if (A_is_leaf) {

            std::shared_ptr<AABBTree> tree_B = std::static_pointer_cast<AABBTree>(node_B);

            if (tree_B->left && box_box_intersect(node_A->box, tree_B->left->box))
                q.emplace_back(std::make_pair(node_A, tree_B->left));

            if (tree_B->right && box_box_intersect(node_A->box, tree_B->right->box))
                q.emplace_back(std::make_pair(node_A, tree_B->right));

        } else if (B_is_leaf) {

            std::shared_ptr<AABBTree> tree_A = std::static_pointer_cast<AABBTree>(node_A);

            if (tree_A->left && box_box_intersect(node_B->box, tree_A->left->box))
                q.emplace_back(std::make_pair(tree_A->left, node_B));

            if (tree_A->right && box_box_intersect(node_B->box, tree_A->right->box))
                q.emplace_back(std::make_pair(tree_A->right, node_B));


        } else {
            std::shared_ptr<AABBTree> tree_A = std::static_pointer_cast<AABBTree>(node_A);
            std::shared_ptr<AABBTree> tree_B = std::static_pointer_cast<AABBTree>(node_B);

            if (tree_A->left && tree_B->left && box_box_intersect(tree_A->left->box, tree_B->left->box))
                q.emplace_back(std::make_pair(tree_A->left, tree_B->left));

            if (tree_A->left && tree_B->right && box_box_intersect(tree_A->left->box, tree_B->right->box))
                q.emplace_back(std::make_pair(tree_A->left, tree_B->right));

            if (tree_A->right && tree_B->left && box_box_intersect(tree_A->right->box, tree_B->left->box))
                q.emplace_back(std::make_pair(tree_A->right, tree_B->left));

            if (tree_A->right && tree_B->right && box_box_intersect(tree_A->right->box, tree_B->right->box))
                q.emplace_back(std::make_pair(tree_A->right, tree_B->right));

        }
    }



    ////////////////////////////////////////////////////////////////////////////
}
