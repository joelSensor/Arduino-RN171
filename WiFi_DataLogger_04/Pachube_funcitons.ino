


void PUTdata(){
  
    String stuff = "Temperature,"+String(Celcius)+"."+String(Resolution)+"\nVoltage,"+milliVolts;
    WiFi.print("PUT /v2/feeds/"); 
    WiFi.print("53982");
    WiFi.println(".csv HTTP/1.1");
    WiFi.println("Host: api.pachube.com");
    WiFi.print("X-PachubeApiKey: ");
    WiFi.println("-UISjO3TGuiIqy0E1CJHcnmh3x-SAKxFYWpxOWdJUGNXYz0g");
    WiFi.println("User-Agent: Arduino (WiFi RN-171)");
    WiFi.print("Content-Type: text/csv\nContent-Length: ");
    WiFi.println(stuff.length());
    WiFi.println("Connection: close");
    WiFi.println();
    WiFi.println(stuff);

}
