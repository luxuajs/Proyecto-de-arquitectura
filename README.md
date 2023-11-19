# Proyecto de Arquitectura

## Integrantes:
  ### Gabriel Silva 29803338
  ### Juan Sanabria 30276906

## Memoria Cache

En este proyecto de arquitectura, hemos desarrollado una simulación de una memoria caché. La simulación se basa en una configuración preestablecida, la cual se encuentra definida en el archivo "configuracion.txt". Al mismo tiempo, se utiliza un archivo de entrada, "entrada.txt", para realizar operaciones y evaluar el rendimiento de la memoria caché.

## Descripción del Proyecto

La memoria caché es una parte crucial en la arquitectura de computadoras, diseñada para mejorar el rendimiento del acceso a la memoria principal. Nuestro proyecto se enfoca en simular el comportamiento de una memoria caché y evaluar su eficacia mediante la manipulación de dos archivos clave: "configuracion.txt" y "entrada.txt".
El programa pricipal se encuentra en el archivo **main.cpp** y este puede ser corrido con la instrucción *make* en la terminal
de linux, esta intrucción realizara un ejecutable llamado **proyecto** gracias al archico **makefile** que se encuentra en la carpeta.

## Configuración de la Memoria Caché

En el archivo "configuracion.txt", se establecen parámetros esenciales para la configuración de la memoria caché. Estos parámetros incluyen el tamaño de la caché, el tamaño de bloque, la asociatividad, y otros elementos que determinan el funcionamiento y la capacidad de la memoria caché.
En la parte final podras encontrar una explicación del formato de entrada del archivo configuracion.txt y que representa cada numero que se guarda en el.

## Evaluación del Rendimiento

Al proporcionar una entrada en el archivo "entrada.txt", el programa simula el acceso a la memoria caché según la configuración definida previamente. La simulación registra y analiza los aciertos, fallos, así como la tasa de aciertos y fallos obtenidos durante la ejecución.

### Resultados y Conclusiones

Los resultados de la simulación permiten evaluar la eficacia de la memoria caché en función de la configuración establecida y las operaciones realizadas. La tasa de aciertos y fallos proporciona información valiosa sobre el desempeño del sistema y sugiere posibles ajustes en la configuración para optimizar el rendimiento.

Este proyecto no solo ofrece una visión práctica de la arquitectura de la memoria caché, sino que también proporciona una herramienta para comprender mejor cómo diferentes configuraciones afectan el rendimiento del sistema.


# Tener en cuenta entrada para cada archivo (configuracion.txt y entrada.txt)

## configuracion.txt
En este archivo cada entero representa:

configuracion1: Representa el tamaño total de la memoria caché en bytes.

configuracion2: Indica el tipo de correspondencia en la caché. Si configuracion2 es 0, se utiliza la correspondencia directa; si es 1, se utiliza la correspondencia asociativa por conjunto.

configuracion3: Representa el tamaño de una línea o conjunto de la caché en bytes.

configuracion4: Indica la política de reemplazo en caso de fallos de caché. Si configuracion4 es 0, se utiliza la política LRU (Least Recently Used); si es 1, se utiliza la política de reemplazo aleatorio.

## entrada.txt
En este archivo se guarda la direcciones de memoria a la cual se debe acceder.

