#include <queue> // std::priority_queue/:
#include <utility> //std::pair

typedef std::pair<double, std::shared_ptr<Object>> tup;

bool point_BoundingBoxTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<BoundingBoxTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  bool hit = false;
  double curr_d, l_d, r_d;
  double min_d = std::numeric_limits<double>::infinity();
  double root_d = point_box_squared_distance(query, root->box);
  std::shared_ptr<Object> curr_obj, closest_obj;
  tup top_tup;

  std::priority_queue<tup, std::vector<tup>, std::greater<tup>> q;
  q.push(std::make_pair(root_d, root));

  while (!q.empty()){
    top_tup = q.top();
    q.pop();
    curr_d = std::get<0>(top_tup);
    curr_obj = std::get<1>(top_tup);
    if (curr_d < min_d){
      // Check if obj is a leaf
      std::shared_ptr<BoundingBoxTree> bbt = std::dynamic_pointer_cast<BoundingBoxTree>(curr_obj);
      if (!bbt){
        if (min_sqrd <= curr_d && curr_d <= max_sqrd){
          hit = true;
          min_d = curr_d;
          closest_obj = curr_obj;
        }
      } else {
        if (bbt->left != NULL){
          l_d = point_box_squared_distance(query, bbt->left->box);
          q.push(std::make_pair(l_d, bbt->left));
        }
        if (bbt->right != NULL){
          r_d = point_box_squared_distance(query, bbt->right->box);
          q.push(std::make_pair(r_d, bbt->right));
        }
      }
    }
  }

  sqrd = min_d;
  descendant = closest_obj;
  return hit;
}
