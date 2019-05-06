int binary_to_gray(int b) {
  return b^(b>>1);
}

int gray_to_binary(int g) {
  int b=0;
  for(;g;g>>=1) b^=g;
  return b;
}
