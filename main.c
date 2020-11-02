#include <stdio.h>
#include <windows.h>

const float melo[20]={261.626f,
                      277.183f,
                      293.665f,
                      311.127f,
                      329.628f,
                      349.228f,
                      369.994f,
                      391.995f,
                      415.305f,
                      440.000f,
                      466.164f,
                      493.883f,
                      523.251f,
                      554.365f,
                      587.330f,
                      622.254f,
                      659.255f,
                      698.456f,
                      739.989f,
                      0.0f
                    };
enum lv{
  C4,  //ド <-普通のド
  CS4,
  D4,  //レ
  DS4,
  E4,  //ミ
  F4,  //ファ
  FS4,
  G4,  //ソ
  GS4,
  A4,  //ラ
  AS4,
  B4,  //シ
  C5,  //ド
  CS5,
  D5,  //レ
  DS5,
  E5,  //ミ
  F5,  //ファ
  FS5,
  NO
};

int ind_lv[11] = {
  17,
  16,
  14,
  12,
  11,
  9,
  7,
  5,
  4,
  2,
  0
};


FILE *input;

void file_open();
void file_close();
void read();
void play();
void view();
void err(int num);

char line[12][100] = {'\0'};
char dummy[100] = {'\0'};

float val[160][2] = {0};

int tmp = 0;

int p = 0;

int main() {
  file_open();
  read();
  read();
  file_close();
  view();
  play();
  return 0;
}

void file_open(){
  if((input = fopen("score.txt","r")) == NULL){
    err(1);
  }
}

void file_close(){
  fclose(input);
}

void read(){
  int index = 0;

  float len = 0.0f;
  enum lv level;

  fscanf(input,"%d",&tmp);
  fgets(dummy,100,input);
  fgets(dummy,100,input);
  for(int i = 0 ; i < 12 ; i++){
    fgets(line[i],100,input);
    printf("%s",line[i]);
  }
  while(index < 90){
    len = 0;
    level = 0;
    if(index % 9 != 0){
      for(int i = 0;i < 11;i++){
        switch(line[i][index]){
          case '8':
            level = ind_lv[i];
            len = 60.0f / tmp / 2.0f;
            if(line[i][index+1] == '.') len *= 1.5f;
            if(line[11][index] == 'S') level++;
            if(line[11][index] == 'F') level--;
            if(line[11][index] == 'R') level = 19;
            val[p][0] = melo[level];
            val[p][1] = len;
            p++;
            break;
          case '4':
            level = ind_lv[i];
            len = 60.0f / tmp;
            if(line[i][index+1] == '.') len *= 1.5f;
            if(line[11][index] == 'S') level++;
            if(line[11][index] == 'F') level--;
            if(line[11][index] == 'R') level = 19;
            val[p][0] = melo[level];
            val[p][1] = len;
            p++;
            break;
          case '2':
            level = ind_lv[i];
            len = 2.0f * 60.0f / tmp;
            if(line[i][index+1] == '.') len *= 1.5f;
            if(line[11][index] == 'S') level++;
            if(line[11][index] == 'F') level--;
            if(line[11][index] == 'R') level = 19;
            val[p][0] = melo[level];
            val[p][1] = len;
            p++;
            break;
          case '1':
            level = ind_lv[i];
            len = 4.0f * 60.0f / tmp;
            if(line[i][index+1] == '.') len *= 1.5f;
            if(line[11][index] == 'S') level++;
            if(line[11][index] == 'F') level--;
            if(line[11][index] == 'R') level = 19;
            val[p][0] = melo[level];
            val[p][1] = len;
            p++;
            break;
          default:
            break;
        }
      }
    }
    if(line[12][index] == 'E') break;
    index++;
  }
}

void view(){
  printf("  H z  :  m s  \n");
  for(int i = 0;i<p;i++){
    printf("%02d:%3.3f:%3.3f\n",i,val[i][0],val[i][1]);
  }
}

void play(){
  for(int i = 0;i<p;i++){
    Beep(val[i][0],val[i][1] * 1000.0f);
  }
}

void err(int num){
  switch (num) {
    case 1:
      printf("FILE OPEN ERROR\n");
      break;
    default:
      printf("UNKNOWN ERROR\n");
      break;
  }
  exit(1);
}
