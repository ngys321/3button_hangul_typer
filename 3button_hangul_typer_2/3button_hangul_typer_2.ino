
#include "LedControl.h" // 라이브러리 사용 선언
// Din 핀을 12번, ClK핀을 11번 CS핀을 10번에 연결, 매트릭스는 4개를 사용 선언
LedControl lc=LedControl(12,11,10,4);
int Mnum = 4; // 매드릭스 갯수
long consonant=0;
long vowel=0;
long bottomConsonant=0;
byte blank[8]=
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
byte upperchar[8]=
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};
byte lowerchar[8]=
{
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000
};


void setup() {
  // put your setup code here, to run once:
  
  pinMode(7, INPUT_PULLUP);//7번핀-위쪽화살표
  pinMode(6, INPUT_PULLUP);//6번핀-아랫쪽화살표
  pinMode(5, INPUT_PULLUP);//5번핀-엔터
  
 for(int c = Mnum; c>=0; c--) // 매트릭스 3번부터 0번까지 세팅
  {
   lc.shutdown(c,false); // 0~3번까지 매트릭스 절전모드 해제
   lc.setIntensity(c,0); // 매트릭스의 밝기 선언 0~15의 수
   lc.clearDisplay(c); // 매트릭스 led를 초기화
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  START:
  for(int i=(Mnum-1); i>=0; i--)
  {
    if(1==matrix(i,0))
    {
      consonant=0;
      vowel=0;
      bottomConsonant=0;
      for(int c = Mnum; c>=0; c--) // 매트릭스 3번부터 0번까지 세팅
      {
       lc.clearDisplay(c); // 매트릭스 led를 초기화
      }
      goto START;
    }
  }
   

  while(1)
  {
    if(digitalRead(7)==HIGH && digitalRead(6)==HIGH) //매트릭스4개 모두 다 만든후에, 위쪽 아랫쪽 화살표 동시에 누르면 화면초기화됨.
    {
      for(int c = Mnum; c>=0; c--) // 매트릭스 3번부터 0번까지 세팅
      {
       lc.clearDisplay(c); // 매트릭스 led를 초기화
      }
      break;
    }    
  }


}

/*
void reversableMatrix(int Mnum, int initState)
{
  int c;
  if(Mnum==-1)
  {
    return;
  }
  else
  {
    if((c = matrix(Mnum,initState))==0)
    {
      reversableMatrix(Mnum-1,0);
    }
    else
    {
      reversableMatrix(Mnum+1,2);
    }
  }
}
*/

int matrix(int Mposition, int initState)
{

  int state = initState; //상태 변수, 0:초성선택해야하는상태(ㄱ,ㄲ,ㄴ...), 1:중성선택해야하는상태(ㅏ,ㅑ,ㅓ...), 2:종성선택해야하는상태(ㄱ,ㄲ,ㄴ...)


///////////////////////////변수변경/////////////////////////
  while(1)
  {
    if(state==0)//상태변수==0:초성선택해야하는상태(ㄱ,ㄲ,ㄴ...) 일때
    {
      if(digitalRead(7)==HIGH && digitalRead(6)==HIGH) //위쪽 아랫쪽 화살표 동시에 누르면 화면초기화됨.
      {
        return 1;
      }
      if((digitalRead(7)==HIGH))//위쪽화살표 버튼 클릭했을때
      {
        if(consonant==18)//맨 뒤 초성(ㅎ)이면, 다시 맨 앞 초성(ㄱ)으로 돌아온다
        {
          delay(400);
          consonant=0;
        }
        else//일반적인 경우에는 그 다음 초성으로 바뀐다
        {
          delay(400);
          consonant++;
        }
      }
      if((digitalRead(6)==HIGH))//아랫쪽화살표 버튼 클릭했을때
      {
        if(consonant==0)//맨 앞 초성(ㄱ)이면, 맨 뒤 초성(ㅎ)으로 간다 
        {
          delay(400);
          consonant=18;
        }
        else//일반적인 경우에는 그 전의 초성으로 바뀐다
        {
          delay(400);
          consonant--;  
        }      
      }
      if((digitalRead(5)==HIGH))//
      {
        delay(400);
        state=1;
      }

    }
    if(state==1)//상태변수==1:중성선택해야하는상태(ㅏ,ㅑ,ㅓ...) 일때
    {
      if(digitalRead(7)==HIGH && digitalRead(6)==HIGH) //위쪽 아랫쪽 화살표 동시에 누르면 화면초기화됨.
      {
        return 1;
      }
      if((digitalRead(7)==HIGH))//위쪽화살표 버튼 클릭했을때
      {
        if(vowel==20)//맨 뒤 중성(ㅢ)이면, 다시 맨 앞 중성(ㅏ)으로 돌아온다
        {
          delay(400);
          vowel=0;
        }
        else//일반적인 경우에는 그 다음 중성으로 바뀐다
        {
          delay(400);
          vowel++;          
        }
      }
      if((digitalRead(6)==HIGH))//아랫쪽화살표 버튼 클릭했을때
      {
        if(vowel==0)//맨 앞 중성(ㅏ)이면, 맨 뒤 중성(ㅢ)으로 간다
        {
          delay(400);
          vowel=20; 
        }
        else//일반적인 경우에는 그 전의 중성으로 바뀐다
        {
          delay(400);
          vowel--;          
        }
      }
      if((digitalRead(5)==HIGH))//
      {
        delay(400);
        state=2;
      }

    }
    if(state==2)//상태변수==2:종성(받침)선택해야하는상태(ㄱ,ㄲ,ㄴ...)
    {
      if(digitalRead(7)==HIGH && digitalRead(6)==HIGH) //위쪽 아랫쪽 화살표 동시에 누르면 화면초기화됨.
      {
        return 1;
      }
      if((digitalRead(7)==HIGH))//위쪽화살표 버튼 클릭했을때
      {
        if(bottomConsonant==27)//맨 뒤 종성(ㅎ)이면, 다시 맨 앞 종성(받침없음)으로 돌아온다
        {
          delay(400);
          bottomConsonant=0;
        }
        else//일반적인 경우에는 그 다음 종성으로 바뀐다
        {
          delay(400);
          bottomConsonant++;          
        }
      }
      if((digitalRead(6)==HIGH))//아랫쪽화살표 버튼 클릭했을때
      {
        if(bottomConsonant==0)//맨 앞 종성(받침없음)이면, 맨 뒤 종성(ㅎ)으로 간다
        {
          delay(400);
          bottomConsonant=27;
        }
        else//일반적인 경우에는 그 전의 종성으로 바뀐다
        {
          delay(400);
          bottomConsonant--;          
        }
      }
      if((digitalRead(5)==HIGH))//
      {
        delay(400);
        consonant=0;
        vowel=0;
        bottomConsonant=0;
        return 0;
      }

    }

    //////////////////////글자출력//////////////////////////
    if(0==1)
    {
      //예외적으로 출력하고 싶은 글자들은 여기에 직접 추가로 도트작업하기
    }
    else
    {
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01000110;
          upperchar[2] = B01000100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11110100;
          upperchar[1] = B01010110;
          upperchar[2] = B01010100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B10000100;
          upperchar[1] = B10000110;
          upperchar[2] = B11000100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B10000110;
          upperchar[2] = B11000100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11110100;
          upperchar[1] = B10100110;
          upperchar[2] = B11110100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01000110;
          upperchar[2] = B10000100;
          upperchar[3] = B11000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B10100110;
          upperchar[2] = B11100100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B10100100;
          upperchar[1] = B11100110;
          upperchar[2] = B10100100;
          upperchar[3] = B11100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B10101010;
          upperchar[1] = B11111011;
          upperchar[2] = B10101010;
          upperchar[3] = B11111000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B10100110;
          upperchar[2] = B10100100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B01010010;
          upperchar[1] = B10101011;
          upperchar[2] = B10101010;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B01100100;
          upperchar[1] = B10010110;
          upperchar[2] = B10010100;
          upperchar[3] = B01100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B01000110;
          upperchar[2] = B10100100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11111010;
          upperchar[1] = B01010011;
          upperchar[2] = B10101010;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B11100110;
          upperchar[2] = B01000100;
          upperchar[3] = B10100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01000110;
          upperchar[2] = B11000100;
          upperchar[3] = B01000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B11100110;
          upperchar[2] = B10000100;
          upperchar[3] = B11100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B11111010;
          upperchar[1] = B01010011;
          upperchar[2] = B11111010;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==0))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B11100110;
          upperchar[2] = B00000100;
          upperchar[3] = B01000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01000110;
          upperchar[2] = B01000110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11110100;
          upperchar[1] = B01010110;
          upperchar[2] = B01010110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B10000100;
          upperchar[1] = B10000110;
          upperchar[2] = B11000110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B10000110;
          upperchar[2] = B11000110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11110100;
          upperchar[1] = B10100110;
          upperchar[2] = B11110110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01000110;
          upperchar[2] = B10000110;
          upperchar[3] = B11000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B10100110;
          upperchar[2] = B11100110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B10100100;
          upperchar[1] = B11100110;
          upperchar[2] = B10100110;
          upperchar[3] = B11100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B10101010;
          upperchar[1] = B11111011;
          upperchar[2] = B10101011;
          upperchar[3] = B11111010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B10100110;
          upperchar[2] = B10100110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B01010010;
          upperchar[1] = B10101011;
          upperchar[2] = B10101011;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B01100100;
          upperchar[1] = B10010110;
          upperchar[2] = B10010110;
          upperchar[3] = B01100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B01000110;
          upperchar[2] = B10100110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11111010;
          upperchar[1] = B01010011;
          upperchar[2] = B10101011;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B11100110;
          upperchar[2] = B01000110;
          upperchar[3] = B10100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01000110;
          upperchar[2] = B11000110;
          upperchar[3] = B01000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B11100110;
          upperchar[2] = B10000110;
          upperchar[3] = B11100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B11111010;
          upperchar[1] = B01010011;
          upperchar[2] = B11111011;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==1))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B11100110;
          upperchar[2] = B00000110;
          upperchar[3] = B01000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01001100;
          upperchar[2] = B01000100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11110010;
          upperchar[1] = B01010110;
          upperchar[2] = B01010010;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B10000100;
          upperchar[1] = B10001100;
          upperchar[2] = B11000100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B10001100;
          upperchar[2] = B11000100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11110010;
          upperchar[1] = B10100110;
          upperchar[2] = B11110010;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01001100;
          upperchar[2] = B10000100;
          upperchar[3] = B11000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B10101100;
          upperchar[2] = B11100100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B10100100;
          upperchar[1] = B11101100;
          upperchar[2] = B10100100;
          upperchar[3] = B11100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B10101001;
          upperchar[1] = B11111011;
          upperchar[2] = B10101001;
          upperchar[3] = B11111000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B10101100;
          upperchar[2] = B10100100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B01010001;
          upperchar[1] = B10101011;
          upperchar[2] = B10101001;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B01100010;
          upperchar[1] = B10010110;
          upperchar[2] = B10010010;
          upperchar[3] = B01100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B01001100;
          upperchar[2] = B10100100;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11111001;
          upperchar[1] = B01010011;
          upperchar[2] = B10101001;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B11101100;
          upperchar[2] = B01000100;
          upperchar[3] = B10100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01001100;
          upperchar[2] = B11000100;
          upperchar[3] = B01000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B11101100;
          upperchar[2] = B10000100;
          upperchar[3] = B11100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B11111001;
          upperchar[1] = B01010011;
          upperchar[2] = B11111001;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==2))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B11101100;
          upperchar[2] = B00000100;
          upperchar[3] = B01000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01001100;
          upperchar[2] = B01001100;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11110010;
          upperchar[1] = B01010110;
          upperchar[2] = B01010110;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B10000100;
          upperchar[1] = B10001100;
          upperchar[2] = B11001100;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B10001100;
          upperchar[2] = B11001100;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11110010;
          upperchar[1] = B10100110;
          upperchar[2] = B11110110;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01001100;
          upperchar[2] = B10001100;
          upperchar[3] = B11000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B10101100;
          upperchar[2] = B11101100;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B10100100;
          upperchar[1] = B11101100;
          upperchar[2] = B10101100;
          upperchar[3] = B11100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B10101001;
          upperchar[1] = B11111011;
          upperchar[2] = B10101011;
          upperchar[3] = B11111001;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B10101100;
          upperchar[2] = B10101100;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B01010001;
          upperchar[1] = B10101011;
          upperchar[2] = B10101011;
          upperchar[3] = B00000001;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B01100010;
          upperchar[1] = B10010110;
          upperchar[2] = B10010110;
          upperchar[3] = B01100010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B01001100;
          upperchar[2] = B10101100;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11111001;
          upperchar[1] = B01010011;
          upperchar[2] = B10101011;
          upperchar[3] = B00000001;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B11101100;
          upperchar[2] = B01001100;
          upperchar[3] = B10100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11000100;
          upperchar[1] = B01001100;
          upperchar[2] = B11001100;
          upperchar[3] = B01000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11100100;
          upperchar[1] = B11101100;
          upperchar[2] = B10001100;
          upperchar[3] = B11100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B11111001;
          upperchar[1] = B01010011;
          upperchar[2] = B11111011;
          upperchar[3] = B00000001;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==3))
      {
        case 1:
          upperchar[0] = B01000100;
          upperchar[1] = B11101100;
          upperchar[2] = B00001100;
          upperchar[3] = B01000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100100;
          upperchar[2] = B00101110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B01010010;
          upperchar[2] = B01010111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B10000000;
          upperchar[1] = B10000100;
          upperchar[2] = B11101110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B10000100;
          upperchar[2] = B11101110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B10100010;
          upperchar[2] = B11110111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11000000;
          upperchar[1] = B01000100;
          upperchar[2] = B10001110;
          upperchar[3] = B11000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B10100100;
          upperchar[2] = B11101110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B10100000;
          upperchar[1] = B11100100;
          upperchar[2] = B10101110;
          upperchar[3] = B11100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11010000;
          upperchar[1] = B11110010;
          upperchar[2] = B11010111;
          upperchar[3] = B11110000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B10100100;
          upperchar[2] = B10101110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B01010000;
          upperchar[1] = B10101000;
          upperchar[2] = B10101010;
          upperchar[3] = B00000111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B01100000;
          upperchar[1] = B10010000;
          upperchar[2] = B10010010;
          upperchar[3] = B01100111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B01000100;
          upperchar[2] = B10101110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11111000;
          upperchar[1] = B01010000;
          upperchar[2] = B10101010;
          upperchar[3] = B00000111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100100;
          upperchar[2] = B01001110;
          upperchar[3] = B10100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100100;
          upperchar[2] = B11101110;
          upperchar[3] = B00100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B11100100;
          upperchar[2] = B10001110;
          upperchar[3] = B11100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B11111000;
          upperchar[1] = B01010000;
          upperchar[2] = B11111010;
          upperchar[3] = B00000111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==4))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100100;
          upperchar[2] = B00001110;
          upperchar[3] = B01000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100110;
          upperchar[2] = B00101111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B01010110;
          upperchar[2] = B00001111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B10000000;
          upperchar[1] = B10000110;
          upperchar[2] = B11101111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B10000110;
          upperchar[2] = B11101111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B11000110;
          upperchar[2] = B11101111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11000000;
          upperchar[1] = B01000110;
          upperchar[2] = B10001111;
          upperchar[3] = B11000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B10100110;
          upperchar[2] = B11101111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B10100000;
          upperchar[1] = B11100110;
          upperchar[2] = B10101111;
          upperchar[3] = B11100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11010000;
          upperchar[1] = B11110000;
          upperchar[2] = B11010110;
          upperchar[3] = B11111111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B10100110;
          upperchar[2] = B00001111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B01010000;
          upperchar[1] = B10101000;
          upperchar[2] = B00000110;
          upperchar[3] = B00001111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B01100000;
          upperchar[1] = B10010000;
          upperchar[2] = B10010110;
          upperchar[3] = B01101111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B01000110;
          upperchar[2] = B10101111;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11111000;
          upperchar[1] = B01010000;
          upperchar[2] = B10100110;
          upperchar[3] = B00001111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100110;
          upperchar[2] = B01001111;
          upperchar[3] = B10100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100110;
          upperchar[2] = B11101111;
          upperchar[3] = B00100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B11100110;
          upperchar[2] = B10001111;
          upperchar[3] = B11100000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B01100000;
          upperchar[2] = B11110110;
          upperchar[3] = B00001111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==5))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100110;
          upperchar[2] = B00001111;
          upperchar[3] = B01000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100000;
          upperchar[2] = B00101110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B01010000;
          upperchar[2] = B00001110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B10000000;
          upperchar[1] = B11100000;
          upperchar[2] = B00001110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B10000000;
          upperchar[2] = B11101110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B10100111;
          upperchar[2] = B11110010;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11000000;
          upperchar[1] = B01000000;
          upperchar[2] = B10001110;
          upperchar[3] = B11000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B10100000;
          upperchar[2] = B11101110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B10100000;
          upperchar[1] = B11100000;
          upperchar[2] = B10101110;
          upperchar[3] = B11100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11010000;
          upperchar[1] = B11110000;
          upperchar[2] = B11010111;
          upperchar[3] = B11110010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B10100000;
          upperchar[2] = B10101110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B01010000;
          upperchar[1] = B10101000;
          upperchar[2] = B00000111;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B01100000;
          upperchar[1] = B10010000;
          upperchar[2] = B10010111;
          upperchar[3] = B01100010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B01000000;
          upperchar[2] = B10101110;
          upperchar[3] = B00000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11111000;
          upperchar[1] = B01010000;
          upperchar[2] = B10101111;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100000;
          upperchar[2] = B01001110;
          upperchar[3] = B10100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100000;
          upperchar[2] = B11101110;
          upperchar[3] = B00100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B11100000;
          upperchar[2] = B10001110;
          upperchar[3] = B11100100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B01100000;
          upperchar[2] = B11110111;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==6))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100000;
          upperchar[2] = B00001110;
          upperchar[3] = B01000100;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100000;
          upperchar[2] = B00101111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B01010000;
          upperchar[2] = B00001111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B10000000;
          upperchar[1] = B10000000;
          upperchar[2] = B11101111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B10000000;
          upperchar[2] = B11101111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B10101111;
          upperchar[2] = B11110110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11000000;
          upperchar[1] = B01000000;
          upperchar[2] = B10001111;
          upperchar[3] = B11000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B10100000;
          upperchar[2] = B11101111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B10100000;
          upperchar[1] = B11100000;
          upperchar[2] = B10101111;
          upperchar[3] = B11100110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11010000;
          upperchar[1] = B11110000;
          upperchar[2] = B11011111;
          upperchar[3] = B11110110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B10100000;
          upperchar[2] = B00001111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B01010000;
          upperchar[1] = B10101000;
          upperchar[2] = B00001111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B01100000;
          upperchar[1] = B10010000;
          upperchar[2] = B10011111;
          upperchar[3] = B01100110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B01000000;
          upperchar[2] = B10101111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11111000;
          upperchar[1] = B01010000;
          upperchar[2] = B10101111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100000;
          upperchar[2] = B01001111;
          upperchar[3] = B10100110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100000;
          upperchar[2] = B11101111;
          upperchar[3] = B00100110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B11100000;
          upperchar[2] = B10001111;
          upperchar[3] = B11100110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B01100000;
          upperchar[2] = B11111111;
          upperchar[3] = B00000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==7))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100000;
          upperchar[2] = B00001111;
          upperchar[3] = B01000110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00111000;
          upperchar[1] = B00001000;
          upperchar[2] = B01111110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00111100;
          upperchar[1] = B00010100;
          upperchar[2] = B01111110;
          upperchar[3] = B00000000;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00100000;
          upperchar[1] = B00111100;
          upperchar[2] = B00000000;
          upperchar[3] = B01111110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00111000;
          upperchar[1] = B00100000;
          upperchar[2] = B00111000;
          upperchar[3] = B01111110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00111100;
          upperchar[1] = B00101000;
          upperchar[2] = B00111100;
          upperchar[3] = B11111111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B11000000;
          upperchar[1] = B01000000;
          upperchar[2] = B10000000;
          upperchar[3] = B11001111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00111000;
          upperchar[1] = B00101000;
          upperchar[2] = B00111000;
          upperchar[3] = B01111110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B10100000;
          upperchar[1] = B11100000;
          upperchar[2] = B10100000;
          upperchar[3] = B11101111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B11010000;
          upperchar[1] = B11110000;
          upperchar[2] = B11010000;
          upperchar[3] = B11110111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00010000;
          upperchar[1] = B00101000;
          upperchar[2] = B00000000;
          upperchar[3] = B01111110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00101000;
          upperchar[1] = B01010100;
          upperchar[2] = B00000000;
          upperchar[3] = B01111110;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B01100000;
          upperchar[1] = B10010000;
          upperchar[2] = B10010000;
          upperchar[3] = B01101111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B00111000;
          upperchar[1] = B00010000;
          upperchar[2] = B00101000;
          upperchar[3] = B11111111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B11111000;
          upperchar[1] = B01010000;
          upperchar[2] = B10101000;
          upperchar[3] = B00001111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100000;
          upperchar[2] = B01000000;
          upperchar[3] = B10101111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B00100000;
          upperchar[2] = B11100000;
          upperchar[3] = B00101111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B11100000;
          upperchar[1] = B11100000;
          upperchar[2] = B10000000;
          upperchar[3] = B11101111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B11110000;
          upperchar[1] = B01100000;
          upperchar[2] = B11110000;
          upperchar[3] = B00001111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==8))
      {
        case 1:
          upperchar[0] = B01000000;
          upperchar[1] = B11100000;
          upperchar[2] = B00000000;
          upperchar[3] = B01001111;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11100010;
          upperchar[1] = B00100010;
          upperchar[2] = B00100010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11110010;
          upperchar[1] = B01010010;
          upperchar[2] = B01010010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B10000010;
          upperchar[1] = B10000010;
          upperchar[2] = B11100010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11100010;
          upperchar[1] = B10000010;
          upperchar[2] = B11100010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11110010;
          upperchar[1] = B10100010;
          upperchar[2] = B11110010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11000010;
          upperchar[1] = B01000010;
          upperchar[2] = B10000010;
          upperchar[3] = B11000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11100010;
          upperchar[1] = B10100010;
          upperchar[2] = B11100010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B10100010;
          upperchar[1] = B11100010;
          upperchar[2] = B10100010;
          upperchar[3] = B11100010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B10101010;
          upperchar[1] = B11111010;
          upperchar[2] = B10101010;
          upperchar[3] = B11111010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B01000010;
          upperchar[1] = B10100010;
          upperchar[2] = B10100010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B01010010;
          upperchar[1] = B10101010;
          upperchar[2] = B10101010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B01100010;
          upperchar[1] = B10010010;
          upperchar[2] = B10010010;
          upperchar[3] = B01100010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11100010;
          upperchar[1] = B01000010;
          upperchar[2] = B10100010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11111010;
          upperchar[1] = B01010010;
          upperchar[2] = B10101010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B01000010;
          upperchar[1] = B11100010;
          upperchar[2] = B01000010;
          upperchar[3] = B10100010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11100010;
          upperchar[1] = B00100010;
          upperchar[2] = B11100010;
          upperchar[3] = B00100010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11100010;
          upperchar[1] = B11100010;
          upperchar[2] = B10000010;
          upperchar[3] = B11100010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B11111010;
          upperchar[1] = B01010010;
          upperchar[2] = B11111010;
          upperchar[3] = B00000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==9))
      {
        case 1:
          upperchar[0] = B01000010;
          upperchar[1] = B11100010;
          upperchar[2] = B00000010;
          upperchar[3] = B01000010;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B00100111;
          upperchar[2] = B00100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11110101;
          upperchar[1] = B01010111;
          upperchar[2] = B01010101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B10000101;
          upperchar[1] = B10000111;
          upperchar[2] = B11100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B10000111;
          upperchar[2] = B11100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11110101;
          upperchar[1] = B10100111;
          upperchar[2] = B11110101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11000101;
          upperchar[1] = B01000111;
          upperchar[2] = B10000101;
          upperchar[3] = B11000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B10100111;
          upperchar[2] = B11100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B10100101;
          upperchar[1] = B11100111;
          upperchar[2] = B10100101;
          upperchar[3] = B11100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11010101;
          upperchar[1] = B11110111;
          upperchar[2] = B11010101;
          upperchar[3] = B11110101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B01000101;
          upperchar[1] = B10100111;
          upperchar[2] = B10100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B01010101;
          upperchar[1] = B10101111;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B01100101;
          upperchar[1] = B10010111;
          upperchar[2] = B10010101;
          upperchar[3] = B01100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B01000111;
          upperchar[2] = B10100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11111101;
          upperchar[1] = B01010111;
          upperchar[2] = B10101101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B01000101;
          upperchar[1] = B11100111;
          upperchar[2] = B01000101;
          upperchar[3] = B10100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B00100111;
          upperchar[2] = B11100101;
          upperchar[3] = B00100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B11100111;
          upperchar[2] = B10000101;
          upperchar[3] = B11100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B11110101;
          upperchar[1] = B01100111;
          upperchar[2] = B11110101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==10))
      {
        case 1:
          upperchar[0] = B01000101;
          upperchar[1] = B11100111;
          upperchar[2] = B00000101;
          upperchar[3] = B01000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B00100111;
          upperchar[2] = B00100111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11110101;
          upperchar[1] = B01010111;
          upperchar[2] = B01010111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B10000101;
          upperchar[1] = B10000111;
          upperchar[2] = B11100111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B10000111;
          upperchar[2] = B11100111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11110101;
          upperchar[1] = B10100111;
          upperchar[2] = B11110111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==5)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11000101;
          upperchar[1] = B01000111;
          upperchar[2] = B10000111;
          upperchar[3] = B11000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==6)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B10100111;
          upperchar[2] = B11100111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==7)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B10100101;
          upperchar[1] = B11100111;
          upperchar[2] = B10100111;
          upperchar[3] = B11100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==8)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11010101;
          upperchar[1] = B11110111;
          upperchar[2] = B11010111;
          upperchar[3] = B11110101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==9)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B01000101;
          upperchar[1] = B10100111;
          upperchar[2] = B10100111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==10)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B01010101;
          upperchar[1] = B10101111;
          upperchar[2] = B00000111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==11)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B01100101;
          upperchar[1] = B10010111;
          upperchar[2] = B10010111;
          upperchar[3] = B01100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==12)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B01000111;
          upperchar[2] = B10100111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==13)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11111101;
          upperchar[1] = B01010111;
          upperchar[2] = B10101111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==14)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B01000101;
          upperchar[1] = B11100111;
          upperchar[2] = B01000111;
          upperchar[3] = B10100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==15)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B00100111;
          upperchar[2] = B11100111;
          upperchar[3] = B00100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==16)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B11100111;
          upperchar[2] = B10000111;
          upperchar[3] = B11100101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==17)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B11110101;
          upperchar[1] = B01100111;
          upperchar[2] = B11110111;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==18)&&(vowel==11))
      {
        case 1:
          upperchar[0] = B01000101;
          upperchar[1] = B11100111;
          upperchar[2] = B00000111;
          upperchar[3] = B01000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B00101101;
          upperchar[2] = B00100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==1)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B11110101;
          upperchar[1] = B01011101;
          upperchar[2] = B01010101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==2)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B10000101;
          upperchar[1] = B10001101;
          upperchar[2] = B11100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==3)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B11100101;
          upperchar[1] = B10001101;
          upperchar[2] = B11100101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==4)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch((consonant==0)&&(vowel==12))
      {
        case 1:
          upperchar[0] = B00000101;
          upperchar[1] = B00001101;
          upperchar[2] = B00000101;
          upperchar[3] = B00000101;
          upperchar[4] = B00000000;
          upperchar[5] = B00000000;
          upperchar[6] = B00000000;
          upperchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        
        
        
        
        
        
        
        
        
         
      
      //////////////////////////////////////////////////////////////받침없는 글자 스위치문 추가 바람

      for(int j=0; j<4; j++)
      {
        lc.setRow(Mposition, j, upperchar[j]); //Mposition번째 매트릭스에서 받침없는 글자를 출력
      }
      
      for(int k=4; k<8; k++)
      {
        lc.setRow(Mposition, k, blank[k]); //Mposition번째 매트릭스에서 받침영역을 빈칸으로 만든다.
      }

        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==0)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00000000;
          lowerchar[6] = B00000000;
          lowerchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==1)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00011100;
          lowerchar[6] = B00000100;
          lowerchar[7] = B00000100;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==2)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00111100;
          lowerchar[6] = B00010100;
          lowerchar[7] = B00010100;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==3)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00110010;
          lowerchar[6] = B00010101;
          lowerchar[7] = B00010101;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==4)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00100000;
          lowerchar[6] = B00100000;
          lowerchar[7] = B00111000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==5)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B01000111;
          lowerchar[6] = B01000010;
          lowerchar[7] = B01110101;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==6)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000010;
          lowerchar[5] = B01000111;
          lowerchar[6] = B01000000;
          lowerchar[7] = B01110010;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==7)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00011100;
          lowerchar[6] = B00010000;
          lowerchar[7] = B00011100;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==8)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00110000;
          lowerchar[5] = B00010000;
          lowerchar[6] = B00100000;
          lowerchar[7] = B00110000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==9)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00110000;
          lowerchar[5] = B00010111;
          lowerchar[6] = B00100001;
          lowerchar[7] = B00110001;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==10)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00110000;
          lowerchar[5] = B00010111;
          lowerchar[6] = B00100101;
          lowerchar[7] = B00110111;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==11)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00110101;
          lowerchar[5] = B00010111;
          lowerchar[6] = B00100101;
          lowerchar[7] = B00110111;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==12)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00110000;
          lowerchar[5] = B00010010;
          lowerchar[6] = B00100101;
          lowerchar[7] = B00110101;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==13)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00110111;
          lowerchar[5] = B00010111;
          lowerchar[6] = B00100100;
          lowerchar[7] = B00111111;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==14)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B01100000;
          lowerchar[5] = B00101111;
          lowerchar[6] = B01000110;
          lowerchar[7] = B01101111;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==15)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00110010;
          lowerchar[5] = B00010111;
          lowerchar[6] = B00100000;
          lowerchar[7] = B00110010;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==16)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00011100;
          lowerchar[6] = B00010100;
          lowerchar[7] = B00011100;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==17)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B01010000;
          lowerchar[5] = B01110000;
          lowerchar[6] = B01010000;
          lowerchar[7] = B01110000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==18)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B01010000;
          lowerchar[5] = B01110010;
          lowerchar[6] = B01010101;
          lowerchar[7] = B01110101;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==19)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00001000;
          lowerchar[6] = B00010100;
          lowerchar[7] = B00100010;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==20)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00010100;
          lowerchar[6] = B00101010;
          lowerchar[7] = B00000000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==21)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00110000;
          lowerchar[5] = B01001000;
          lowerchar[6] = B01001000;
          lowerchar[7] = B00110000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==22)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B00011100;
          lowerchar[6] = B00001000;
          lowerchar[7] = B00010100;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==23)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00010000;
          lowerchar[5] = B00111000;
          lowerchar[6] = B00010000;
          lowerchar[7] = B00101000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==24)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B01110000;
          lowerchar[5] = B00010000;
          lowerchar[6] = B01110000;
          lowerchar[7] = B00010000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==25)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B01110000;
          lowerchar[5] = B01110000;
          lowerchar[6] = B01000000;
          lowerchar[7] = B01110000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==26)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00000000;
          lowerchar[5] = B01111100;
          lowerchar[6] = B00101000;
          lowerchar[7] = B01111100;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      switch(bottomConsonant==27)
      {
        case 1:
          lowerchar[0] = B00000000;
          lowerchar[1] = B00000000;
          lowerchar[2] = B00000000;
          lowerchar[3] = B00000000;
          lowerchar[4] = B00010000;
          lowerchar[5] = B00111000;
          lowerchar[6] = B00000000;
          lowerchar[7] = B00010000;
          break;
        default :
          ;
      }
        //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

      ///////////////////////////////////////////////////////////////받침글자 스위치문 추가 바람
      for(int m=4; m<8; m++)
      {
        lc.setRow(Mposition, m, lowerchar[m]); //Mposition번째 매트릭스에서 받침글자를 출력한다. 
      }  

    }
  
  };

}
