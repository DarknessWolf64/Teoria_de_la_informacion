las codificaciones que hice en el esquema de comunicacion el cual es el archivo de codificaciones.cpp fueron las siguientes:

1. huffman

2. shannon-fano

3. codificacion cesar: 
Esta fue inventada por mi la cual consiste en un tipo de modificacion del cifrado cesar normal la cual hace lo mismo que esta pero la variacion es que en lugar de usar letras utiliza un arreglo de binarios los cuales son su equivalencia, su funcion es simple busca una coincidencia en el arreglo de cesar y regresa el valor 3 indices mas.
Para el caso de utilizar el codificado y decodificado se envia el arreglo de binarios de la codificacion cesar, el binario a codificar o a decodificar y sus respectivos tamaños.

4. codificacion a doble linea:
Esta fue inventada por mi la cual consiste en divir en 2 arreglos, el arreglo que se utiliza para el cifrado cesar igual, su funcion es algo simple la cual si busca una coincidencia en alguna de las listas regresar el valor de la otra lista pero conservando la misma posicion.
Para el caso de utilizar el codificado y decodificaco se envia ambos arreglos, el arreglo a codificar o a decodificar, en el caso de las 2 listas se envia el numero que es la mitad de la lista donde se hizo ambas y el tamaño de la lista a codificar o a decodificar.

--------------------------------------------------------------------------------------------------------------------------
Implementacion del metodo adaptativa en el canal

para el caso de huffman y shannon-fano que solo se envia un string solamente se verifica mediante un booleano el proceso es este:

canal 1 con mucho ruido es decir para la perdida del paquete
canal 2 con poco ruido
canal 3 sin nada de ruido

si en el canal 1 no se envia el booleano es falso y pasa al canal 2, si en el canal 2 no se envia nuevamente el booleano es falso y pasa al canal 3 este canal lo envia si o si.

para saber si pasan por el canal se tiene que tomar en cuenta la probabilidad de perdida de paquete que se hizo por cada canal, en el 1 es de 0.5, del 2 es de 0.85 y del ultimo no tiene esa afectacion. para ver si se pierde o no genera una probabilidad aleatoria entre el 0 y el 1 si la probabilidad es menor a la de ese canal pasa sino pasa a otro canal hasta que se envia.

para el caso de las otras 2 codificaciones se toma en cuenta los paquetes enviados y tambien se toma en cuenta lo siguiente:

canal 1 con mucho ruido es decir para la perdida del paquete
canal 2 con poco ruido
canal 3 sin nada de ruido

se crea una lista de booleanos para ver si el paquete fue enviado o no por ese canal.

si en el canal 1 no se envia el paquete en ese arreglo en su indece se agrega un booleano falso, sino se agrega un verdadero al arreglo y se finaliza el proceso de envios.

si en el canal 2 se checan si el paquete fue enviado por medio del arreglo de booleanos si en el arreglo marca falso se toma el indice y se envia el paquete con ese numero, sino se envia se pasa al canal 3 el cual hace los mismo.

para saber si pasan por el canal se tiene que tomar en cuenta la probabilidad de perdida de paquete que se hizo por cada canal, en el 1 es de 0.5, del 2 es de 0.85 y del ultimo no tiene esa afectacion. para ver si se pierde o no genera una probabilidad aleatoria entre el 0 y el 1 si la probabilidad es menor a la de ese canal pasa sino pasa a otro canal hasta que se envia.

--------------------------------------------------------------------------------------------------------------------------

Modificaciones

Algunas modificaciones que se hicieron fueron crear otro canal especializado para huffman y shannon-fano, y crear un receptor para cada codificacion.

--------------------------------------------------------------------------------------------------------------------------
Proceso de eleccion de codificacion

Esta parte se hace con un switch en base a un numero generado aleatoriamente el cual elige el cifrado y en el mismo se implementa su codificacion, envio, canal y receptor el cual hace la decoficacion.

Cabe aclarar que solo se modifico la parte del canal y receptor, los demas componentes siguen igual.
