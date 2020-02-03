void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  
  for (int i = 0; i < height*width; i++){
    double alpha = A[4*i + 3] / 255.0;
    C[4*i] = alpha*A[4*i] + (1.0 - alpha)*B[4*i];
    C[4*i + 1] = alpha*A[4*i + 1] + (1.0 - alpha)*B[4*i + 1];
    C[4*i + 2] = alpha*A[4*i + 2] + (1.0 - alpha)*B[4*i + 2];
    C[4*i + 3] = 1;
  }
}
