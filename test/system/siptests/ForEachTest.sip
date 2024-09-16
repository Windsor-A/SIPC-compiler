main(){
  var a, b, c, d;
  b = 0;
  c = [1,2,3,4];
  for(a : c){
    b = b + a;
  }
  if(b != 10) error b;
  d = [];
  for(a : d){
    error a;
  }
  return 0;
}