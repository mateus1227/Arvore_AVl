
#include "arvore.h"


int main() {

    tipoapontador raiz;
    tiporegistro x;
    int op = 1;

    inicializa(&raiz);

    while (op != 0) {
        printf("\n\t1 - Criar Arvore\n\t2 - Inserir\n\t3 - Retirar Registro\n\t4 - Imprimir Central\n\t5 - Imprimir Pre\n\t6 - Imprimir Pos\n\t0 - SAIR\n\n\t Sua opcao: ");
            scanf("%d", &op);
        switch (op) {
            case 1: inicializa(&raiz);
                break;
            case 2:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &x.valor);
                insereBalanceado(&raiz, x);
                break;
            case 3:
                printf("Informe o valor a ser retirado: ");
                scanf("%d", &x.valor);
                retira(&raiz, x);
                break;
            case 4:imprimircentral(&raiz);break;
            case 5:imprimirpre(&raiz);break;
            case 6:imprimirpos(&raiz);break;
        }
    }

    return 0;
}

    
    
