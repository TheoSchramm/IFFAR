#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item {
private:
    // Atts
    string nome;
    string desc;
    int quant;
    string fornec;
    float valor;

public:
    // Constructor
    Item(string nome_, string desc_, int quant_, string fornec_, float valor_) :
        nome(nome_), desc(desc_), quant(quant_), fornec(fornec_), valor(valor_) {};

    // Getters
    string getNome() const { return nome; };
    string getDesc() const { return desc; };
    int getQuant() const { return quant; };
    string getFornec() const { return fornec; };
    float getValor() const { return valor; };

    // Setters
    void setNome(string i) { nome = i; };
    void setDesc(string i) { desc = i; };
    void setQuant(int i) { quant = i; };
    void setFornec(string i) { fornec = i; };
    void setValor(float i) { valor = i; };
};

// O melhor seria um DB ao invés dessa classe
class inventario {
public:
    vector<Item*> arr;

    int IsNotEmpty() {
        if (!arr.size()) {
            cout << ">> Registre algum produto primeiro!\n ";
            return 0;
        }
        return 1;
    }
    void listar() {
        if (IsNotEmpty()) {
            cout << "===[ Produtos ]===\n";
            for (int i = 0; i != arr.size(); i++)
                cout << "[" << i + 1 << "]" << arr[i]->getNome() << "\n";
            cout << "\n";

        }
    }

    void apagar(int index) {
        if (IsNotEmpty()) {
            delete arr[index - 1];
            arr.erase(arr.begin() + index - 1);
        }
    }
};
// Criação do inventário GLOBAL (Onde será guardado todos os Objs já criados)
inventario inv;

// Usa o int index pra saber se é pra criar um novo OBJ (Comparando com a quantia de elementos no vetor) ou editar um já existente
void createObj(int index) {
    // Essa parte da função será descartada com a implementação do input via Front
    // Usei strings para poder usar o "getline" afim de evitar problemas de buffer
    string nome;
    string desc;
    string quant;
    string fornec;
    string valor;

    cout << "===[ Cadastro de Produto ]===\n";
    cout << ">> Insira o nome do produto: ";
    getline(cin, nome);

    cout << ">> Insira a descrição do produto: ";
    getline(cin, desc);

    cout << ">> Insira a quantia do produto: ";
    getline(cin, quant);

    cout << ">> Insira o nome do fornecedor do produto: ";
    getline(cin, fornec);

    cout << ">> Insira o valor do produto: ";
    getline(cin, valor);

    // New entry
    if (index == inv.arr.size()) {
        try {
            // Tenta alocar no vetor o novo item
            inv.arr.push_back(new Item(nome, desc, stoi(quant), fornec, stof(valor)));
            cout << ">> Produto cadastrado com sucesso!.\n\n";
        }
        catch (exception& err) {
            cout << ">> Não foi possível o cadastro do produto.\n\n";
        }
    }

    // Edit entry
    else {
        // Index vem com +1 para caso de só ter 1 obj no vetor
        index -= 1;
        try {
            inv.arr[index - 1]->setNome(nome);
            inv.arr[index - 1]->setDesc(desc);
            inv.arr[index - 1]->setQuant(stoi(quant));
            inv.arr[index - 1]->setFornec(fornec);
            inv.arr[index - 1]->setValor(stof(valor));
        }
        catch (exception& err) {
            cout << ">> Não foi possível a mudança de produto.\n\n";
        }
    };
};

int main() {
    string option;
    while (1) {
        cout << R"(
        ===[ Menu ]===
        [1] Cadastrar produtos
        [2] Ver inventário
        [3] Editar produto
        [4] Deletar produto
        [5] Sair
        >> )";
        getline(cin, option);

        if (option == "1")
            createObj(inv.arr.size());

        else if (option == "2")
            inv.listar();

        else if (option == "3") {
            if (inv.IsNotEmpty()) {
                string index;
                cout << ">> Insira a posição do produto: ";
                getline(cin, index);

                if (stoi(index) >= 0 && stoi(index) <= inv.arr.size()) {
                    createObj(stoi(index) + 1);
                }
                else {
                    cout << ">> Produto não encontrado.\n\n";
                }
            }
        }

        else if (option == "4") {
            if (inv.IsNotEmpty()) {
                string index;
                cout << ">> Insira a posição do produto: ";
                getline(cin, index);

                if (stoi(index) >= 0 && stoi(index) <= inv.arr.size()) {
                    try {
                        inv.apagar(stoi(index));
                        cout << ">> Produto apagado com sucesso!.\n\n";
                    }
                    catch (exception& err) {
                        cout << ">> Não foi possível apagar o produto.\n\n";
                    }
                }
                else {
                    cout << ">> Procuto não encontrado. \n\n";
                }
            }
        }

        else if (option == "5") {
            break;
        }
    }
    return 1;
}
