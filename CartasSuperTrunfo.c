#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//############################################################################################
//############################################################################################
//###                                                                                      ###
//### AVISO: Este código foi feito por um estudante que só usou python e Java a vida toda, ###
//### ou seja, está sendo sustendado por delírios e visões do além.                        ### 
//###                                                                                      ###
//############################################################################################
//############################################################################################
//###                                                                                      ###
//### OBS n°1: Esta linguagem de programação é definitivamente uma experiência, não é boa, ###
//### mas é, definitivamente, uma experiência.                                             ### 
//###                                                                                      ###
//### OBS n°2: Demorou 3 dias para eu perceber que poderia simplesmene usar variáveis      ###
//### em vez de espalhar ponteiros pelas funçoes                                           ### 
//###                                                                                      ###
//### OBS n°2 e meio: Nestes 3 dias meu hdd foi corrompido duas vezes                      ###
//###                                                                                      ###
//### OBS n°3: Dia 4, depois de finalmente fazer as cartas serem registradas e deixar o    ###
//### usuário ler as cartas, só faltam as funções de comparar e deletar as cartas.         ###
//###                                                                                      ###
//### OBS n°3 e meio: Não tenho certeza se deletar as cartas é necessário, não me lembro a ###
//### essa altura do campeonato, mas agrr já foi, quero deletar então vou deletar.         ###
//###                                                                                      ###
//### OBS n°4: Espero não ter que fazer outra abominação dessas, SENHOR eu só quero usar   ###
//### uma linguagem orientada a objetos que não reclame de ponteiro, o que que eu fiz pra  ###
//### merecer esta punição                                                                 ###
//###                                                                                      ###
//### OBS n°5: Chega de choradeira, n sou feito de gelo pra derreter fácil.                ###
//###                                                                                      ###
//###                                                                                      ###
//### OBS n°6: Se tiver dúvidas sobre a variável "balde", ela é um placeholder, nada demais###
//###                                                                                      ###
//############################################################################################
//############################################################################################




int quantidade_cartas = 0;
char escolha_char;
int escolha = 0;
int parar = 0;
int resposta_estranha = 0;
char balde[100];

// codigo cross plataforma pra limpar o terminal de comando
void Limpar() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void await(){
    getchar();
    fflush(stdin);
    getchar();
    fflush(stdin);
    return;
}

bool check_letra_maiuscula(char c) {
    return (c >= 'A' && c <= 'Z'); 
}

void menu_inicial();

//Pedir pra usar C foi maldade, linguagem estruturada tem q fazer isso
typedef struct Cidade {

    bool existe;

    char estado;
    char codigo_carta[4];
    char nome[51];
    unsigned long int pop;
    float area;
    float PIB;
    int n_pontos_turisticos;
    float densidade_pop;
    float pib_per_capta;
    float super_poder;

    void (*mostrar)(struct Cidade *self);
} Cidade;

Cidade Cidades[108];

int encontrar_index();

void mostrar_cidade(Cidade *self){
    printf("----------------------------------------");
    printf("\nCódigo da cidade: %s", self->codigo_carta);
    printf("\nNome da cidade: %s", self->nome);
    printf("\nEstado da cidade: %c", self->estado);
    printf("\nPopulação da cidade: %i", self->pop);
    printf("\nNúmero de pontos turísticos: %i", self->n_pontos_turisticos);
    printf("\nÁrea da cidade: %.2f KM²", self->area); 
    printf("\nDensidade populacional: %.2f Moradores / KM²", self->densidade_pop);
    printf("\nPIB: R$ %.2f", self->PIB);  
    printf("\nPIB per capta: R$ %.2f / Cidadão", self->pib_per_capta); 
    printf("\nSuper poder: %.2f", self->super_poder); 
    printf("\n----------------------------------------\n");
    return;
}


