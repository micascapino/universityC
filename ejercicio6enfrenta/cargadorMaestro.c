#include <stdio.h>

typedef struct{
    int nro;
    char nom[50];
    char domicilio[50];
    char cuil[20];
}empleado;

int maintxt(){
    empleado e;
    FILE *arch, *txt;

    arch = fopen("maestro","wb");
    txt = fopen("maestrotxt.txt","r");

    while(fscanf(txt,"%d %s %s %s",&e.nro, e.nom,e.domicilio,e.cuil) == 4){
        fwrite(&e,sizeof(empleado),1,arch);
    }
    fclose(arch);
    fclose(txt);
    return 0;
}
