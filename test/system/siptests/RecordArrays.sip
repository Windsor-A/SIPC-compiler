main(){
  var a,b,c,d;
  a = {p: 7, q:2};
  c = {p: 4, q:3};
  b = [3 of a];
  if(b[0].p - b[2].q != 5) error b[0].p - b[2].q;
  d = [a,c];
  if(d[0].q + d[1].q != 5) error d[0].q + d[1].q;
  return 0;
}