import 'package:firebase_auth/firebase_auth.dart';

class UsuarioService {
  final FirebaseAuth _auth = FirebaseAuth.instance;

  Future<String> criarNovaConta(String nome, String email, String senha) async {
    try {
      UserCredential c = await _auth.createUserWithEmailAndPassword(
        email: email,
        password: senha,
      );
      c.user!.updateDisplayName(nome);
      return "";
    } on FirebaseAuthException catch (erro) {
      return erro.message!;
    } catch (e) {
      return "Ocorreu um erro. Tente novamente.";
    }
  }

  Future<String> login(String email, String senha) async {
    try {
      UserCredential user = await _auth.signInWithEmailAndPassword(
        email: email,
        password: senha,
      );
      return "";
    } on FirebaseAuthException catch (erro) {
      return erro.message!;
    }
  }
}
