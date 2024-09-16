main(){
  var a,b,c,d;
  a = 13;
  b = 42;
  c = a < b ? a : b;
  if(c != 13) error c;
  d = -b;
  if(d != -42) error d;
  return 0;
}