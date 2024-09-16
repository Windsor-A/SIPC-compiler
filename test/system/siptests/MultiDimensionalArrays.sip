make2dArray(x,y,val){
  var a;
  a = [x of [y of val]];
  return a;
}

sum2(var1){
  var sum,i,j;
  sum = 0;
  for(i : 0 .. #var1){
    for(j : 0 .. #var1[i]){
      sum = sum + var1[i][j];
    }
  }
  return sum;
}

make3dArray(x,y,z,val){
  var a;
  a = [x of [y of [z of val]]];
  return a;
}

sum3(var1){
  var sum,i,j,k;
  sum = 0;
  for(i : 0 .. #var1){
    for(j : 0 .. #var1[i]){
      for(k : 0 .. #var1[i][j]){
        sum = sum + var1[i][j][k];
      }
    }
  }
  return sum;
}

make4dArray(w,x,y,z,val){
  var a;
  a = [w of [x of [y of [z of val]]]];
  return a;
}

sum4(var1){
  var sum,i,j,k,l;
  sum = 0;
  for(i : 0 .. #var1){
    for(j : 0 .. #var1[i]){
      for(k : 0 .. #var1[i][j]){
        for(l : 0 .. #var1[i][j][k]){
          sum = sum + var1[i][j][k][l];
        }
      }
    }
  }
  return sum;
}


main(){
  var arr1, arr2, arr3;
  arr1 = make2dArray(7,8,9);
  arr2 = make3dArray(3,4,5,6);
  arr3 = make4dArray(2,3,4,5,6);
  if(sum2(arr1) != 504) error sum2(arr1);
  if(sum3(arr2) != 360) error sum3(arr2);
  if(sum4(arr3) != 720) error sum4(arr3);
  return 0;
}