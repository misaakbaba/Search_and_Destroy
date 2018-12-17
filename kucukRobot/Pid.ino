// qtr dan gelen verilere göre hangi pozisyonda olduğunu gösteren dataset
int prob[][lim]={{0,1,1,1,1,1,1,1,2000},{1,1,1,1,1,1,1,0,5000}
    ,{0,0,1,1,1,1,1,1,2500},{1,0,0,1,1,1,1,1,2833}
    ,{1,1,0,0,1,1,1,1,3166},{1,1,1,0,0,1,1,1,3500}
    ,{1,1,1,1,0,0,1,1,3833}
    ,{1,1,1,1,1,0,0,1,4166},{1,1,1,1,1,1,0,0,4500}};



int compareArrays(int * arr){ // qtr dan okunan değerleri prob arrayi ile karşılaştırıp pozisyonu buluyor
  int result;
    for(int i=0;i<8;i++){
      if(qtrVal[i]!=arr[i]){
        result=0;
        break;
      }else{
        result=arr[8];
      }
      
    }
    return result;
 }

 void computePos(){ // qtr i okuyup compute pos a gönderiyor
  readQtr();
  for(int i=0;i<9;i++){   
    if(compareArrays(prob[i])!=0){
      pos=compareArrays(prob[i]);
    }
  }
 }
