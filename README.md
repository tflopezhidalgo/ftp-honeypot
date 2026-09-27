# FTP Honeypot

Pequeñisimo servidor FTP que sirve como [honeypot](https://es.wikipedia.org/wiki/Honeypot) escrito en C++ para la materia Taller de Programacion 1 (FIUBA).

El codigo contiene un cliente y el servidor propiamente dicho. El cliente posee los comandos basicos para realizar operaciones como si fuese un servidor FTP real.

El archivo `taller.cfg` contiene la configuracion de los comandos junto con algunos mensajes que son enviados desde el servidor.

Utiliza `make` para compilar las dependencias y los archivos fuentes.

## Compilacion

Para generar los ejecutables basta con correr `make`, esto generara el binario para el cliente y el servidor.

## Uso 

### Servidor

Para correr el servidor basta con indicar el archivo de configuracion a utilizar y el puerto

``` 
./server <puerto> <archivo configuracion>
```

### Cliente

Para correr el cliente debemos conocer el puerto en que se levanto el servidor

```
./client <puerto>
```