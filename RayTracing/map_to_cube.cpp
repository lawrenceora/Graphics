void map_to_cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  V = Eigen::MatrixXd::Zero(8,3);
  F = Eigen::MatrixXi::Zero(6,4);
  UV = Eigen::MatrixXd::Zero(14,2);
  UF = Eigen::MatrixXi::Zero(6,4);
  NV = Eigen::MatrixXd::Zero(6,3);
  NF = Eigen::MatrixXi::Zero(6,4);

  V <<  1, 0, 0,
        1, 0, 1,
        1, 1, 0,
        1, 1, 1,
        0, 0, 0,
        0, 0, 1,
        0, 1, 0,
        0, 1, 1;

  UV <<       1, 0, 2, 0,
        0, 1, 1, 1, 2, 1, 3, 1, 4, 1,
        0, 2, 1, 2, 2, 2, 3, 2, 4, 2,
              1, 3, 2, 3;

  UV = UV / 4;

  NV <<  0, 0, 1,
         0, 0,-1,
         0, 1, 0,
         0,-1, 0,
         1, 0, 0,
        -1, 0, 0;

  F << 0, 4, 5, 1,
       0, 4, 6, 2,
       0, 1, 5, 2,
       1, 5, 7, 3,
       4, 6, 7, 5,
       2, 3, 7, 6;

  UF << 3, 0,  1,  6,
        3, 2,  7,  7,
        3, 4, 9,  8,
        4, 5, 10, 9,
        6,11, 10,  5,
        8,9, 13, 12;

  NF << 3, 3, 3, 3,
        1, 1, 1, 1,
        4, 4, 4, 4,
        0, 0, 0, 0,
        5, 5, 5, 5,
        2, 2, 2, 2;
}
