#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "LgRad";
const char* password = "Casa de Oracion 2024";
int backupAngulo = 0; 
int nuevoAngulo = 0;
int tiempo=150;

WiFiServer server(80);

int ledRojo =32;
int  pinServo = 25;
int pinServoZoom=33;

Servo myServo;
Servo ServoZoom;

void setup() {
  Serial.begin(115200);
  pinMode(ledRojo, OUTPUT);
  myServo.attach(pinServo, 500, 2500);
  ServoZoom.attach(pinServoZoom, 500, 2500);//Servo Zoom

  connectWiFi();
  backupAngulo=0; 
  nuevoAngulo =0;

  ServoZoom.write(90);
}
/***************************************************
* Connecting to a WiFi network
****************************************************/
void connectWiFi(void)
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    //Serial.print(".");
    Serial.print("Buscando Wifi ...");
    
    delay(100);
    
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}
/***************************************************
* Paneos
****************************************************/
void paneosGeneral(int x) {
  digitalWrite(ledRojo, HIGH);
  if (x == 1) { // Cambié el = por == para comparación en lugar de asignación
    /* paneo numero uno de cero a 180*/
    for (size_t i = 5; i <= 175; i++) {
      myServo.write(i);
      delay(tiempo);
    }
  } else if (x == 2) { // Cambié el = por == para comparación en lugar de asignación
    /* paneo dos de 180 a cero */
    for (size_t i = 175; i >= 5; i--) {
      myServo.write(i);
      delay(tiempo);
    }
  }
  digitalWrite(ledRojo, LOW);
}
/***************************************************
* Angulos
****************************************************/
void movimientoEntreAngulos(int anguloAntiguo, int anguloNuevo) {
  if (anguloAntiguo == 50 || anguloAntiguo == 55 || anguloAntiguo == 100 || anguloAntiguo == 105 || anguloAntiguo == 150 || anguloAntiguo == 155) {
    anguloAntiguo = anguloNuevo;
  }
  digitalWrite(ledRojo, HIGH);

  Serial.println("inicio funcion ");
 if (anguloAntiguo == anguloNuevo) {
  Serial.println("Los angulops son iguales");


 }
 if (anguloAntiguo < anguloNuevo ){
  Serial.println("Movimendo de menor a mayor ");
  for (size_t i = anguloAntiguo; i <= anguloNuevo; i ++) {

    myServo.write(i);
    delay(tiempo);

    }   

    backupAngulo=anguloNuevo;
    
   
    Serial.print("fin movimiento");
  

    

  }
  if(anguloAntiguo > anguloNuevo ){

    Serial.println("El angulo es mayor ");
    for (size_t i = anguloAntiguo; i >= anguloNuevo; i --) {
    myServo.write(i);
    delay(tiempo);
    }

    backupAngulo=anguloNuevo;
    Serial.println("fin movimeinto ");


  }
  digitalWrite(ledRojo, LOW);
  Serial.println("fin de función ");
  
}
void loop() {
    WiFiClient client = server.available();
    // Encender el LED
    
    if (client) {
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        // Respuesta HTTP
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        // Contenido HTML
                        client.print("<html><body>");
                        client.print("<h1>Bienvenido Ingeniero Eliasib</h1></br>");
                        client.print("<h1>Software control camara 1</h1></br>");
                        client.print("</br>");
                        client.print("<a href=\"/ZIN\"><h1> ZOOM Menos</h1></a></br>");
                        client.print("<a href=\"/ZOUT\"><h1> ZOOM Mas</h1></a></br>");
                        client.print("<a href=\"/170\"><h1> 170 Grados</h1></a></br>");
                        client.print("<a href=\"/5\"><h1> 5 Grados</h1></a></br>");
                        client.print("</body></html>");

                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }

                // Manejo de comandos
                if (currentLine.endsWith("GET /ZOUT")) {
                    
                    ServoZoom.write(115);
                    delay(300);
                    ServoZoom.write(90);                                     
                    
                } else if (currentLine.endsWith("GET /ZIN")) {
                    
                    ServoZoom.write(55);
                    delay(300);
                    ServoZoom.write(90);                
                    
                } else if (currentLine.endsWith("GET /PANEO1")) {
                    
                    paneosGeneral(1);              
                    
                } else if (currentLine.endsWith("GET /PANEO2")) {
                    
                    paneosGeneral(2);                 
                    
                } else if (currentLine.endsWith("GET /175")) {
                    
                    nuevoAngulo =175;
                    
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /170")) {
    
                    
                    nuevoAngulo =170;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
      
                    
                  }
                else if (currentLine.endsWith("GET /165")) {
                    
                    nuevoAngulo =165;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /160")) {
                    
                    nuevoAngulo =160;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /155")) {
                    
                    nuevoAngulo =155;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /150")) {
                    
                    nuevoAngulo =150;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /145")) {
                    
                    nuevoAngulo =145;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /140")) {
                    
                    nuevoAngulo =140;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /135")) {
                    
                    nuevoAngulo =135;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /130")) {
                    
                    nuevoAngulo =130;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /125")) {
                    
                    nuevoAngulo =125;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /120")) {
                    
                    nuevoAngulo =120;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /115")) {
                     
                    nuevoAngulo =115;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /110")) {
                    
                    nuevoAngulo =110;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /105")) {
                    
                    nuevoAngulo =105;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /100")) {
                    
 		    
                    nuevoAngulo =100;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
          
                    
                }
                else if (currentLine.endsWith("GET /95")) {
                    
                    nuevoAngulo =95;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /90")) {
                    
                    nuevoAngulo =90;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /85")) {
                    
                    nuevoAngulo =85;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /80")) {
                    
                    nuevoAngulo =80;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /75")) {
                    
                    nuevoAngulo =75;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /70")) {
                    
                    nuevoAngulo =70;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /65")) {
                    
                    nuevoAngulo =65;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /60")) {
                    
                    nuevoAngulo =60;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /55")) {
                    
                    nuevoAngulo =55;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /50")) {
                    
                    nuevoAngulo =50;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /45")) {
                    
                    nuevoAngulo =45;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /40")) {
                    
                    nuevoAngulo =40;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /35")) {
                    
                    nuevoAngulo =35;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /30")) {
                    
                    nuevoAngulo =30;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /25")) {
                    
                    nuevoAngulo =25;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /20")) {
                    
                    nuevoAngulo =20;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /15")) {
                    
                    nuevoAngulo =15;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /10")) {
                    
                    nuevoAngulo =10;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
                else if (currentLine.endsWith("GET /5")) {
                    
                    nuevoAngulo =5;
                    movimientoEntreAngulos(backupAngulo, nuevoAngulo) ;
                    
                }
        
            }
        }
        client.stop();
    }
}
