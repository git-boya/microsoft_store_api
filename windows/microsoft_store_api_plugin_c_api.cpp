#include "include/microsoft_store_api/microsoft_store_api_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "microsoft_store_api_plugin.h"

void MicrosoftStoreApiPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  microsoft_store_api::MicrosoftStoreApiPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
