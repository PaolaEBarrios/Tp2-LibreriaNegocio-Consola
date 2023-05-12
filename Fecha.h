#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

int ValidarFecha(int dia, int mes, int anio){

switch(mes){

case 1:
if((anio>=1900 && anio<=2020) && (dia>=1 && dia<=31)){
return 1;
}
else{
return -1;
}
break;

case 2:
if((anio % 4 == 0  && anio % 100 != 0) || anio % 400 == 0){
    if((dia >= 1 && dia <= 29) && (anio>=1900 && anio<=2020)){
        return 1;
    }
    else{
            return -1;
    }
}
else if((dia>=1 && dia <= 28) && (anio>=1900 && anio<=2020)){
    return 1;
}
else{
    return -1;
}
break;

case 3:
if((anio>=1900 && anio<=2020) && (dia>=1 && dia<=31)){
return 1;
}
else{
return -1;
}
break;

case 4:
if((anio>=1900 && anio<=2020) && (dia>=1 && dia<=30)){
return 1;
}
else{
return -1;
}
break;

case 5:
if((anio>=1900 && anio<=2020) && (dia>=1 && dia<=31)){
return 1;
}
else{
return -1;
}
break;

case 6:
if((dia>=1 && dia<=30) && (anio>=1900 && anio<=2020)){
return 1;
}
else{
return -1;
}
break;

case 7:
if((anio>=1900 && anio<=2020) && (dia>=1 && dia<=31)){
return 1;
}
else{
return -1;
}
break;
case 8:
if((dia>=1 && dia<=31) && (anio>=1900 && anio<=2020)){
return 1;
}
else{
return -1;
}
break;

case 9:
if((dia>=1 && dia<=30) && (anio>=1900 && anio<=2020)){
return 1;
}
else{
return -1;
}
break;

case 10:
if((dia>=1 && dia<=31) && (anio>=1900 && anio<=2020)){
return 1;
}
else{
return -1;
}
break;
case 11:
if((anio>=1900 && anio<=2020)&& (dia>=1 && dia<=30)){
return 1;
}
else{
return -1;
}
break;
case 12:
if((anio>=1900 && anio<=2020) && (dia>=1 && dia<=31)){
return 1;
}
else{
return -1;
}
break;

default:
return -1;
break;
}

}


#endif // FECHA_H_INCLUDED