void comparar_cidade(Cidade cidade_1, Cidade cidade_2){
    printf("----------------------------------------");
    printf("\nCódigo da cidade: %s", cidade_1.codigo_carta);
    printf("\nNome da cidade: %s", cidade_1.nome);
    printf("\nEstado da cidade: %c", cidade_1.estado);
    printf("\nPopulação da cidade: %i -> %s", cidade_1.pop, (cidade_1.pop > cidade_2.pop) ? "Vence" : (cidade_1.pop == cidade_2.pop) ? "Empata" : "Perde");
    printf("\nNúmero de pontos turísticos: %i -> %s", cidade_1.n_pontos_turisticos, (cidade_1.n_pontos_turisticos > cidade_2.n_pontos_turisticos) ? "Vence" : (cidade_1.n_pontos_turisticos == cidade_2.n_pontos_turisticos) ? "Empata" : "Perde");
    printf("\nÁrea da cidade: %.2f KM² -> %s", cidade_1.area, (cidade_1.area > cidade_2.area) ? "Vence" : (cidade_1.area == cidade_2.area) ? "Empata" : "Perde"); 
    printf("\nDensidade populacional: %.2f Moradores / KM² -> %s", cidade_1.densidade_pop, (cidade_1.densidade_pop > cidade_2.densidade_pop) ? "Vence" : (cidade_1.densidade_pop == cidade_2.densidade_pop) ? "Empata" : "Perde");
    printf("\nPIB: R$ %.2f", cidade_1.PIB, (cidade_1.PIB > cidade_2.PIB) ? "Vence" : (cidade_1.PIB == cidade_2.PIB) ? "Empata" : "Perde");  
    printf("\nPIB per capta: R$ %.2f / Cidadão -> %s", cidade_1.pib_per_capta, (cidade_1.pib_per_capta > cidade_2.pib_per_capta) ? "Vence" : (cidade_1.pib_per_capta == cidade_2.pib_per_capta) ? "Empata" : "Perde"); 
    printf("\nSuper poder: %.2f -> %s", cidade_1.super_poder, (cidade_1.super_poder > cidade_2.super_poder) ? "Vence" : (cidade_1.super_poder == cidade_2.super_poder) ? "Empata" : "Perde"); 
    printf("\n----------------------------------------\n");
    return;
}

Cidade nova_cidade(char estado, char codigo_carta[], char nome[], unsigned long int pop, float area, float PIB, int n_pontos_turisticos) {
    float Supe;
    Supe =  pop + area + PIB + n_pontos_turisticos + (area / pop) + (PIB / pop);
    Cidade cidade = {true, estado, "", "", pop, area, PIB, n_pontos_turisticos, pop / area, PIB / pop, Supe};
    strncpy(cidade.codigo_carta, codigo_carta, 3);
    strncpy(cidade.nome, nome, 50);
    cidade.mostrar=mostrar_cidade;
    return cidade;
}

int cartas_total(){

    int tamanho = 108;
    int quantidade = 0;

    for (int i = 0; i < tamanho; i++) {
        if (Cidades[i].existe){
            quantidade ++;
        }
    }
    return quantidade;
}

int encontrar_index_vazio(){

    for (int i = 0; i < 108; i++) {
        if (Cidades[i].existe != true) { return i; }
    }

    return -1;
}

int encontrar_index(char cod[]){

    for (int i = 0; i < 108; i++) {
        if (strcmp(Cidades[i].codigo_carta, cod) == 0) { return i; }
    }

    return -1;
}

int cartas_por_estado(char estado){

    int tamanho = 108;
    int quantidade = 0;

    for (int i = 0; i < tamanho; i++) {
        if (Cidades[i].estado == toupper(estado)){
            quantidade++;
        }
        else if (Cidades[i].estado == '\0'){
            return quantidade;
        }
    }

    return quantidade;
}

