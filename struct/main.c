#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int validEmail(char* email) {
    // Define a sequência de caracteres permitidos na string "email"
    const char* pattern = "^[a-zA-Z0-9]+([\\._]?[a-zA-Z0-9]+)*@[a-zA-Z0-9]+([\\.-]?[a-zA-Z0-9]+)*(\\.[a-zA-Z]{2,})+$";
    // Declara uma variavel do tipo "regex temporario"
    regex_t regex;
    // Compila e executa a comparação do regex
    int result = regcomp(&regex, pattern, REG_EXTENDED);
    result = regexec(&regex, email, 0, NULL, 0);
    // Libera da memória o regex temporario
    regfree(&regex);
    
    return (!result);
}

struct Contato {
    char nome[50];
    char tel[20];
    char end[100];
    char email[50];
    struct Contato* proximo;
}

struct Contato* searchContato(struct Contato* head, const char* tel) {
    // Percorre toda a lista encadeada em busca do Node com o mesmo valor da variável "tel"
    struct Contato* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->tel, tel) == 0) {
            return temp;
        }
        temp = temp->proximo;
    }
    return NULL;
}

int createContato(struct Contato** head, char t_nome[], char t_tel[], char t_end[], char t_email[]) {
    struct Contato* newContato = (struct Contato*)malloc(sizeof(struct Contato));

    strcpy(newContato->nome, t_nome);
    strcpy(newContato->tel, t_tel);
    strcpy(newContato->end, t_end);
    strcpy(newContato->email, t_email);
    newContato->proximo = NULL;
    
    if (validEmail(t_email)){
        // Caso a lista estja vazia, a Head se torna o novo contato
        if (*head == NULL) { *head = newContato ;} 
        else {
            // Percorre toda a lista encadeada em busca do último Node
            struct Contato* temp = *head;
            while (temp->proximo != NULL) {temp = temp->proximo ;}
            // Aloca o novo contato como o próximo contato do último Node da lista
            temp->proximo = newContato ;}
        return 1 ;}
    printf(">> Email invalido! \n");
    return 0 ;
}

void verLista(struct Contato* head) {
    struct Contato* temp = head;
    printf("\n===[ Contatos ]===\n");
    while (temp != NULL) {
        printf("Nome: %s\n", temp->nome);
        printf("Telefone: %s\n", temp->tel);
        printf("Endereço: %s\n", temp->end);
        printf("Email: %s\n", temp->email);
        printf("------------------------\n");
        temp = temp->proximo;
    }
}

int editCont(struct Contato* contato) {
    char t_nome[64];
    char t_tel[24];
    char t_end[128];
    char t_email[64];
    
    printf("\n===[ Editor ]===\n");
    
    printf(">> Digite o nome do contato: ");
    fgets(t_nome, sizeof(t_nome), stdin);
    
    printf(">> Digite o telefone do contato: ");
    fgets(t_tel, sizeof(t_tel), stdin);
    
    printf(">> Digite o endereço do contato: ");
    fgets(t_end, sizeof(t_end), stdin);
    
    printf(">> Digite o email do contato: ");
    fgets(t_email, sizeof(t_email), stdin);
    
    // Remoção dos caracteres de quebra de linha
    t_nome[strcspn(t_nome, "\n")] = '\0';
    t_tel[strcspn(t_tel, "\n")] = '\0';
    t_end[strcspn(t_end, "\n")] = '\0';
    t_email[strcspn(t_email, "\n")] = '\0';
    
    if (validEmail(t_email)){
        strcpy(contato->nome, t_nome);
        strcpy(contato->tel, t_tel);
        strcpy(contato->end, t_end);
        strcpy(contato->email, t_email);
        return 1;
    }
    printf(">> Email invalido! \n");
    return 0 ;

}

