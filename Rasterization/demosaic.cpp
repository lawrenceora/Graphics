void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      int curr = 3*(i*width + j);
      int up = (i-1)*width + j;
      int mid = i*width + j;
      int down = (i+1)*width + j;
      bool red = (i % 2 == 1 && j % 2 == 0);
      bool blue = (i % 2 == 0 && j % 2 == 1);
      bool green = !(red || blue);
      bool top = i == 0;
      bool left = j == 0;
      bool right = j == (width - 1);
      bool bottom = i == (height - 1);

      //Decide the red value
      if (red){
        rgb[curr] = bayer[mid];
      } else if (top && green){
        rgb[curr] = bayer[down];
      } else if (right && green && j % 2 == 1){
        rgb[curr] = bayer[mid - 1];
      } else if (bottom && green && i % 2 == 0){
        rgb[curr] = bayer[up];
      } else if (top && right){ //and blue
        rgb[curr] = bayer[down - 1];
      } else if (bottom && right && blue){
        rgb[curr] = bayer[up - 1];
      } else if (right){ //and blue
        rgb[curr] = (bayer[down - 1] + bayer[up - 1]) / 2;
      } else if (top){ //and blue
        rgb[curr] = (bayer[down - 1] + bayer[down + 1]) / 2;
      } else if (bottom && blue){
        rgb[curr] = (bayer[up - 1] + bayer[up + 1]) / 2;
      } else if (green && i % 2 == 0){
        rgb[curr] = (bayer[up] + bayer[down]) / 2;
      } else if (green){ // odd row green
        rgb[curr] = (bayer[mid - 1] + bayer[mid + 1]) / 2;
      } else { // blue
        rgb[curr] = (bayer[up + 1] + bayer[up - 1] + bayer[down - 1] + bayer[down + 1]) / 4;
      }

      curr++;

      //Decide the green value
      if (green){
        rgb[curr] = bayer[mid];
      } else if (left && bottom){
        rgb[curr] = (bayer[up] + bayer[mid + 1]) / 2;
      } else if (bottom && right){
        rgb[curr] = (bayer[up] + bayer[mid - 1]) / 2;
      } else if (top && right){
        rgb[curr] = (bayer[mid - 1] + bayer[down]) / 2;
      } else if (top){
        rgb[curr] = (bayer[mid - 1] + bayer[mid + 1] + bayer[down]) / 3;
      } else if (left){
        rgb[curr] = (bayer[mid + 1] + bayer[up] + bayer[down]) / 3;
      } else if (bottom){
        rgb[curr] = (bayer[mid + 1] + bayer[up] + bayer[mid - 1]) / 3;
      } else if (right){
        rgb[curr] = (bayer[mid - 1] + bayer[up] + bayer[down]) / 3;
      } else {
        rgb[curr] = (bayer[mid - 1] + bayer[mid + 1] + bayer[up] + bayer[down]) / 4;
      }

      curr++;

      //Decide the blue value
      if (blue){
        rgb[curr] = bayer[mid];
      } else if (green && left){
        rgb[curr] = bayer[mid + 1];
      } else if (bottom && green && i % 2 == 1){
        rgb[curr] = bayer[up];
      } else if (right && green && j % 2 == 0){
        rgb[curr] = bayer[mid - 1];
      } else if (bottom && left){ //and red
        rgb[curr] = bayer[up + 1];
      } else if (bottom && right && red){
        rgb[curr] = bayer[up - 1];
      } else if (bottom){ //and red
        rgb[curr] = (bayer[up - 1] + bayer[up + 1]) / 2;
      } else if (left){
        rgb[curr] = (bayer[up + 1] + bayer[down + 1]) / 2;
      } else if (left && red){
        rgb[curr] = (bayer[up - 1] + bayer[down - 1]) / 2;
      } else if (green && j % 2 == 0){
        rgb[curr] = (bayer[mid - 1] + bayer[mid + 1]) / 2;
      } else if (green){ // odd row
        rgb[curr] = (bayer[up] + bayer[down]) / 2;
      } else { //red
        rgb[curr] = (bayer[up + 1] + bayer[up - 1] + bayer[down - 1] + bayer[down + 1]) / 4;
      }
    }
  }
}
