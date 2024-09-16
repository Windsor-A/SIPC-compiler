main(){
  var a,b,c,d;
  a = 1;
  b = 2;
  c = 3;
  d = 4;
  if(a < b){
    a = 3;
  }
  else{
    error a;
  }
  if(a <= c){
    c = c + 1;
  }
  else{
    error a;
  }
  if(c >= d){
    d = a + b;
  }
  else{
    error d;
  }
  return d;
}