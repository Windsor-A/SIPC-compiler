main(){
  var a, b, c;
  b = 0;
  c = 1;
  for(a : 0 .. 3){
    b = b + a;
  }
  if(b != 3) error b;
  for(a : 1 .. 6 by 2){
    c = c * a;
  }
  if(c != 15) error c;
  return 0;
}