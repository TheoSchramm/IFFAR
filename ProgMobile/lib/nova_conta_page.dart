import 'package:appfirebase/home_page.dart';
import 'package:appfirebase/services/usuario_service.dart';
import 'package:flutter/material.dart';
import 'package:firebase_auth/firebase_auth.dart';

class NovaContaPage extends StatelessWidget {
  NovaContaPage({super.key});

  TextEditingController _txtNome = new TextEditingController();
  TextEditingController _txtEmail = new TextEditingController();
  TextEditingController _txtSenha = new TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.blue[200],
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: ConstrainedBox(
            constraints: BoxConstraints(maxWidth: 400),
            child: Card(
              elevation: 4,
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(16),
              ),
              child: Padding(
                padding: const EdgeInsets.all(16.0),
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Text(
                      'Criar Nova Conta',
                      style: TextStyle(
                        fontSize: 24,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    Divider(),
                    TextFormField(
                      controller: _txtNome,
                      decoration: InputDecoration(labelText: 'Nome:'),
                    ),
                    SizedBox(height: 16),
                    TextFormField(
                      controller: _txtEmail,
                      decoration: InputDecoration(labelText: 'Email:'),
                    ),
                    SizedBox(height: 16),
                    TextFormField(
                      controller: _txtSenha,
                      decoration: InputDecoration(labelText: 'Senha:'),
                    ),
                    SizedBox(height: 16),
                    Wrap(
                      spacing: 8,
                      runSpacing: 8,
                      children: [
                        ElevatedButton(
                          onPressed: () async {
                            try {
                              UsuarioService service = UsuarioService();
                              String resposta = await service.criarNovaConta(
                                  _txtNome.text,
                                  _txtEmail.text,
                                  _txtSenha.text);
                              if (resposta != '') {
                                ScaffoldMessenger.of(context).showSnackBar(
                                  SnackBar(content: Text(resposta)),
                                );
                              } else {
                                await service.login(
                                    _txtEmail.text, _txtSenha.text);
                                ScaffoldMessenger.of(context).showSnackBar(
                                  SnackBar(
                                      content:
                                          Text('Conta criada com sucesso!')),
                                );
                                Navigator.of(context).pushReplacement(
                                  MaterialPageRoute(builder: (_) => HomePage()),
                                );
                              }
                            } on FirebaseAuthException catch (e) {
                              ScaffoldMessenger.of(context).showSnackBar(
                                SnackBar(
                                    content: Text(e.message ??
                                        'Ocorreu um erro. Tente novamente.')),
                              );
                            }
                          },
                          child: Text('Cadastrar'),
                        ),
                        ElevatedButton(
                          onPressed: () {
                            Navigator.of(context).pop();
                          },
                          child: Text('Voltar'),
                        ),
                      ],
                    ),
                  ],
                ),
              ),
            ),
          ),
        ),
      ),
    );
  }
}
