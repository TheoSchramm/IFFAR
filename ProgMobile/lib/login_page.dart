import 'dart:io';

import 'package:appfirebase/home_page.dart';
import 'package:appfirebase/nova_conta_page.dart';
import 'package:appfirebase/services/usuario_service.dart';
import 'package:flutter/material.dart';

class LoginPage extends StatelessWidget {
  LoginPage({super.key});

  TextEditingController _txtEmail =
      new TextEditingController(text: 'example@mail.com');
  TextEditingController _txtSenha = new TextEditingController(text: '12345678');

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.blue[200],
      body: Center(
        child: Padding(
          padding: const EdgeInsets.all(16.0),
          child: Align(
            alignment: Alignment.center,
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
                        'Login',
                        style: TextStyle(
                          fontSize: 24,
                          fontWeight: FontWeight.bold,
                        ),
                      ),
                      Divider(),
                      TextFormField(
                        controller: _txtEmail,
                        decoration: InputDecoration(
                          labelText: 'Email:',
                        ),
                      ),
                      SizedBox(height: 16),
                      TextFormField(
                        controller: _txtSenha,
                        decoration: InputDecoration(
                          labelText: 'Senha:',
                        ),
                        obscureText: true,
                      ),
                      SizedBox(height: 16),
                      Wrap(
                        spacing: 8,
                        runSpacing: 8,
                        children: [
                          ElevatedButton(
                            onPressed: () async {
                              UsuarioService service = UsuarioService();
                              String resposta = await service.login(
                                  _txtEmail.text, _txtSenha.text);
                              if (resposta != '') {
                                SnackBar snackBar = SnackBar(
                                  content: Text(resposta),
                                );
                                ScaffoldMessenger.of(context)
                                    .showSnackBar(snackBar);
                              } else {
                                Navigator.of(context).push(MaterialPageRoute(
                                    builder: (_) => HomePage()));
                              }
                            },
                            child: Text('Login'),
                          ),
                          ElevatedButton(
                            onPressed: () {
                              Navigator.of(context).push(MaterialPageRoute(
                                  builder: (_) => NovaContaPage()));
                            },
                            child: Text('Criar nova Conta'),
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
      ),
    );
  }
}
