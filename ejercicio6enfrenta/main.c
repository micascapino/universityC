#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int nro;
    char nom[50];
    char domicilio[50];
    char cuil[20];
}empleado;

void bajas();
void cargaArchivos();
void muestraActualizado();

int main()
{
cargaArchivos();
bajas();
muestraActualizado();
return 0;
}

void cargaArchivos(){
    empleado e;
    FILE *archM, *txtM, *archB, *txtB;

    archM = fopen("maestro","wb");
    txtM = fopen("maestrotxt.txt","r");

    while(fscanf(txtM,"%d %s %s %s",&e.nro, e.nom,e.domicilio,e.cuil) == 4){
        fwrite(&e,sizeof(empleado),1,archM);
    }
    fclose(archM);
    fclose(txtM);

    archB = fopen("bajas","wb");
    txtB = fopen("bajastxt.txt","r");

    while(fscanf(txtB,"%d %s %s %s",&e.nro, e.nom,e.domicilio,e.cuil) == 4){
        fwrite(&e,sizeof(empleado),1,archB);
    }
    fclose(archB);
    fclose(txtB);
}

void bajas(){
FILE *maestro, *bajas, *actualizado;
empleado em,eb;

maestro=fopen("maestro","rb");
bajas=fopen("bajas","rb");
actualizado=fopen("actualizado","wb");

if (maestro == NULL || bajas == NULL)
    printf("Algun archivo no existe");
else{
    fread(&em,sizeof(empleado),1,maestro);
    fread(&eb,sizeof(empleado),1,bajas);
    while (!feof(maestro) || !feof(bajas)){
        if (em.nro == eb.nro){
            //elimina, no lo escribe en el de actualizar
            fread(&em,sizeof(empleado),1,maestro);
            fread(&eb,sizeof(empleado),1,bajas);
        }
        else if (em.nro < eb.nro){
            fwrite(&em,sizeof(empleado),1,actualizado);
            fread(&em,sizeof(empleado),1,maestro);
        }
        else{
            printf("No existe este empleado %d en el maestro.\n",eb.nro);
            fread(&eb,sizeof(empleado),1,bajas);
        }
    }
    fclose(maestro);fclose(bajas);fclose(actualizado);
}
}



void muestraActualizado(){
    FILE *arch;
    empleado e;

    arch=fopen("actualizado","rb");
    if (arch == NULL)
        printf("No se genero el archivo o no se encuentra.");
    else{
        fread(&e,sizeof(empleado),1,arch);
        while(!feof(arch)){
            printf("%d %s %s %s\n",e.nro,e.nom,e.domicilio,e.cuil);
            fread(&e,sizeof(empleado),1,arch);
        }
        fclose(arch);
    }
}