void comparar_cartas(){
    Limpar();
    if (resposta_estranha == 1){
        printf("Resposta não reconhecida.\n\n");
        resposta_estranha = 0;
    }
    char resposta_c = '\0';
    int resposta = 0;
    
    int carta_1 = -2;
    int carta_2 = -2;

    if (cartas_total() < 2){
        printf("\n\nNão existem cartas suficientes para fazer uma comparação.\n\nPressione enter para retornar ao menu.");
        await();
        return;
    }
    while (isdigit(resposta_c) == 0){ 
        Limpar();
        printf("\n\nPara comparar cartas, primeiro selecione uma categoria.\n\n1-População da cidade\n2-Número de pontos turísticos\n3-Área da cidade\n4-Densidade populacional\n5-PIB\n6-PIB per capta\n7-Super poder\n8-Cancelar\n\nSua escolha: ");
        scanf("%c", &resposta_c);
    }

    fflush(stdin);
    resposta = atoi(&resposta_c);

    if (resposta == 0){
        fflush(stdin);
    }
    
    char carta_1_input[4] = "X00";
    char carta_2_input[4] = "X00";
    if(resposta != 8){
        while (carta_1 < 0){
            Limpar();
            printf("\n\nPara comparar cartas, primeiro selecione uma categoria.\n\n1-População da cidade\n2-Número de pontos turísticos\n3-Área da cidade\n4-Densidade populacional\n5-PIB\n6-PIB per capta\n7-Super poder\n8-Cancelar\n\nSua escolha: %i\n", resposta);
            if (carta_1 == -1){
                printf("\nCarta não encontrada!");
            }
            printf("\nCódigo da primeira carta: ('C' para cancelar)");
            scanf(" %s", &carta_1_input);
            carta_1 = encontrar_index(carta_1_input);
            if (strcmp(carta_1_input, "C\0\0\0") == 1){
                return;
            }
            fflush(stdin);
        }
        while (carta_2 < 0){
            Limpar();
            printf("\n\nPara comparar cartas, primeiro selecione uma categoria.\n\n1-População da cidade\n2-Número de pontos turísticos\n3-Área da cidade\n4-Densidade populacional\n5-PIB\n6-PIB per capta\n7-Super poder\n8-Cancelar\n\nSua escolha: %i\n", resposta);
            printf("\nCódigo da primeira carta: %s", carta_1_input);
            if (carta_2 == -1){
                printf("\nCarta não encontrada!");
            }
            printf("\nCódigo da segunda carta: ('C' para cancelar)");
            scanf(" %s", &carta_2_input);
            carta_2 = encontrar_index(carta_2_input);
            if (strcmp(carta_1_input, "C\0\0\0") == 1){
                return;
            }
            fflush(stdin);
        }

        Limpar();
        comparar_cidade(Cidades[carta_1], Cidades[carta_2]);
        printf("\nVS!!!");
        comparar_cidade(Cidades[carta_2], Cidades[carta_1]);
        printf("\n");
        
    }
    int cidade_vencedora = -1;
    switch (resposta) {
        case 1:
            cidade_vencedora = (Cidades[carta_1].pop > Cidades[carta_2].pop) ? carta_1 : carta_2;
            if (cidade_vencedora >= 0){
                printf("A cidade %s (%s) Vence na categoria escolhida! (População da cidade)", Cidades[cidade_vencedora].nome, Cidades[cidade_vencedora].codigo_carta);
            }else{
                printf("As cidades empataram na categoria escolhida. (População da cidade)");
            }
            break;
        case 2:
            cidade_vencedora = (Cidades[carta_1].n_pontos_turisticos > Cidades[carta_2].n_pontos_turisticos) ? carta_1 : carta_2;
            if (cidade_vencedora >= 0){
                printf("A cidade %s (%s) Vence na categoria escolhida! (Número de pontos turísticos)", Cidades[cidade_vencedora].nome, Cidades[cidade_vencedora].codigo_carta);
            }else{
                printf("As cidades empataram na categoria escolhida. (Número de pontos turísticos)");
            }
            break;
        case 3:
            cidade_vencedora = (Cidades[carta_1].area > Cidades[carta_2].area) ? carta_1 : carta_2;
            if (cidade_vencedora >= 0){
                printf("A cidade %s (%s) Vence na categoria escolhida! (Área da cidade)", Cidades[cidade_vencedora].nome, Cidades[cidade_vencedora].codigo_carta);
            }else{
                printf("As cidades empataram na categoria escolhida. (Área da cidade)");
            }
            break;
        case 4:
            cidade_vencedora = (Cidades[carta_1].densidade_pop < Cidades[carta_2].densidade_pop) ? carta_1 : carta_2;
            if (cidade_vencedora >= 0){
                printf("A cidade %s (%s) Vence na categoria escolhida! (Densidade populacional)", Cidades[cidade_vencedora].nome, Cidades[cidade_vencedora].codigo_carta);
            }else{
                printf("As cidades empataram na categoria escolhida. (Densidade populacional)");
            }
            break;
        case 5:
            cidade_vencedora = (Cidades[carta_1].PIB > Cidades[carta_2].PIB) ? carta_1 : carta_2;
            if (cidade_vencedora >= 0){
                printf("A cidade %s (%s) Vence na categoria escolhida! (PIB)", Cidades[cidade_vencedora].nome, Cidades[cidade_vencedora].codigo_carta);
            }else{
                printf("As cidades empataram na categoria escolhida. (PIB)");
            }
            break;
        case 6:
            cidade_vencedora = (Cidades[carta_1].pib_per_capta > Cidades[carta_2].pib_per_capta) ? carta_1 : carta_2;
            if (cidade_vencedora >= 0){
                printf("A cidade %s (%s) Vence na categoria escolhida! (PIB per capta)", Cidades[cidade_vencedora].nome, Cidades[cidade_vencedora].codigo_carta);
            }else{
                printf("As cidades empataram na categoria escolhida. (PIB per capta)");
            }
            break;
        case 7:
            cidade_vencedora = (Cidades[carta_1].super_poder > Cidades[carta_2].super_poder) ? carta_1 : carta_2;
            if (cidade_vencedora >= 0){
                printf("A cidade %s (%s) Vence na categoria escolhida! (Super poder)", Cidades[cidade_vencedora].nome, Cidades[cidade_vencedora].codigo_carta);
            }else{
                printf("As cidades empataram na categoria escolhida. (Super poder)");
            }
            break;
        case 8:
            return;
            break;
        default:
            resposta_estranha = 1;
            return;
    }
    printf("\n\nPressione enter para retornar ao menu.");
    await();
}

