main(){
  var a,b;
  a = [3,4,5,6];
  b = a;
  b[2] = 7;
  if(a[2] != 7) error a[2];
  return 0;
}