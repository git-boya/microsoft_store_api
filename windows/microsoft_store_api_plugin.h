#ifndef FLUTTER_PLUGIN_MICROSOFT_STORE_API_PLUGIN_H_
#define FLUTTER_PLUGIN_MICROSOFT_STORE_API_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace microsoft_store_api {

class MicrosoftStoreApiPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  MicrosoftStoreApiPlugin();

  virtual ~MicrosoftStoreApiPlugin();

  // Disallow copy and assign.
  MicrosoftStoreApiPlugin(const MicrosoftStoreApiPlugin&) = delete;
  MicrosoftStoreApiPlugin& operator=(const MicrosoftStoreApiPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace microsoft_store_api

#endif  // FLUTTER_PLUGIN_MICROSOFT_STORE_API_PLUGIN_H_
