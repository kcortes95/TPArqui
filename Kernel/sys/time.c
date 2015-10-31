#include "time.h"
#include "libkevin/video.h"
#include "libasm.h"

void getTime(int GMT){
    int s = getHours();
    int m = getMinutes();
    int h = getSeconds();
    //printf("%d:%d:%d",h+GMT,s,m);
}

//TODO: Esto deberiamos hacerlo mejor! Estamos repitiendo código
int getHours(){
    out_port(0x70,4); //horas
    int hBCD = in_port(0x71);
    return BCDtoNumber(hBCD);
} 

//TODO: corregir!
int getMinutes(){
    out_port(0x70,2); //minutos
    int mBCD = in_port(0x71);
    return BCDtoNumber(mBCD);
}

//TODO: corregir!
int getSeconds(){
    out_port(0x70,4); //segundos
    int sBCD = in_port(0x71);
    return BCDtoNumber(sBCD);
}

int BCDtoNumber(int bcd){
    int unidad = bcd & 0x0F;
    int decena = (bcd & 0xF0) >> 4;
    return decena * 10 + unidad;
}