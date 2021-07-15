  // 2017311729 민욱
  // calculator.c
  
  #include <stdio.h>
  #include<stdlib.h>

  typedef int bool;
  #define true 1
  #define false 0
  #define lld long long int
  #define BITSIZE 64
  typedef struct Division{
    lld quotient;
    lld remainer;
  }Division;

  bool iEqual(lld a, lld b);              // Determines whether two numbers are equal.
  bool isNotEqual(lld a, lld b);          // Determines whether two numbers are not equal.
  bool isNegative(lld a);                 // Determines whether number is negative
  bool isGreaterThan(lld a, lld b);       // check if a is greater than b
  bool isSmallerThan(lld a, lld b);       // check if a is smaller than b
  bool checkSign(lld a, lld b);           // Determines whether sign of two numbers are equal.
  lld toPositive(lld a);                  // Change number to positive value
  lld iPlusOne(lld a);                    // Return Increased number
  lld* digitArray(int a);                 // Return DigitArray
  lld leftShift(lld a);                   // shifting bits to the left
  lld rightShift(lld a);                  // shifting bits to the right
  lld Add(lld a, lld b);                  // Adding without built in operator
  lld subtract(lld a, lld b);             // Subtracting without built in operator
  lld multiply(lld a, lld b);             // MultiPlying without buit in operator
  lld divisionWithPositive(lld a, lld b); // Dividing recursive logic
  Division divide(lld a, lld b);          // Divide without built in operator


  bool iEqual(lld a, lld b){
    if(a==b) return true;
    else return false;
  };
  bool isNotEqual(lld a,lld b){
    return iEqual(iEqual(a, b), false);
  };
  bool isNegative(lld a){
    lld sign = 0x80000000;
    if(sign&a){
      return true;
    }
    return false;
  }
  bool isGreaterThan(lld a, lld b){
    if(isNegative(subtract(a,b))){
      return false;
    }
    return true;
  }
  bool isSmallerThan(lld a, lld b){
    if(isNegative(subtract(a,b))){
      return true;
    }
    return false;
  }
  bool checkSign(lld a, lld b){
    if(iEqual(isNegative(a),isNegative(b))){  // 부호 같은경우, 곱한값이 양수인경우
      return true;
    }
    return false;
  }
  lld toPositive(lld a){
    if(isNegative(a)){
      return iPlusOne(~a);
    }
    return a;
  }
  lld iPlusOne(lld a){
    return ++a;
  };
  lld iSubOne(lld a){
    return subtract(a,1);
  };
  lld* digitArray(int a){
    int i=1;
    lld top=0;
    lld bottom=1;
    static lld digit_Array[BITSIZE] = {0, }; // 64비트 
    digit_Array[0] = 1;
    while(isNotEqual(i,BITSIZE)){
      top = top^bottom;
      bottom = iPlusOne(top);
      digit_Array[i] = bottom;
      i = iPlusOne(i);
    }
    return digit_Array;
  }
  lld leftShift(lld a){
    lld* digit_array = digitArray(BITSIZE);
    int i=0;
    lld result = 0;
    while(isNotEqual(i,BITSIZE)){
      int increased = iPlusOne(i);
      if(digit_array[i]&a){
        result |= digit_array[increased];
      }
      i = iPlusOne(i);
    }
    return result;
  }
  lld rightShift(lld a){
    lld* digit_array = digitArray(BITSIZE);
    int i=iSubOne(BITSIZE);
    lld result = 0;
    while(isNotEqual(i,0)){
      int decreased = iSubOne(i);
      if(digit_array[i]&a){
        result |= digit_array[decreased];
      }
      i = iSubOne(i);
    }
    return result;
  }
  lld Add(lld a, lld b){
    if(iEqual(b, 0)){
      return a;
    }
    else if(iEqual(a,0)){
      return b;
    }
    int sum = a^b;
    int carry = leftShift((a&b));
    return Add(sum,carry);
  }
  lld subtract(lld a, lld b){
    lld comp_b = iPlusOne(~b);
    return Add(a, comp_b);
  }
  lld multiply(lld a, lld b){
    lld sign = 0x80000000;
    if(checkSign(a,b)){ // 부호 같은경우
      sign = 0;
    }
    lld result = 0;
    a = toPositive(a);
    b = toPositive(b);
    int i = 0;
    lld* digit_array = digitArray(BITSIZE);
    while(isNotEqual(i,BITSIZE)){
      int increased = iPlusOne(i);
      if(digit_array[i]&b){
        int j = 0;
        lld shifted = a;
        while(isNotEqual(j,i)){
          shifted = leftShift(shifted);
          j = iPlusOne(j);
        }
        result = Add(result,shifted);
      }
      i = iPlusOne(i);
    }
  if(sign){
    result = iPlusOne(~result);
    return result;
  }
  return result;
  }
  lld divisionWithPositive(lld a, lld b){
    if(isSmallerThan(a,b)){
      return 0;
    }
    return 1 + divisionWithPositive(subtract(a,b),b);
  }
  Division divide(lld a, lld b){
    struct Division division;
    division.quotient = 0;
    division.remainer = 0;
    if(iEqual(a,0)){
      division.remainer = b;
      return division;
    }
    if(iEqual(b,0)){
      division.remainer = -1;
      return division;
    }
    if(iEqual(a,b)){
      division.quotient = 1;
      return division;
    }
    lld sign = 0x80000000;
    if(checkSign(a,b)){ // 부호 같은경우
      sign = 0;
    }
    lld result = 0;
    lld _a;
    lld _b;
    _a = toPositive(a);
    _b = toPositive(b);
    lld quotient = divisionWithPositive(_a,_b);
    division.quotient = quotient;
  if(sign){
    quotient = iPlusOne(~quotient);
    division.quotient = quotient;
  }
  lld remainer = subtract(a,multiply(quotient,b));
  division.remainer = remainer;
  return division;
  }
  void getInput(lld* left, lld* right, char* operator){
    printf("Calculator without operator\n");
      printf("Put Your Left Operand\n");
      scanf("%lld",left);
      fflush(stdin);
      printf("Put Your Right Operand\n");
      scanf("%lld",right);
      fflush(stdin);
      printf("Put Your Operator\n");
      scanf(" %c",operator);
      fflush(stdin);
  }

  int main(void){
    lld left;
    lld right;
    char operator;
    while(true) {
      getInput(&left, &right, &operator);
      if(iEqual(operator,'+')){
        printf("%lld + %lld = %lld\n", left, right, Add(left,right));
      }
      else if(iEqual(operator,'-')){
        printf("%lld - %lld = %lld\n", left, right, subtract(left,right));
      }
      else if(iEqual(operator,'*')){
        printf("%lld * %lld = %lld\n", left, right, multiply(left,right));
      }
      else if(iEqual(operator,'/')){
        Division d = divide(left,right);
        if(iEqual(d.remainer,-1)){
          printf("Can't Divide With Zero");
        }
        printf("%lld / %lld\n", left, right);
        printf("quotient: %lld\n", d.quotient);
        printf("remainer: %lld\n", d.remainer);
      }
      else{
        printf("Not a Proper operator");
      }
      printf("\n\n");
    }

}
