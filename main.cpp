#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item{
    public:
        // Constructor
        Item( string nome_, string desc_, int quant_, string fornec_, float valor_ ){
            nome = nome_;
            desc = desc_;
            quant = quant_;
            fornec = fornec_;
            valor = valor_;
        };
        
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
        
    private:
        // Atts
        string nome;
        string desc;
        int quant;
        string fornec;
        float valor;
};

// O melhor seria uma DB/JSON ao invés dessa classe
class inventario{
    public:
        vector<Item*> arr;
        
        int IsNotEmpty(){
            if (!arr.size()){
                cout << ">> Registre algum produto primeiro!\n ";
                return 0;
            }
            return 1;
        }
        void listar(){
            if (IsNotEmpty()) {
                cout << "===[ Produtos ]===\n";
                for(int i = 0; i != arr.size(); i++)
                    cout << "[" << i+1 << "]" << arr[i]->getNome() << "\n";
                cout << "\n";
                
            }
        }
        
        void apagar(int index){
            if (IsNotEmpty()) {
                delete arr[index-1];
                arr.erase(arr.begin() + 1);
            }
        }
};
// Criação do inventário GLOBAL (Será referenciado na próxima função)
inventario inv;

// Essa função será descartada com a implementação do Front
void createObj(){
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

    try{
        // Tenta alocar no vetor o novo item
        inv.arr.push_back(new Item(nome, desc, stoi(quant), fornec, stof(valor)));
        cout << ">> Produto cadastrado com sucesso!.\n\n";
    }
    catch (exception& err){
        cout << ">> Não foi possível o cadastro do produto.\n\n";
    }
};

int main() {
    string option;
    while (1) {
        cout << "\n===[ Menu ]=== \n[1] Cadastrar produtos \n[2] Ver inventário \n[3] Deletar produto \n[4] Sair \n>> ";
        getline(cin, option);
        
        if (option == "1")
                createObj();
        else if (option == "2")
                inv.listar();
        else if (option == "3") {
                if (inv.IsNotEmpty()) {
                    string index;
                    cout << "Insira a posição do produto: ";
                    getline(cin, index);
                    try {
                        inv.apagar(stoi(index));
                        cout << ">> Produto apagado com sucesso!.\n\n";
                    }
                    catch (exception& err) {
                        cout << ">> Não foi possível apagar o produto.\n\n";
                    }
                }
        }
        else if (option == "4")
            break;
    }
  return 1;
}