int delCont(struct Contato* contato, struct Contato** head) {
    // Caso o Contato passado por argumento seja a head da lista
    if (*head == contato) {
        *head = contato->proximo;
        free(contato);
        return 1;
    }

    // Procuro pelo node anterior ao Contato passado por argumento
    struct Contato* prev = *head;
    while (prev->proximo != NULL && prev->proximo != contato) { prev = prev->proximo ;}
    
    // Caso o node não seja encontrado
    if (prev->proximo == NULL) { return 0; }
    
    prev->proximo = contato->proximo;
    free(contato);
    return 1;
}

int main() {
    struct Contato* head = NULL;
    char option[64];
    
    while (1) {
        printf("===[ Menu ]===\n[1] Adicionar novo contato \n[2] Ver lista \n[3] Editar contato \n[4] Apagar contato \n[5] Sair \n>> ");
        fgets(option, sizeof(option), stdin);
        option[strcspn(option, "\n")] = '\0';

        if (!strcmp(option, "1")){
            char t_nome[64];
            char t_tel[24];
            char t_end[128];
            char t_email[64];
            
            printf(">> Digite o nome do contato: ");
            fgets(t_nome, sizeof(t_nome), stdin);
            
            printf(">> Digite o telefone do contato: ");
            fgets(t_tel, sizeof(t_tel), stdin);
            
            printf(">> Digite o endereço do contato: ");
            fgets(t_end, sizeof(t_end), stdin);
            
            printf(">> Digite o email do contato: ");
            fgets(t_email, sizeof(t_email), stdin);
            
            // Remoção dos caracteres de quebra de linha
            t_nome[strcspn(t_nome, "\n")] = '\0';
            t_tel[strcspn(t_tel, "\n")] = '\0';
            t_end[strcspn(t_end, "\n")] = '\0';
            t_email[strcspn(t_email, "\n")] = '\0';

            if (createContato(&head, t_nome, t_tel, t_end, t_email)) {printf(">> Contato criado com sucesso! \n") ;}
            else { printf(">> Houve um erro ao criar o contato! \n") ;}}
        
        else if (!strcmp(option, "2")){ 
            if (head == NULL) { printf(">> Adicione algum contato primeiro! \n") ;}
            else { verLista(head) ;}}
        
        else if (!strcmp(option, "3")){ 
            if (head == NULL){ printf(">> Adicione algum contato primeiro! \n") ;}
            else {
                char t_tel[24];
                
                printf(">> Insira o número do Contato: ");
                fgets(t_tel, sizeof(t_tel), stdin);
                
                t_tel[strcspn(t_tel, "\n")] = '\0';

                struct Contato* resultado = searchContato(head, t_tel);

                if (resultado == NULL) {printf(">> Contato não encontrado! \n") ;}
                else {
                    if (editCont(resultado)){ printf(">> Contato editado com sucesso! \n") ;}
                    else { printf(">> Houve um erro ao editar o contato! \n") ;}}
                }  
            }
        
        else if (!strcmp(option, "4")){ 
            if (head == NULL){ printf(">> Adicione algum contato primeiro! \n") ;}
            else {
                char t_tel[24];
                
                printf(">> Insira o número do Contato: ");
                fgets(t_tel, sizeof(t_tel), stdin);
                
                t_tel[strcspn(t_tel, "\n")] = '\0';
            
                struct Contato* resultado = searchContato(head, t_tel);
                
                if (resultado == NULL) {printf(">> Contato não encontrado! \n") ;}
                else {
                    if (delCont(resultado, &head)){ printf(">> Contato deletado com sucesso! \n") ;}
                    else { printf(">> Houve um erro ao deletar o contato! \n") ;}}
                }
            }
        
        else if (!strcmp(option, "5")){ printf(">> Até mais! \n"); break ;}
        
        else { printf(">> Erro! \n") ;}
        
        printf("\n");
    }

    // Percorre e libera toda a lista encadeada
    struct Contato* temp = head;
    while (temp != NULL) {
        struct Contato* currentContato = temp;
        temp = temp->proximo;
        free(currentContato);}

    return 0;
}