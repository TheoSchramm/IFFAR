import 'dart:typed_data';
import 'package:camera/camera.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:appfirebase/services/firestore_service.dart';

class CameraPage extends StatefulWidget {
  final String alunoId;
  final Function(Uint8List) onImageCaptured;

  CameraPage({required this.alunoId, required this.onImageCaptured});

  @override
  _CameraPageState createState() => _CameraPageState();
}

class _CameraPageState extends State<CameraPage> {
  CameraController? controller;
  List<CameraDescription>? cameras;
  bool isCameraReady = false;

  @override
  void initState() {
    super.initState();
    SystemChrome.setPreferredOrientations([
      DeviceOrientation.portraitUp,
    ]);
    initCamera();
  }

  Future<void> initCamera() async {
    cameras = await availableCameras();
    controller = CameraController(cameras!.first, ResolutionPreset.low);
    await controller!.initialize();
    setState(() {
      isCameraReady = true;
    });
  }

  Future<void> takePicture() async {
    if (!controller!.value.isInitialized) {
      return;
    }
    try {
      final XFile file = await controller!.takePicture();
      final bytes = await file.readAsBytes();

      await FirestoreService().atualizarImagem(widget.alunoId, bytes);

      widget.onImageCaptured(bytes);
      Navigator.pop(context);
    } catch (e) {
      print('Erro ao tirar foto: $e');
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('Voltar')),
      body: isCameraReady
          ? Column(
              children: [
                Expanded(
                  child: Transform.rotate(
                    angle: 90 * 3.1415927 / 180,
                    child: AspectRatio(
                      aspectRatio: controller!.value.aspectRatio,
                      child: CameraPreview(controller!),
                    ),
                  ),
                ),
                ElevatedButton(
                  onPressed: takePicture,
                  child: Icon(Icons.camera_alt),
                ),
              ],
            )
          : Center(child: CircularProgressIndicator()),
    );
  }

  @override
  void dispose() {
    controller?.dispose();
    SystemChrome.setPreferredOrientations([
      DeviceOrientation.portraitUp,
      DeviceOrientation.portraitDown,
      DeviceOrientation.landscapeLeft,
      DeviceOrientation.landscapeRight,
    ]);
    super.dispose();
  }
}
