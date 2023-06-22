#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

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

// A melhor opção seria utilizar uma DB ao invés de um simples vetor
class inventario {
public:
    vector<Item*> arr;

    // Retorna 1 caso o indice referenciado realmente exista
    int validIndex(int index) { return index > 0 && index <= arr.size() ;}

    int isEmpty() {
        if (!arr.size()) {
            cout << ">> Registre algum produto primeiro. \n\n";
            return 1 ;}
        return 0 ;}
    
    void listar() {
        if (!isEmpty()) {
            cout
                << "\n===[ " 
                << setw(15) << left << setfill(' ') << "ID" << " ]===[ "
                << setw(15) << left << setfill(' ') << "Produto" << " ]===[ "
                << setw(15) << left << setfill(' ') << "Descricao" << " ]===[ "
                << setw(15) << left << setfill(' ') << "Quantia" << " ]===[ "
                << setw(15) << left << setfill(' ') << "Fornecedor" << " ]===[ "
                << setw(15) << left << setfill(' ') << "Valor" << " ]===" << "\n";

            for (int i = 0; i != arr.size(); i++){
                    cout 
                        << "===[ " 
                        << setw(15) << left << setfill(' ') << i+1 << " ]===[ "
                        << setw(15) << left << setfill(' ') << arr[i]->getNome() << " ]===[ "
                        << setw(15) << left << setfill(' ') << arr[i]->getDesc() << " ]===[ "
                        << setw(15) << left << setfill(' ') << arr[i]->getQuant() << " ]===[ "
                        << setw(15) << left << setfill(' ') << arr[i]->getFornec() << " ]===[ "
                        << setw(15) << left << setfill(' ') << arr[i]->getValor() << " ]===";
            cout << "\n\n" ;}}}

    void apagar(int index) {
        if (!isEmpty()) {
            try {
                delete arr[index];
                arr.erase(arr.begin() + index);
                cout << ">> Produto apagado com sucesso. \n\n" ;}
            catch (exception& err) {
                cout << ">> Nao foi possivel apagar o produto. \n\n" ;}}}

};

// Criação do inventário GLOBAL (Onde serão guardado todos os Objs já criados)
inventario inv;

// Essa função usa o index pra saber se é pra criar um novo OBJ ou editar um já existente
void createObj(int index) {
    // É usado strings afim de evitar problemas com buffer
    string nome;
    string desc;
    string quant;
    string fornec;
    string valor;

    // DRY
    string menu_msg = (index > inv.arr.size()) ? "\n===[ Cadastro de Produto ]===\n" : "\n===[ Editor de Produto ]===\n";
    cout << menu_msg;

    // Todos esses inputs serão descartados com a implementação dos end-points da API
    cout << ">> Insira o nome do produto: ";
    getline(cin, nome);
    cout << ">> Insira a descricao do produto: ";
    getline(cin, desc);
    cout << ">> Insira a quantia do produto: ";
    getline(cin, quant);
    cout << ">> Insira o nome do fornecedor do produto: ";
    getline(cin, fornec);
    cout << ">> Insira o valor do produto: ";
    getline(cin, valor);

    // Novo item
    if (index > inv.arr.size()) {
        try {
            // Tenta alocar o novo item no vetor
            inv.arr.push_back(new Item(nome, desc, stoi(quant), fornec, stof(valor)));
            cout << ">> Produto cadastrado com sucesso.\n\n";
        }
        catch (exception& err) {
            cout << ">> Nao foi possivel o cadastro do produto.\n\n";
        }
    }

    // Editar item já existente
    else {
        try {
            // A implementação e utilização dos Setters torna muito mais fácil do que deletar o objeto já existente na memória e alocar um novo
            inv.arr[index]->setNome(nome);
            inv.arr[index]->setDesc(desc);
            inv.arr[index]->setQuant(stoi(quant));
            inv.arr[index]->setFornec(fornec);
            inv.arr[index]->setValor(stof(valor));
            cout << ">> Produto editado com sucesso.\n\n";
        }
        catch (exception& err) {
            cout << ">> Nao foi possivel editar o produto.\n\n";
        }
    };
};

// C++ Obj -> JSON Obj
void print_json() {
    json jsonData;
    for (const auto& Item : inv.arr) {
        json ItemJson;
        
        // Repare que se torna necessário o uso de Getters
        ItemJson["nome"] = Item->getNome();
        ItemJson["desc"] = Item->getDesc();
        ItemJson["quant"] = Item->getQuant();
        ItemJson["fornec"] = Item->getFornec();
        ItemJson["valor"] = Item->getValor();
        jsonData.push_back(ItemJson) ;}
    cout << "\n===[ Representacao do Arquivo JSON ]===\n" << jsonData.dump(4) << "\n\n";
};

int main() {
    string option;
    while (1) {
        cout << R"(===[ Menu ]===
[1] Cadastrar produtos
[2] Ver inventario
[3] Editar produto
[4] Deletar produto
[5] Encerrar execucao
>> )";
        getline(cin, option);

        if (option == "1") { createObj(inv.arr.size() + 1); }

        else if (option == "2") { inv.listar(); }

        else if (option == "3") {
            if (!inv.isEmpty()) {
                string index;
                cout << ">> Insira o ID do produto a ser editado: ";
                getline(cin, index);

                if (inv.validIndex(stoi(index))) {
                    createObj(stoi(index) - 1) ;}
                else {
                    cout << ">> Produto nao encontrado.\n\n" ;}}
        }

        else if (option == "4") {
            if (!inv.isEmpty()) {
                string index;
                cout << ">> Insira o ID do produto a ser apagado: ";
                getline(cin, index);

                if (inv.validIndex(stoi(index))) {
                        inv.apagar(stoi(index) - 1) ;}
                else {
                    cout << ">> Produto nao encontrado. \n\n" ;}}
        }

        else if (option == "5") { break ;}

        else if (option == "6") { print_json() ;}

        else { cout << "\n" ;}
    }
    return 1;
}
