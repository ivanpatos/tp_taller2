Introducción
============

El servidor Udrive es desarrollado en c++, con la ayuda de las librerías **mongoose** como base para implementar un servidor http, **jsoncpp** para el manejo de datos json y **rocksdb** para la persistencia de datos.

Para realizar tests unitarios, se utiliza **google test** junto **google mock**, y para testear la api se ejecutan scripts python que hacen uso de las librerías **requests** y **unittest**.

El presente documento tiene como objetivo explicar cómo instalar y ejecutar el servidor.