void cadastrar_cidade_passo2(){
    Limpar();
    if (resposta_estranha == 1){
        printf("Resposta não reconhecida.\n\n");
        resposta_estranha = 0;
    }

    char balde[100];
    char estado;
    char codigo_carta[4];
    char nome[51];
    unsigned long int pop;
    float area;
    float PIB;
    int n_pontos_turisticos;

    printf("\nQual o estado da sua cidade? (Uma letra de A-Z, 'CANCELAR' para cancelar): ");
    fflush(stdin); scanf(" %[^\n]", &balde);
    if (strcmp(balde,"CANCELAR")==0){
        return;
    }else if(!check_letra_maiuscula(toupper(balde[0]))){
        printf("O estado deve ser uma das letras do alfabeto. \n\nPressione qualquer teclar para retornar ao menu.");
        await();
        Limpar();
        return;
    }else{
        int cartas_no_estado = cartas_por_estado(toupper(balde[0]));
        if (cartas_no_estado > 3){
            printf("Este estado já tem o número máximo de cidades. \n\nPressione qualquer teclar para retornar ao menu.");
            await();
            Limpar();
            return;
        }
        estado = toupper(balde[0]);
        sprintf(codigo_carta, "%c%02d", estado, cartas_no_estado+1);
    }
    printf("\nQual o nome da sua cidade? ('CANCELAR' para cancelar): ");
    fflush(stdin); scanf(" %[^\n]", &balde);
    if (strcmp(balde,"CANCELAR")==0){
        return;
    }else{
        strncpy(nome, balde, 50);
    }
    printf("\nQual a população da sua cidade? ('CANCELAR' para cancelar): ");
    fflush(stdin); scanf(" %[^\n]", &balde);
    if (strcmp(balde,"CANCELAR")==0){
        return;
    }else if(atoi(balde) > 0){
        pop = atoi(balde);
    }else{
        printf("A população não pode ser menos de 1.\n\nPressione qualquer teclar para retornar ao menu inicial.");
        await();
        Limpar();
        return;
    }
    printf("\nQual a área (em KM²) da sua cidade? ('CANCELAR' para cancelar): ");
    fflush(stdin); scanf(" %[^\n]", &balde);
    if (strcmp(balde,"CANCELAR")==0){
        return;
    }else if(atoi(balde) > 0){
        area = atof(balde);
    }else{
        printf("A área não pode ser menos de 1.\n\nPressione qualquer teclar para retornar ao menu inicial.");
        await();
        Limpar();
        return;
    }
    printf("\nQual o PIB (Produto Interno Bruto, em R$) da sua cidade? ('CANCELAR' para cancelar): ");
    fflush(stdin); scanf(" %[^\n]", &balde);
    if (strcmp(balde,"CANCELAR")==0){
        return;
    }else if(atoi(balde) > 0){
        PIB = atof(balde);
    }else{
        printf("O PIB não pode ser menos de 1.\n\nPressione qualquer teclar para retornar ao menu inicial.");
        await();
        Limpar();
        return;
    }
    printf("\nQuantos pontos existem na sua cidade? ('CANCELAR' para cancelar): ");
    fflush(stdin); scanf(" %[^\n]", &balde);
    if (strcmp(balde,"CANCELAR")==0){
        return;
    }else if(atoi(balde) > 0){
        n_pontos_turisticos = atoi(balde);
    }else{
        printf("A cidade precisa de ao menos UM ponto turístico.\n\nPressione qualquer teclar para retornar ao menu inicial.");
        await();
        Limpar();
        return;
    }
    Limpar();
    Cidade temp = nova_cidade(estado, codigo_carta, nome, pop, area, PIB, n_pontos_turisticos);
    temp.mostrar(&temp);
    
    int dummy;
    printf("Cadastrar esta carta?\n\n1-Sim\n2-Não (Voltar ao menu inicial)\n\nSua resposta: ");
    int resposta;
    scanf("%d", &resposta);
    switch (resposta) {
        case 1:
            Cidades[encontrar_index_vazio()] = temp;
            break;
        case 2:
            Limpar();
            return;
        default:
            resposta_estranha = 1;
            Limpar();
            return;
    }
    printf("Cidade cadastrada! Pressione enter para retornar ao menu.\n");
    await();
    Limpar();
    return;
}

