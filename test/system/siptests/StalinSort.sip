
stalinsort(arr){
  var count,out,lasthighest,i;
  lasthighest = 0;
  count = 0;
  for(i : 0 .. #arr){
    if(arr[i] >= arr[lasthighest]){
      lasthighest = i;
      count++;
    }
  }
  out = [count of 0];
  count = 0;
  lasthighest = 0;
  for(i : 0 .. #arr){
    if(arr[i] >= arr[lasthighest]){
      lasthighest = i;
      out[count] = arr[i];
      count++;
    }
  }
  return out;
}

main(){
  var a,b;
  a = [55, 45, 68, 52, 50, 22, 69, 10, 94, 11];
  b = stalinsort(a);
  if(#b != 4) error #b;
  if(b[0] != 55) error b[0];
  if(b[1] != 68) error b[1];
  if(b[2] != 69) error b[2];
  if(b[3] != 94) error b[3];
  return 0;
}