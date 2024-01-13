# HalloCamSp32
Proyecto Hallo Cam Camaras Automatas

Este proyecto hace uso de un SP32 de arduino version 4 en la seleccion de tarjetas en el IDE ARDUINO VER 2.2.1 seleccionar DOIT ESP32 DEVKIT V1
la aplicacion esta diseñada para enviar comandos por medio del metodo POST y GET el cual es cifrado, todo esto se basa en la web interna que lanza el ESP32, 
la APP solo hace uso de la pagina y cada boton envia el numero del agunlo que se requiere mover, en el codigo del sp32 se usan las funciones de paneo y de angulos
para mover el servo principal a ese angulo y un segundo servo para mover un servo motor que mueve el boton de zoom en agulos segun se requiere para que la camara de
un zoom acia adelante o en retroceso, toda la comunicacion se realiza via wifi los datos de red del SSId puede ser cambiados a conveniencia y en la app el url 
es la ip del ESP32 el cual se puede visualizar en Monitor Serie del IDE, ejemplo http://ip y si quiere probar un movimiento solo ingresa a la misma red con o sin 
internet , despues pone la web http:// ip y seguido ingresa /angulo o que es igual /170 podria ser tambine /120 etc.
