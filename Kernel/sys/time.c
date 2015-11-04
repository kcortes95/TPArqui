#include "../arch/include/types.h"
#include "../arch/include/arch.h"
#include "include/time.h"
#include "include/video.h"


void getTime(int GMT){
	int s = getHours();
	int m = getMinutes();
	int h = getSeconds();
    //printf("%d:%d:%d",h+GMT,s,m);
}

//TODO: Esto deberiamos hacerlo mejor! Estamos repitiendo código
int getHours(){
	_outport(0x70,4); //horas
	int hBCD = _inport(0x71);
	return BCDtoNumber(hBCD);
} 

//TODO: corregir!
int getMinutes(){
	_outport(0x70,2); //minutos
	int mBCD = _inport(0x71);
	return BCDtoNumber(mBCD);
}

//TODO: corregir!
int getSeconds(){
	_outport(0x70,4); //segundos
	int sBCD = _inport(0x71);
	return BCDtoNumber(sBCD);
}

int BCDtoNumber(int bcd) {
	int unidad = bcd & 0x0F;
	int decena = (bcd & 0xF0) >> 4;
	return decena * 10 + unidad;
}
