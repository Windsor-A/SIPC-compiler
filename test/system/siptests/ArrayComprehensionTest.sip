main(){
  var a,b,c;
  a = 3;
  b = 7;
  c = [a of b];
  if(c[0] != 7) error (c[0]);
  if(c[1] != 7) error (c[1]);
  if(c[2] != 7) error c[2];
  if(#c != 3) error #c;
  return 0;
}