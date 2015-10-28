#include <time.h>
#include <video.h>
#include <libasm.h>


int BCDtoNumber(int bcd){
    int unidad = bcd & 0x0F;
    int decena = (bcd & 0xF0) >> 4;
    return decena * 10 + unidad;
}

void getTime(int GMT){
    int s = getHours();
    int m = getMinutes();
    int h = getSeconds();
    printf("%d:%d:%d"h+GMT,s,m);
}

int getHours(){
    out_port(0x70,4); //horas
    int hBCD = in_port(0x71);
    h = BCDtoNumber(hBCD);
    return h;
} 

int getMinutes(){
	out_port(0x70,2); //minutos
    int mBCD = in_port(0x71);
    m = BCDtoNumber(mBCD);
    return m;
}

int getSeconds(){
	out_port(0x70,0); //segundos
    int sBCD = in_port(0x71);
    s = BCDtoNumber(sBCD);
    return s;
}