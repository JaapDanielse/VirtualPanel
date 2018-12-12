void setup() 
{
  // put your setup code here, to run once:

  float test = 123.456;
  char outstr[10];

  dtostrf(test,0,1,outstr);
  int i=0;
 // while (outstr[i]==' ') outstr[i++]='0';


  Serial.begin(115200);
  
  Serial.print(">");
  Serial.print(outstr);
  Serial.println("<");


}

void loop() {
  // put your main code here, to run repeatedly:

}
