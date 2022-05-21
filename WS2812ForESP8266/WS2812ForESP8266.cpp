/**
 * Copyright (c) 2022 by LiHooo
 */
#include "Arduino.h"
#include "WS2812ForESP8266.h"


WS2812::WS2812(Pix_type *buf,int ledNum){
    this->buf=buf;
    this->ledNum=ledNum;
    this->init();
}
WS2812::WS2812(Pix_type *buf,int ledNum,bool inverseColor){
    this->buf=buf;
    this->ledNum=ledNum;
    this->inverseColor=inverseColor;
    this->init();
}

void WS2812::init(){
    Serial.begin(8000000UL,SERIAL_8N1,SERIAL_TX_ONLY,15,1);// 最后的参数invert=1是翻转TXD的电平
    Serial.swap();  //把UART0的TXD切换到GPIO15

}


void WS2812::setInverseColor(bool inverseColor){
    this->inverseColor=inverseColor;
    if(inverseColor){
        this->CODE0=DEF_CODE1;
        this->CODE1=DEF_CODE0;
    }
    else{
        this->CODE0=DEF_CODE0;
        this->CODE1=DEF_CODE1;
    }
}
bool WS2812::isInverseColor(){
    return this->inverseColor;
}
void WS2812::setLedNum(int ledNum){
    this->ledNum=ledNum;
}
int  WS2812::getLedNum(){
    return this->ledNum;
}

void WS2812::clear()
{
    for(int i=0;i<ledNum;i++)   
    {
        buf[i].Value=0x00000000UL;
    }
}
void WS2812::clear(Pix_type blank_pix)
{
    for(int i=0;i<ledNum;i++)   
    {
        buf[i]=blank_pix;
    }
}
void WS2812::setPix(int index,Pix_type pix)
{
    if(index>ledNum)return;
    buf[index]=pix;
}

void WS2812::setPix(int index,unsigned long rgb_raw)
{
    if(index>ledNum)return;
    buf[index].Value=rgb_raw;
}
void WS2812::setPix(int index,RGB_type rgb)
{
    if(index>ledNum)return;
    buf[index].RGB=rgb;
}

void WS2812::show()
{
    unsigned char temp;  
    Pix_type t_pix;
    for(int i=0;i<ledNum;i++)   
    {
        t_pix=buf[i];
        //ESP.wdtFeed();
        //RGB->GRB
        temp=t_pix.RGB.Red;
        t_pix.RGB.Red=t_pix.RGB.Green;
        t_pix.RGB.Green=temp;
        for(int k=0;k<24;k++)
        {
            if(t_pix.Value&0x00800000UL)   
            {
                while(( (USS(0) >> USTXC) & 0xff) >= 0x7f);  
                USF(0) = CODE1;  
                //Serial.write(CODE1);  //上2行等效于此代码，但Arduino库太慢
            }               
            else 
            {
                while(( (USS(0) >> USTXC) & 0xff) >= 0x7f);
                USF(0) = CODE0;
                //Serial.write(CODE0);
            }     
            t_pix.Value<<=1;
        }
    }
}