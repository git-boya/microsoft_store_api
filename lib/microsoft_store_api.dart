
import 'microsoft_store_api_platform_interface.dart';

class MicrosoftStoreApi {
  /// review
  Future<void> requestRateAndReviewApp() {
    return MicrosoftStoreApiPlatform.instance.requestRateAndReviewApp();
  }

  Future<void> reviewInMicrosoftStore(String productId){
    return MicrosoftStoreApiPlatform.instance.reviewInMicrosoftStore(productId);
  }
  /// get PFN
  Future<String?> getPackageFamilyName() {
    return MicrosoftStoreApiPlatform.instance.getPackageFamilyName();
  }

  /// Gets the collection of packages for the current app that have updates
  /// available for download from the Microsoft Store,
  /// including optional packages for the app.
  Future getAppAndOptionalStorePackageUpdatesAsync() {
    return MicrosoftStoreApiPlatform.instance.getAppAndOptionalStorePackageUpdatesAsync();
  }
}
