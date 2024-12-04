import 'package:flutter/material.dart';
import 'dart:async';

import 'package:flutter/services.dart';
import 'package:microsoft_store_api/microsoft_store_api.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  String _platformVersion = 'Unknown';
  final _microsoftStoreApiPlugin = MicrosoftStoreApi();

  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: Column(
            mainAxisSize: MainAxisSize.min,
            children: [
              Text('Running on: $_platformVersion\n'),
              ElevatedButton(onPressed: (){
                _microsoftStoreApiPlugin.requestRateAndReviewApp();
              }, child: Text("Review")),
              ElevatedButton(onPressed: (){
                _microsoftStoreApiPlugin.reviewInMicrosoftStore("9PM2LNL0RFBK");
              }, child: Text("ReviewInStore")),

              ElevatedButton(onPressed: (){
                _microsoftStoreApiPlugin.getPackageFamilyName().then((value){
                  print("PFN:$value");
                });
              }, child: Text("packageFamilyName")),
            ],
          ),
        ),
      ),
    );
  }
}
