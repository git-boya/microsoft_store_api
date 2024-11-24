import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'microsoft_store_api_method_channel.dart';

abstract class MicrosoftStoreApiPlatform extends PlatformInterface {
  /// Constructs a MicrosoftStoreApiPlatform.
  MicrosoftStoreApiPlatform() : super(token: _token);

  static final Object _token = Object();

  static MicrosoftStoreApiPlatform _instance = MethodChannelMicrosoftStoreApi();

  /// The default instance of [MicrosoftStoreApiPlatform] to use.
  ///
  /// Defaults to [MethodChannelMicrosoftStoreApi].
  static MicrosoftStoreApiPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [MicrosoftStoreApiPlatform] when
  /// they register themselves.
  static set instance(MicrosoftStoreApiPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }

  Future<void> requestRateAndReviewApp(){
    throw UnimplementedError('requestRateAndReviewApp() has not been implemented.');
  }

  Future<String?> getPackageFamilyName() {
    throw UnimplementedError('getPackageFamilyName() has not been implemented.');
  }

  Future getAppAndOptionalStorePackageUpdatesAsync() {
    throw UnimplementedError('getAppAndOptionalStorePackageUpdatesAsync() has not been implemented.');
  }
}
