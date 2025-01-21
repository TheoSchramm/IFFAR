import 'package:appfirebase/home_page.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:flutter/material.dart';
import 'services/firestore_service.dart';

class AlunoPage extends StatefulWidget {
  String? id;
  AlunoPage({this.id, super.key});

  @override
  State<AlunoPage> createState() => _AlunoPageState();
}

class _AlunoPageState extends State<AlunoPage> {
  TextEditingController _txtNome = TextEditingController();
  TextEditingController _txtClasse = TextEditingController();
  TextEditingController _txtIdade = TextEditingController();

  FirestoreService servico = FirestoreService();

  @override
  void initState() {
    if (widget.id != null) {
      servico.buscarPorID(widget.id!)!.then((dados) {
        _txtNome.text = dados['nome'];
        _txtClasse.text = dados['classe'];
        _txtIdade.text = dados['idade'].toString();
      });
    }

    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: Colors.blue[200],
      body: Center(
        child: Padding(
          padding: EdgeInsets.all(16),
          child: ConstrainedBox(
            constraints: BoxConstraints(maxWidth: 600),
            child: Card(
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(16),
              ),
              elevation: 4,
              child: Padding(
                padding: const EdgeInsets.all(16.0),
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Text(
                      'Registrar aluno',
                      style: TextStyle(
                        fontSize: 24,
                        fontWeight: FontWeight.bold,
                      ),
                    ),
                    Divider(),
                    TextFormField(
                      controller: _txtNome,
                      decoration: InputDecoration(
                        labelText: 'Nome do aluno:',
                      ),
                    ),
                    SizedBox(height: 16),
                    TextFormField(
                      controller: _txtClasse,
                      decoration: InputDecoration(
                        labelText: 'Classe:',
                      ),
                    ),
                    SizedBox(height: 16),
                    TextFormField(
                      controller: _txtIdade,
                      decoration: InputDecoration(
                        labelText: 'Idade (anos):',
                      ),
                    ),
                    SizedBox(height: 16),
                    Wrap(
                      spacing: 8,
                      runSpacing: 8,
                      children: [
                        ElevatedButton(
                          onPressed: () async {
                            try {
                              DocumentReference resposta = await servico.gravar(
                                widget.id.toString(),
                                _txtNome.text,
                                _txtClasse.text,
                                int.parse(_txtIdade.text),
                              );

                              if (resposta.id.isNotEmpty) {
                                ScaffoldMessenger.of(context).showSnackBar(
                                  SnackBar(content: Text('Salvo com sucesso!')),
                                );
                                Navigator.of(context).pushReplacement(
                                  MaterialPageRoute(builder: (_) => HomePage()),
                                );
                              }
                            } catch (e) {
                              ScaffoldMessenger.of(context).showSnackBar(
                                SnackBar(content: Text('$e')),
                              );
                            }
                          },
                          child: Text('Salvar'),
                        ),
                        ElevatedButton(
                          onPressed: () {
                            Navigator.of(context).pushReplacement(
                              MaterialPageRoute(builder: (_) => HomePage()),
                            );
                          },
                          child: Text('Cancelar'),
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
