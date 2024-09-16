main(){
  var a,b,c,d,e,f;
  a = true;
  b = false;
  c = a and b;
  if(c) error 1;
  d = c or a;
  if(not d) error 2;
  e = (d or c) and (a or b);
  if(not e) error 3;
  f = not e;
  if(f) error 4;
  return 0;
}