void cadastrar_cidade(){
    Limpar();
    if (resposta_estranha == 1){
        printf("Resposta não reconhecida.\n\n");
        resposta_estranha = 0;
    }
    char resposta_c = '\0';
    int resposta = 0;
    while (isdigit(resposta_c) == 0){
        Limpar();
        printf("\nCadastrar carta?\n\n1-Continuar\n2-Voltar\n\nSua escolha: ");
        scanf(" %c", &resposta_c);
    }
    resposta = atoi(&resposta_c);
    switch (resposta) {
        case 1:
            cadastrar_cidade_passo2(parar, Cidades, resposta_estranha);
            break;
        case 2:
            return;
        default:
            resposta_estranha = 1;
            return;
    }
}

void navegar_cartas(){
    if (cartas_total() > 0){
        int sair_lista = 0;
        int carta_atual = 0;
        int ate_carta = 0;
        while (sair_lista == 0){
            int vazios_pulados = 0;
            
            char resposta_c2 = '\0';
            int resposta2 = 0;
            while (isdigit(resposta_c2) == 0){ 
                Limpar();
                ate_carta = carta_atual + 2;
                if (ate_carta > cartas_total()){
                    ate_carta = cartas_total();
                }
                printf("Listando cartas, de %i até %i de %i \n\n", carta_atual+1, ate_carta, cartas_total());
                for (int i = carta_atual; i < ate_carta; i++) {
                    if (Cidades[i+vazios_pulados].existe){
                        Cidades[i+vazios_pulados].mostrar(&Cidades[i+vazios_pulados]);
                    }else{
                        vazios_pulados++;
                        i--;
                    }
                }
                printf("\n1-Retroceder 3 cartas\n2-Retroceder 1 carta\n3-Avançar 1 carta\n4-Avançar 3 cartas\n5-Voltar\n\nSua escolha: ");
                scanf(" %c", &resposta_c2);
            }
            resposta2 = atoi(&resposta_c2);
            switch (resposta2)
            {
                case 1:
                    carta_atual = carta_atual - 3;
                    if (carta_atual < 0){
                        carta_atual = 0;
                    }
                    break;
                case 2:
                    carta_atual = carta_atual - 1;
                    if (carta_atual < 0){
                        carta_atual = 0;
                    }
                    break;
                case 3:
                    carta_atual = carta_atual + 1;
                    if (carta_atual > cartas_total()){
                        carta_atual = cartas_total();
                    }
                    break;
                case 4:
                    carta_atual = carta_atual + 3;
                    if (carta_atual > cartas_total()){
                        carta_atual = cartas_total();
                    }
                    break;
                case 5:
                    sair_lista = 1;
                    break;
            default:
                break;
            }
        }
    }else{
        printf("Nenhuma carta para exibir, pressione enter para retornar. \n");
        await();
    }
}

