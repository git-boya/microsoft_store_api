import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'microsoft_store_api_platform_interface.dart';

/// An implementation of [MicrosoftStoreApiPlatform] that uses method channels.
class MethodChannelMicrosoftStoreApi extends MicrosoftStoreApiPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('microsoft_store_api');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }

  @override
  Future<void> requestRateAndReviewApp() async{
    await methodChannel.invokeMethod('requestRateAndReviewApp');
  }

  @override
  Future<String?> getPackageFamilyName() async{
    final familyName = await methodChannel.invokeMethod('getPackageFamilyName');
    return familyName;
  }

  @override
  Future getAppAndOptionalStorePackageUpdatesAsync() async{
    await methodChannel.invokeMethod('getAppAndOptionalStorePackageUpdatesAsync');
  }
}
