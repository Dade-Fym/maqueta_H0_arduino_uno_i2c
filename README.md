# maqueta_H0_arduino_uno_i2c
Codigo C++ para desvios y semaforos de una maqueta ferroviaria
Existen dos conceptos basicos la salida digital o pines de arduino y la salida logica que es cada una de las funciones de salida creadas en el codigo.
Este codigo esta pensado para uan maqueta ferroviaria que maneje los desvios con servomotores basicos para arduino
Los semaforos se controlan añadiendo una salida digital y asociandola a la misma salida logica creada en el codigo
Se pueden asociar varios servomotores y salidas digitales a una salida logica
Lleva una pantalla de 16x2 para mostrar el estado de los desvios
La v_1 las salidas y entradas se asocian a un pin digital de arduino y los servomotores a un expansor I2C PCA9685
La V_2.2 las asalidas y entradas digitales estan asociadas a un expansor de entradas analogicas I2c, un PCF8574
En la carpeta comprimida estan las librerias que funcionan con este codigo
