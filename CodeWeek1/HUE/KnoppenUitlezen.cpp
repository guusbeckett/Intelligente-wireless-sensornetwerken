/*
Udp NTP Client
Get the time from a Network Time Protocol (NTP) time server
Demonstrates use of UDP sendPacket and ReceivePacket
For more on NTP time servers and the messages needed to communicate with them,
see http://en.wikipedia.org/wiki/Network_Time_Protocol

created 4 Sep 2010
by Michael Margolis

modified 17 Sep 2010
by Tom Igoe

modified 4 feb 2015
by Guus Beckett, Jim van Abkoude & Julian West
This code is in the public domain.
*/
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>
// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] =
{
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
unsigned int localPort = 8888; // local port to listen for UDP packets
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets
const int button1 = 8;     // the number of the pushbutton pin
const int button2 = 7;     // the number of the pushbutton pin
void hue(int switcher)
{
    EthernetClient client;

    IPAddress server(192,168,1,2);

    if(client.connect(server,80))
    {
        client.println("PUT /api/newdeveloper/lights/4/state HTTP/1.1");
        // client.println("GET /api/newdeveloper/lights/4 HTTP/1.1");
        client.println("Host: 192.168.1.2"); 
        client.println("Connection: keep-alive"); 
        client.println("Content-Type:   text/plain; charset=UTF-8"); 
        if (switcher)
        {
            client.println("Content-Length: 11"); 
            client.println(""); 
            Serial.println("Sending ON:true");
            client.println("{\"on\":true}");
        }
        else 
        {
            client.println("Content-Length: 12"); 
            client.println(""); 
            Serial.println("Sending ON:false");
            client.println("{\"on\":false}");
        }
        client.println(""); 
        Serial.println("Klaar");
        while (!client.available())
        {
            delay(1);
        }
        while (client.available()) {
            char c = client.read();
            Serial.print(c);
        }
    }
    else
    {
        Serial.println("Can\'t connect");
    }
}
void setup()
{
    Serial.begin(9600);
    Serial.println("Starting up");
    // start Ethernet and UDP
    if (Ethernet.begin(mac) == 0)
    {
        Serial.println("Failed to configure Ethernet using DHCP");
        // no point in carrying on, so do nothing forevermore:
        for (;;);
    }
else
{

    Serial.print("Local IP: ");
    Serial.println(Ethernet.localIP());
    Serial.print("Subnet Mask: ");
    Serial.println(Ethernet.subnetMask());
    Serial.print("Gateway: ");
    Serial.println(Ethernet.gatewayIP());
    Serial.print("Primary DNS: ");
    Serial.println(Ethernet.dnsServerIP());
}
DNSClient client;
client.begin(Ethernet.dnsServerIP());
pinMode(button1, INPUT);  
pinMode(button2, INPUT);  

}
void loop()
{
    int onOffSwitch = -1;
    int buttonState1 = digitalRead(button1);
    int buttonState2 = digitalRead(button2);
    
    if (buttonState1 == HIGH) {     
    // turn LED on:    
        Serial.println("ON");
        onOffSwitch = 1;

    }
    if (buttonState2 == HIGH) {     
    // turn LED on:    
        Serial.println("OFF");
        onOffSwitch = 0;
    }
    // wait ten seconds before asking for the time again
    if (onOffSwitch!=-1)
    {
      /* code */
        hue(onOffSwitch);
    }
    delay(1000);
}









