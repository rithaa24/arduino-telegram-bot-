#include "arduino_secrets.h"
#include <WiFi101.h>
#include <SPI.h>
#include <TelegramBot.h> 

// Initialize Wifi connection to the router
char ssid[] = SECRET_SSID;             // your network SSID (name)
char pass[] = SECRET_PASS;           // your network key

// Initialize Telegram BOT
const char BotToken[] = SECRET_BOT_TOKEN;

WiFiSSLClient client;
TelegramBot bot (BotToken, client);


void setup() {

  Serial.begin(115200);
  while (!Serial) {} // Wait for the Serial monitor to be opened
  delay(3000);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");

  bot.begin();
}

void loop() {

    message m = bot.getUpdates(); // Read new messages
    if ( m.chat_id != 0 ){ // Checks if there are some updates
      Serial.println(m.text);
      bot.sendMessage(m.chat_id, m.text);  // Reply to the same chat with the same text
    } else {
      Serial.println("no new message");
    }

}
