import 'package:appfirebase/aluno_page.dart';
import 'package:appfirebase/services/firestore_service.dart';
import 'package:flutter/material.dart';
import 'camera_page.dart';
import 'dart:typed_data';

class HomePage extends StatelessWidget {
  const HomePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.blue[200],
      body: Center(
        child: Padding(
          padding: EdgeInsets.all(16),
          child: ConstrainedBox(
            constraints: BoxConstraints(maxWidth: 800),
            child: StreamBuilder(
              stream: FirestoreService().listar().snapshots(),
              builder: (context, snap) {
                if ((snap.connectionState == ConnectionState.waiting) ||
                    (!snap.hasData || snap.data!.docs.isEmpty)) {
                  return CircularProgressIndicator(
                    color: Colors.blue[200],
                    backgroundColor: Colors.white,
                  );
                }

                final dados = snap.data!.docs;
                return ListView.builder(
                  itemCount: dados.length,
                  itemBuilder: (context, indice) {
                    var aluno = dados[indice].data() as Map<String, dynamic>;
                    Uint8List? imageBytes;
                    if (aluno.containsKey('imageBytes') &&
                        aluno['imageBytes'] != null) {
                      imageBytes = Uint8List.fromList(
                          List<int>.from(aluno['imageBytes']));
                    }
                    return Card(
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(15),
                      ),
                      elevation: 4,
                      margin: EdgeInsets.symmetric(vertical: 10),
                      child: ListTile(
                        leading: CircleAvatar(
                          backgroundColor: Colors.blueGrey[200],
                          backgroundImage: imageBytes != null
                              ? MemoryImage(imageBytes)
                              : AssetImage('assets/images/default_pfp.png')
                                  as ImageProvider,
                        ),
                        title: Text(
                          "${aluno['nome'] ?? 'N/A'}, ${aluno['classe'] ?? 'N/A'}",
                          style: TextStyle(fontWeight: FontWeight.bold),
                        ),
                        subtitle: Text(
                            '${aluno['idade']?.toString() ?? 'N/A'} anos.'),
                        trailing: Row(
                          mainAxisSize: MainAxisSize.min,
                          children: [
                            IconButton(
                              onPressed: () {
                                String id = dados[indice].id;
                                Navigator.of(context).push(MaterialPageRoute(
                                  builder: (_) => AlunoPage(id: id),
                                ));
                              },
                              icon: Icon(Icons.edit, color: Colors.blue),
                            ),
                            IconButton(
                              onPressed: () {
                                showDialog(
                                  context: context,
                                  builder: (_) {
                                    return AlertDialog(
                                      title: Text('Excluir item'),
                                      content: Text(
                                        'Tem certeza que deseja apagar o aluno ${aluno['nome'] ?? 'N/A'}?',
                                      ),
                                      actions: [
                                        TextButton(
                                          onPressed: () {
                                            Navigator.pop(context);
                                          },
                                          child: Text('Cancelar'),
                                        ),
                                        TextButton(
                                          onPressed: () {
                                            FirestoreService()
                                                .excluir(dados[indice].id)
                                                .then((_) {
                                              Navigator.pop(context);
                                            });
                                          },
                                          child: Text('Apagar'),
                                        ),
                                      ],
                                    );
                                  },
                                );
                              },
                              icon: Icon(Icons.clear, color: Colors.red),
                            ),
                            IconButton(
                              onPressed: () {
                                Navigator.of(context).push(MaterialPageRoute(
                                  builder: (_) => CameraPage(
                                    alunoId: dados[indice].id,
                                    onImageCaptured: (imageBytes) {},
                                  ),
                                ));
                              },
                              icon: Icon(Icons.camera_alt, color: Colors.green),
                            ),
                          ],
                        ),
                      ),
                    );
                  },
                );
              },
            ),
          ),
        ),
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () {
          Navigator.of(context)
              .push(MaterialPageRoute(builder: (_) => AlunoPage()));
        },
        child: Icon(Icons.add),
        backgroundColor: Colors.white,
      ),
    );
  }
}
