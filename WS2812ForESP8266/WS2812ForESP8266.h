#ifndef __WS2812_H_
#define __WS2812_H_



//UART模拟,串口设置电平反转，起始位1位，数据8位，停止位1位，串口是LSB
//START(H) HHHHHHLL  STOP(L)    L=3*0.125us=0.375us;  H=7*0.125us=0.875us
//data=11000000
#define DEF_CODE1  B11000000
//START(H) HHLLLLLL  STOP(L)    H=3*0.125us=0.375us;  L=7*0.125us=0.875us
//data=11111100
#define DEF_CODE0  B11111100

typedef struct
{
  unsigned char :8;
  unsigned char Red;
  unsigned char Green;
  unsigned char Blue;
}RGB_type;
typedef union
{
  RGB_type RGB;
  unsigned long Value;
}Pix_type;

class WS2812 {
  private:
    int ledNum;
    bool inverseColor=false;
    unsigned char CODE0=DEF_CODE0;
    unsigned char CODE1=DEF_CODE1;
    Pix_type *buf;
    void init();
  public:
    WS2812(Pix_type *buf,int ledNum);
    WS2812(Pix_type *buf,int ledNum,bool inverseColor);

    void setInverseColor(bool inverseColor);
    bool isInverseColor();
    void setLedNum(int ledNum);
    int  getLedNum();
    void clear();
    void clear(Pix_type blank_pix);
    void setPix(int index,Pix_type pix);
    void setPix(int index,unsigned long rgb_raw);
    void setPix(int index,RGB_type rgb);
    void show();

};

#endif