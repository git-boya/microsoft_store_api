import 'package:flutter_test/flutter_test.dart';
import 'package:microsoft_store_api/microsoft_store_api.dart';
import 'package:microsoft_store_api/microsoft_store_api_platform_interface.dart';
import 'package:microsoft_store_api/microsoft_store_api_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockMicrosoftStoreApiPlatform
    with MockPlatformInterfaceMixin
    implements MicrosoftStoreApiPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final MicrosoftStoreApiPlatform initialPlatform = MicrosoftStoreApiPlatform.instance;

  test('$MethodChannelMicrosoftStoreApi is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelMicrosoftStoreApi>());
  });

  test('getPlatformVersion', () async {
    MicrosoftStoreApi microsoftStoreApiPlugin = MicrosoftStoreApi();
    MockMicrosoftStoreApiPlatform fakePlatform = MockMicrosoftStoreApiPlatform();
    MicrosoftStoreApiPlatform.instance = fakePlatform;

    expect(await microsoftStoreApiPlugin.getPlatformVersion(), '42');
  });
}
