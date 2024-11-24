#include "microsoft_store_api_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>
#include <winrt/Windows.Services.Store.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.ApplicationModel.h>

#include <memory>
#include <sstream>
using namespace winrt;
using namespace Windows::Services::Store;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;

namespace microsoft_store_api {

// static
void MicrosoftStoreApiPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "microsoft_store_api",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<MicrosoftStoreApiPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

MicrosoftStoreApiPlugin::MicrosoftStoreApiPlugin() {}

MicrosoftStoreApiPlugin::~MicrosoftStoreApiPlugin() {}

void MicrosoftStoreApiPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } 
  else if (method_call.method_name().compare("requestRateAndReviewApp") == 0) {
      try {
          StoreContext context = StoreContext::GetDefault();
          auto asyncOp = context.RequestRateAndReviewAppAsync();
          asyncOp.Completed(
              [](IAsyncOperation<StoreRateAndReviewResult> const& asyncInfo, AsyncStatus const& asyncStatus) {
                  if (asyncStatus == AsyncStatus::Completed) {
                      auto result = asyncInfo.GetResults();
                  }
                  else {
                  }
              });
          result->Success();
      }
      catch (...) {
          result->Error("Error", "Failed to rate and review app");
      }

  }
  else if (method_call.method_name().compare("getPackageFamilyName") == 0) {
      try {
          AppInfo appInfo = AppInfo::Current();
          winrt::hstring familyName = appInfo.PackageFamilyName();
          result->Success(flutter::EncodableValue(winrt::to_string(familyName)));
      }
      catch (...) {
          result->Error("Error", "Failed to get package family name.");
      }
  }
  else {
    result->NotImplemented();
  }
}

}  // namespace microsoft_store_api
