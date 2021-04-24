#include <stdio.h>

typedef struct{
int seccion;
char legajo[6];
float importe;
}pagos;

int maintxt(){

    pagos p;
    FILE *arch, *txt;

    arch = fopen("pagos","wb");
    txt = fopen("pagostxt.txt","r");

    while(fscanf(txt,"%d %s %f", &p.seccion, p.legajo, &p.importe) == 3){
        fwrite(&p,sizeof(pagos),1,arch);
    }
    fclose(arch);
    fclose(txt);
    return 0;

}



