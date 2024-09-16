main(){
  var a,b,c,d;
  a = 3;
  b = 4;
  c = [1,2,a,b];
  if((c[0] + c[1] + c[2]) != 6) error (c[0] + c[1] + c[2]);
  d = [];
  if(#d != 0) error #d;
  return 0;
}