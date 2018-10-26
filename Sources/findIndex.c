#include<stdio.h>
#include<stdlib.h>

unsigned int *EncontrarIndex(unsigned int RegistroActual)
{
    unsigned int RegistrosSalida[11]={0x0,0x1,0x3,0x7,0xF,0x1F,0x3F,0x7F,0xFF,0x1FF,0x3FF};
    static unsigned int RegSubidaBajada[2];
    unsigned short iterador=0;
    unsigned short index=0;
    while((RegistroActual>=RegistrosSalida[iterador]) && (iterador<11))
        {
            index=iterador;
            iterador++;
        }

    if (RegistrosSalida[index]==0x0)
    {
        RegSubidaBajada[0]=0x0;
        RegSubidaBajada[1]=0x1;
    }
    else if (RegistrosSalida[index]==0x3FF)
    {
        RegSubidaBajada[0]=0x1FF;
        RegSubidaBajada[1]=0x3FF;    
    }
    else
    {
        RegSubidaBajada[0]=RegistrosSalida[index-1];
        RegSubidaBajada[1]=RegistrosSalida[index+1];
    }
    return RegSubidaBajada;
}

int main(void){


    unsigned int RegistroActual=0x1;
    unsigned int *p;
    unsigned int i;
    p=EncontrarIndex(RegistroActual);
    for (i = 0; i < 2; ++i)
    {
        /* code */
        printf("%d\n",*(p+i));
    }
    
    return 0;

}