#include <Arduino.h>
#include <gspserialresponse.h>
#include <gspflash.h>


void Areceived(String szParam) {
  Serial.println("A received : " + szParam);
}

void Breceived(String szParam) {
  Serial.println("B received : " + szParam);
}

//
// respond to two different string types:
//
// if the responder sees "=A######" where ###### is the  6 subsequent characters after the =A header,
// it will invoke the callback and send the received characters as a parameter.
//
// if the responder sees "=B###" where ### is the  3 subsequent characters after the =B header,
// it will invoke the callback and send the received characters as a parameter.
gspSerialResponse sr1("=A",6,Areceived);
gspSerialResponse sr2("=B",3,Breceived);


gspFlash led1(LED_BUILTIN);
gspSerialResponse sr3("=C",1,GSPFLASH_ONOFF_PARSER(led1)); //<- using helper macros for gspflash

/*

///////////////////////////////////////////

Received:

  =A123456

Response:

  A received : 123456

///////////////////////////////////////////

Received:

  =BABC

Response:

  B received : ABC

///////////////////////////////////////////

Received:
  =C0

Response:
  {LED Turns Off}

Received:
  =C1

Response:
  {LED Turns On}



*/

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  gspGrouped::register_instance(& sr1);  // <- do this for each instance
  gspGrouped::register_instance(& sr2);
  gspGrouped::register_instance(& sr3);
  gspGrouped::register_instance(& led1);
  
  gspFlash::startCheckAll();            // <- gspFlash is checked here. Once for all of them.

}

void loop() {
  // put your main code here, to run repeatedly:
  gspSerialResponse::checkAll(); // <- do this once for all instances.
}