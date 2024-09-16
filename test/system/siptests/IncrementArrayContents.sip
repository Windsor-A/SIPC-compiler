main(){
  var a;
  a = [1,2,3];
  a[0]++;
  a[1]++;
  a[2]--;
  if(a[0] != 2) error a[0];
  if(a[1] != 3) error a[1];
  if(a[2] != 2) error a[2];
  return 0;
}