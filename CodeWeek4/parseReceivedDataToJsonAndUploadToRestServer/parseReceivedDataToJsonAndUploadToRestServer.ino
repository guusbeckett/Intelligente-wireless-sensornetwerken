#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>
#include <SPI.h>
#include "XBee1.h"

int incomingByte = 0;
// char buffer[20]; deprecated
String buffer = "";
const int dezeMeetopstelling = 1;
//178.62.191.231
IPAddress restServer(178, 62, 191, 231); //Backup
String restServerString = "178.62.191.231";
String restServerPort   = "8080";
byte mac[] =
{
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
XBee* bee;
ZBRxResponse response = ZBRxResponse();



void setup() {
	Serial.begin(9600);
	Serial.println("Programme started");
	if (Ethernet.begin(mac) == 0)
	{
		Serial.println("Failed to configure Ethernet using DHCP");
        // no point in carrying on, so do nothing forevermore:
        for (;;);
    }
    else
    {
    	Serial.print("Eth info \n Local IP: ");
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
    if (client.getHostByName("zaku2.com", restServer) == 1)
    {
    	Serial.print("resolved server to ");
    	Serial.print(restServer);
    }
    else
    {
    	Serial.print("Unable to resolve IP, using default: ");
    	Serial.println(restServer);
    }
    bee = new XBee();
    bee->begin(9600);
}

void send_pack(int number)
{
	Serial.println("send_pack");
	int contentLength;

	EthernetClient client;

	String jsonBody = String("{ \"meetopstellingen\": \""+String(dezeMeetopstelling)+"\","
	//+"\"timestamp\": "+time.year()+"-"+time.month()+"-"+time.day()+" "+time.hour()+":"+time.minute()+":"+time.second() +"\","
	+"\"waarde\": \"" + String(number)+"\"}");

	if(client.connect(restServer,8080))
	{
		client.print("POST /iws/data HTTP/1.1");
        // client.println("GET /api/newdeveloper/lights/4 HTTP/1.1");
        client.print("Host: ");
        client.print(String(restServerString+":"+restServerPort));
        client.print("Connection: keep-alive"); 
        client.print("Content-Type:   application/json; charset=UTF-8"); 
        client.print("Content-Length: "); 
        client.print(jsonBody.length());
        client.print(""); 
        client.print(jsonBody);
        client.print(""); 

        Serial.print("Sent package with body");
        Serial.print(jsonBody);       
        Serial.print(" and length ");
        Serial.println(jsonBody.length());

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

void loop() {
  bee->readPacket();

  if (bee->getResponse().isAvailable()) {
    bee->getResponse().getZBRxResponse(response);
    uint8_t offset = response.getDataOffset();
    int id = response.getData(offset-5)*1000 + response.getData(offset-4)*100 + response.getData(offset-3)*10 + response.getData(offset-2);
    int temp = response.getData(offset);
    Serial.println(id);
    send_pack(temp);
    //Serial.println(*payload);
  }
	// char index = 0; deprecated

	//while (Serial.available() > 0) 
	//{
        // read the incoming byte:
        //if(Serial.available() > 0)
        //buffer.concat(Serial.read());
    //}
    /*if(buffer.length()!=0)
    {
    	Serial.println("Ontvangen:");
    	Serial.println(buffer);
    	send_pack(buffer.toInt()); //Does this work? It should!
		// int i = 0; while (i<21){buffer[i++]=0;} //clearing the bufffer
		buffer = ""; //clearing the buffer
		// index = 0; deprecated 
	}

	delay(1000);
  }*/
  delay(1000);
}
