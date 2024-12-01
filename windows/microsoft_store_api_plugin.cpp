#include "microsoft_store_api_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Services.Store.h>
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.UI.Core.h>


// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <ShObjIdl.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

using namespace winrt;
using namespace Windows::Services::Store;
//using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;
using namespace std;

// Helper function to convert wstring to string
std::string wstring_to_string(const std::wstring& wstr) {
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (len == 0) {
        throw std::runtime_error("Failed to convert wstring to string");
    }

    std::vector<char> buffer(len);
    if (WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &buffer[0], len, nullptr, nullptr) == 0) {
        throw std::runtime_error("Failed to convert wstring to string");
    }
    
    return std::string(&buffer[0]);
}

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
  
  HWND hWnd = registrar->GetView()->GetNativeWindow();
  StoreContext context = StoreContext::GetDefault();
  auto initWindow{
      context.as<IInitializeWithWindow>()
  };
  initWindow->Initialize(hWnd);
  registrar->AddPlugin(std::move(plugin));
}

MicrosoftStoreApiPlugin::MicrosoftStoreApiPlugin() {}

MicrosoftStoreApiPlugin::~MicrosoftStoreApiPlugin() {}

void MicrosoftStoreApiPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("requestRateAndReviewApp") == 0) {
      try {
          // Ensure this is called on the UI thread
          //CoreDispatcher dispatcher = CoreWindow::GetForCurrentThread().Dispatcher();
          
          CoreApplication::MainView().CoreWindow().Dispatcher().RunAsync(CoreDispatcherPriority::Normal,
              [result = std::move(result)]() mutable {
                  try {
                      StoreContext context = StoreContext::GetDefault();
                      Windows::Foundation::IAsyncOperation<StoreRateAndReviewResult> asyncOp = context.RequestRateAndReviewAppAsync();
                      asyncOp.Completed([](Windows::Foundation::IAsyncOperation<StoreRateAndReviewResult> const& asyncInfo, Windows::Foundation::AsyncStatus const& asyncStatus) {
                              if (asyncStatus == winrt::Windows::Foundation::AsyncStatus::Completed) {
                                  auto result = asyncInfo.GetResults();
                                  // Handle the result if necessary
                              }
                              else {
                                  // Handle the error or cancellation
                              }
                          });
                      result->Success();
                  }
                  catch (const winrt::hresult_error& ex) {
                      // Convert HRESULT to string
                      std::ostringstream oss;
                      oss << "HRESULT: 0x" << std::hex << ex.code();
                      std::string errorCode = oss.str();

                      // Convert hstring to std::string
                      std::wstring messageW = ex.message().c_str();
                      std::string errorMessage = wstring_to_string(messageW);

                      // Set the error
                      result->Error(errorCode, errorMessage);
                  }
                  catch (const std::exception& ex) {
                      result->Error("Error", ex.what());
                  }
              });
      }
      catch (const winrt::hresult_error& ex) {
          // Convert HRESULT to string
          std::ostringstream oss;
          oss << "HRESULT: 0x" << std::hex << ex.code();
          std::string errorCode = oss.str();

          // Convert hstring to std::string
          std::wstring messageW = ex.message().c_str();
          std::string errorMessage = wstring_to_string(messageW);

          // Set the error
          result->Error(errorCode, errorMessage);
      }
      catch (const std::exception& ex) {
          result->Error("Error", ex.what());
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
