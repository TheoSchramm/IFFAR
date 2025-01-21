import 'package:cloud_firestore/cloud_firestore.dart';
import 'dart:typed_data';

class FirestoreService {
  final _firestore = FirebaseFirestore.instance;

  gravar(String id, String nome, String classe, int idade) {
    if (id != 'null') {
      final documentRef = _firestore.collection('alunos').doc(id);
      documentRef.update({
        'nome': nome,
        'classe': classe,
        'idade': idade,
      });

      return documentRef;
    } else {
      return _firestore.collection('alunos').add({
        'nome': nome,
        'classe': classe,
        'idade': idade,
        'imageBytes': null,
      });
    }
  }

  CollectionReference listar() {
    return _firestore.collection('alunos');
  }

  Future<void> excluir(String id) {
    final documentRef = _firestore.collection('alunos').doc(id);
    return documentRef.delete();
  }

  Future<DocumentSnapshot<Map<String, dynamic>>>? buscarPorID(String id) {
    return _firestore.collection('alunos').doc(id).get();
  }

  Future<void> atualizarImagem(String id, Uint8List imageBytes) {
    final documentRef = _firestore.collection('alunos').doc(id);
    return documentRef.update({'imageBytes': imageBytes});
  }
}
