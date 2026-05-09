#include <sys/_stdint.h>
#include <esp_mac.h>
#include <esp_wifi.h>

#include "user_wifi.h"
#include "gui_paint.h"

// Function to initialize WiFi in station mode
void wifi_ap_init(const char *ssid, const char *pwd) {

  WiFi.softAP(ssid, pwd);
  Serial.println("Hotspot Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  // 打印热点的 IP 地址

}

uint8_t wifi_ap_StationNum()
{
  return WiFi.softAPgetStationNum();  
}

void wifi_ap_StationMac(char *mac, uint8_t num)
{
  static wifi_sta_list_t sta_list;  // List to hold connected stations' information

  esp_wifi_ap_get_sta_list(&sta_list);

  wifi_sta_info_t sta_info = sta_list.sta[num];

  // Format the MAC address and display it in the list
  snprintf(mac, MAC_Addr_length, MACSTR, MAC2STR(sta_info.mac));
}