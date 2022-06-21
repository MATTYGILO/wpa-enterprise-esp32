// Include MicroPython API.
#include <string.h>
#include <WiFi.h>
#include "esp_wpa2.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/objstr.h"
#include "ecc/ecc.h"


// This is the function which will be called from Python as enterprise.encrypt_key(a, b).
STATIC mp_obj_t enterprise_connect(const mp_obj_t ssid, const mp_obj_t username, const mp_obj_t identity, const mp_obj_t password) {
    // Extract the ints from the micropython input objects.
//    #define SSID "eduroam"
//    #define WPA2_USERNAME "username@ed.ac.uk"
//    #define WPA2_IDENTITY WPA2_USERNAME
//    #define WPA2_PASSWORD "password"

    // Disconnect from wifi
    WiFi.disconnect(true);

    // Initialise wifi mode
    WiFi.mode(WIFI_STA);
    //    modespnetwork
    // Initialise serial
    Serial.begin(115200);
    delay(10);

    Serial.print("Trying to connect to ");
    Serial.println(SSID);

    // Set wpa2 details
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)WPA2_IDENTITY, strlen(WPA2_IDENTITY));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)WPA2_USERNAME, strlen(WPA2_USERNAME));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)WPA2_PASSWORD, strlen(WPA2_PASSWORD));

    // Set wpa2 wifi configuration to default settings
    esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT();

    // Set configuration settings to enable function
    esp_wifi_sta_wpa2_ent_enable(&config);

    // Connect to wifi
    WiFi.begin(SSID);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
      counter++;
      if(counter>=60){
        ESP.restart();
      }
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address set: ");
    Serial.println(WiFi.localIP());

}
// Define a Python reference to the function above.Tes
STATIC MP_DEFINE_CONST_FUN_OBJ_2(enterprise_connect_obj, enterprise_connect);

// Define all properties of the module.
// Table entries are key/value pairs of the attribute name (a string)
// and the MicroPython object reference.
// All identifiers and strings are written as MP_QSTR_xxx and will be
// optimized to word-sized integers by the build system (interned strings).
STATIC const mp_rom_map_elem_t example_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_enterprise) },
    { MP_ROM_QSTR(MP_QSTR_encrypt_key), MP_ROM_PTR(&enterprise_connect_obj) },
};

STATIC MP_DEFINE_CONST_DICT(example_module_globals, example_module_globals_table);

// Define module object.
const mp_obj_module_t example_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&example_module_globals,
};

// Register the module to make it available in Python.
// Note: the "1" in the third argument means this module is always enabled.
// This "1" can be optionally replaced with a macro like MODULE_enterprise_ENABLED
// which can then be used to conditionally enable this module.
MP_REGISTER_MODULE(MP_QSTR_enterprise, example_user_cmodule, 1);