#include <list> 

typedef std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> two_trees;

void find_all_intersecting_pairs_using_BoundingBoxTrees(
  const std::shared_ptr<BoundingBoxTree> & rootA,
  const std::shared_ptr<BoundingBoxTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  std::list<two_trees> q;
  two_trees curr_trees;
  std::shared_ptr<Object> tree_A, tree_B;
 
  if (box_box_intersect(rootA->box, rootB->box)){
    q.push_back(std::make_pair(rootA, rootB));
  }

  while (!q.empty()){
    curr_trees = q.front();
    q.pop_front();

    tree_A = std::get<0>(curr_trees);
    tree_B = std::get<1>(curr_trees);
    
    // Check if both roots are leafs:
    std::shared_ptr<BoundingBoxTree> bbt_A = std::dynamic_pointer_cast<BoundingBoxTree>(tree_A);
    std::shared_ptr<BoundingBoxTree> bbt_B = std::dynamic_pointer_cast<BoundingBoxTree>(tree_B);

    if (!bbt_A && !bbt_B){
      leaf_pairs.push_back(make_pair(tree_A, tree_B));
    } else if (!bbt_A){
      if (bbt_B->left != NULL){
        if (box_box_intersect(tree_A->box, bbt_B->left->box)){
          q.push_back(std::make_pair(tree_A, bbt_B->left));
        }
      }
      if (bbt_B->right != NULL){
        if (box_box_intersect(tree_A->box, bbt_B->right->box)){
          q.push_back(std::make_pair(tree_A, bbt_B->right));
        }
      }
    } else if (!bbt_B){
      if (bbt_A->left != NULL){
        if (box_box_intersect(bbt_A->left->box, tree_B->box)){
          q.push_back(std::make_pair(bbt_A->left, tree_B));
        }
      }
      if (bbt_A->right != NULL){
        if (box_box_intersect(bbt_A->right->box, tree_B->box)){
          q.push_back(std::make_pair(bbt_A->right, tree_B));
        }
      } 
    } else {
      if (bbt_A->left != NULL && bbt_B->left != NULL){
        if (box_box_intersect(bbt_A->left->box, bbt_B->left->box)){
          q.push_back(std::make_pair(bbt_A->left, bbt_B->left));
        }
      }
      if (bbt_A->left != NULL && bbt_B->right != NULL){
        if (box_box_intersect(bbt_A->left->box, bbt_B->right->box)){
          q.push_back(std::make_pair(bbt_A->left, bbt_B->right));
        }
      }
      if (bbt_A->right != NULL && bbt_B->right != NULL){
        if (box_box_intersect(bbt_A->right->box, bbt_B->right->box)){
          q.push_back(std::make_pair(bbt_A->right, bbt_B->right));
        }
      }
      if (bbt_A->right != NULL && bbt_B->left != NULL){
        if (box_box_intersect(bbt_A->right->box, bbt_B->left->box)){
          q.push_back(std::make_pair(bbt_A->right, bbt_B->left));
        }
      }
    }
  }
}