void inspecionar(){
    printf("Informe o código da carta: ");
        char codigo[4];
        fflush(stdin); scanf(" %[^\n]", &codigo);
        if (encontrar_index(codigo) >= 0){
            Limpar();
            Cidades[encontrar_index(codigo)].mostrar(&Cidades[encontrar_index(codigo)]);
            printf("Pressione enter para retornar.\n\n");
        }else{
            printf("Cidade não encontrada! Pressione enter para retornar\n\n");
        }
        await();
        Limpar();
}

void remover_cidade(int index) {

    Cidades[index].existe = false;

    Cidades[index].estado = '\0';
    Cidades[index].codigo_carta[0] = '\0';
    Cidades[index].nome[0] = '\0';
    Cidades[index].pop = 0;
    Cidades[index].area = 0.0;
    Cidades[index].PIB = 0.0;
    Cidades[index].n_pontos_turisticos = 0;
    Cidades[index].densidade_pop = 0.0;
    Cidades[index].pib_per_capta = 0.0;
    Cidades[index].super_poder = 0.0;
}

void deletar_carta(){

    int carta_alvo_index = -2;

    char carta_alvo[4] = "X00";

    while (carta_alvo_index < 0){
        Limpar();
        printf("Deletando uma carta.");
        if (carta_alvo_index == -1){
            printf("\n\nCarta não encontrada!");
        }
        printf("\n\nEscolha uma carta para deletar e insira o código ('C' para deletar): ");
        scanf(" %s", &carta_alvo);
        carta_alvo_index = encontrar_index(carta_alvo);
        if (strcmp(carta_alvo, "C\0\0\0") == 1){
            return;
        }
        fflush(stdin);
    }

    

    char resposta_c = '\0';
    int resposta = 0;
    while (isdigit(resposta_c) == 0){ 
        Limpar();
        printf("\n");
        Cidades[carta_alvo_index].mostrar(&Cidades[carta_alvo_index]);
        printf("\n\nDeseja mesmo deletar esta cidade?\n\n1-Sim\n2-Não\n\nSua escolha: ");
        scanf(" %c", &resposta_c);
    }
    resposta = atoi(&resposta_c);
    if (resposta == 0){
        fflush(stdin);
    }
    switch (resposta) {
        case 1:
            remover_cidade(carta_alvo_index);
            break;
        case 2:
            return;
            break;
        default:
            resposta_estranha = 1;
    }
}

void menu_inicial(){
    Limpar();
    if (resposta_estranha == 1){
        printf("Resposta não reconhecida.\n\n");
        resposta_estranha = 0;
    }
    char resposta_c = '\0';
    int resposta = 0;
    while (isdigit(resposta_c) == 0){ 
        Limpar();
        printf("\nBem vindo ao super trunfo em C\n\nEscolha uma opção:\n\n1-Cadastrar uma carta\n2-Comparar duas cartas\n3-Inspecionar uma carta\n4-Listar cartas\n5-Deletar uma carta\n6-Sair\n\nSua escolha: ");
        scanf(" %c", &resposta_c);
    }
    resposta = atoi(&resposta_c);
    if (resposta == 0){
        fflush(stdin);
    }
    switch (resposta) {
        case 1:
            cadastrar_cidade();
            break;
        case 2:
            comparar_cartas();
            break;
        case 3:
            inspecionar();
            break;
        case 4:
            navegar_cartas();
            break;
        case 5:
            deletar_carta();
            break;
        case 6:
            parar = 1;
            break;
        default:
            resposta_estranha = 1;
    }
}

int main() {
    while (parar != 1){
        menu_inicial();
    }

    return 0;
}
