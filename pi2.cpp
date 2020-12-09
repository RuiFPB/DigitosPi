/****************************************/
/* Computar os dígitos de pi            */
/* Baseado no programa original de      */
/* Roy Williams (1994), traduzido para  */
/* c++ por Rui Barbosa, Dezembro 2020   */
/* Utiliza a fórmula de Machin          */
/* pi/4 = 4 arctan(1/5) - arctan(1/239) */
/****************************************/
/* Executar como ./pi2 <n>              */
/* Sendo n o número de dígitos          */
/* Compilado com g++                    */
/****************************************/
/* Os últimos dígitos estão errados...  */
/****************************************/

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#include "pi2.h"

#define BASE 10000

long nblock;
long *tot;
long *t1;
long *t2;
long *t3;

int main(int argc, char **argv){
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif

    unsigned int ndigit = 60;   // número de dígitos

    // Verifica se foi dado um argumento na execução
    if(argc == 2){
        if (std::string(argv[1]) == "max") // Calcula o número máximo de dígitos suportados (teoricamente) pelo programa
            ndigit = 4294967295;
        else
            ndigit = atoi(argv[1]);
    }

    // Caso contrário é dada ajuda de execução e n é assumido como 60, continuando a execução
    else {
        std::cout << "Utilização: " << argv[0] << " <n>" << std::endl;
        std::cout << "  n - número de casas decimais a calcular" << std::endl << std::endl;
        std::cout << "A assumir n como 60" << std::endl;
    }

    // Qualquer número de dígitos menor que 20 é assumido como 20
    //para não gerar erros de cálculo
    if(ndigit < 20)
        ndigit = 20;

    // Define o tamanho de um bloco de dígitos a calcular
    nblock = ndigit/4;

    // Reserva memória para a execução
    tot = (long *)malloc(nblock*sizeof(long));
    t1 = (long *)malloc(nblock*sizeof(long));
    t2 = (long *)malloc(nblock*sizeof(long));
    t3 = (long *)malloc(nblock*sizeof(long));

    // Caso a memória não possa ser reservada, é dado um erro e a execução termina
    if (!tot || !t1 || !t2 || !t3) {
        std::cout << "Memória insuficiente" << std::endl;
        return 1;
    } else {
        std::cout << "A calcular " << ndigit << " digitos de pi....\n";
        std::cout << "Por favor aguarde, poderá demorar algum tempo...\n";
    }


    // Formula de Machin--------------
    // Calculo de 4*arctan(1/5) e guardado em tot
    arctan(tot, t1, t2, 5, 1);
    mult(tot, 4);

    // Calculo de arctan(1/239) e guardado em t3
    arctan(t3, t1, t2, 239, 2);
    // Ao tot é subtraído t3
    sub(tot, t3);

    // tot múltiplicado por 4 para que seja igual a pi
    mult(tot, 4);

    // Apresentação do resultado final
    escreve(tot);
    // -------------------------------
    
}


// função arctan (metade da função ainda me é estranha)
void arctan(long *resultado, long *w1, long *w2, long denom, long passo){
    long denom2 = denom*denom;
    long k = 1;

    // Define o resultado para 1
    set(resultado, 1);
    // Divide o resultado(1) pelo denominador
    div(resultado, denom);
    // O valor do resultado é copiado para w1
    copy(w1, resultado);

    // Enquanto w2 diferente de 0
    do{
        // se passo diferente de 0
        if (passo)
            // divide w1 pelo quadrado do denominador
            div(w1, denom2);
        // se passo igual a 0
        else {
            // w1 é dividido pelo denominador 2 vezes
            div(w1, denom);
            div(w1, denom);
        }

        // w1 é copiado para w2
        copy(w2, w1);
        // w2 é dividido por 2*k+1
        div(w2, 2*k+1);
        
        // se k impar
        if(k%2)
            // w2 é subraído do resultado
            sub(resultado, w2);
        // se k par
        else
            // w2 é somado ao resultado
            add(resultado, w2);

        // k incrementado por 1
        k++;

    } while(!zero(w2));
    
}

//Compara resultado com 0 e devolve true se for 0
bool zero(long *nm){
    for(int i = 0; i < nblock; i++)
        if (nm[i])
            return false;
    return true;
}

//copia os valores de inic para o resultado
void copy(long *resultado, long *inic){
    for(int i=0; i<nblock; i++)
        resultado[i] = inic[i];
}

//limpa o resultado antes da execução
void set(long *resultado, long rhs){
    for (int i = 0; i<nblock; i++)
        resultado[i] = 0;
    resultado[0] = rhs;
}

// Subtrai val de resultado
void sub(long *resultado, long *val){
    
    for(int i = nblock-1; i>= 0; i--){
        resultado[i] -= val[i];

        if(resultado[i] < 0){
            resultado[i] += BASE;
            resultado[i-1]--;
        }
    }
}

//Soma val a resultado
void add(long *resultado, long *val){
    for(int i = nblock - 1; i >= 0; i--){
        resultado[i] += val[i];
        if(resultado[i] >= BASE){
            resultado[i] -= BASE;
            resultado[i-1]++;
        }
    }
}

// multiplica resultado por val
void mult(long *resultado, long val){
    long carry = 0;
    for(int i = nblock-1; i >= 0; i--){
        resultado[i] *= val;
        resultado[i] += carry;
        carry = resultado[i]/BASE;
        resultado[i] %= BASE;
    }
}

//Obtem a divisão de result por denom
void div(long *resultado, long denom){
    long carry = 0;

    for(int i=0; i<nblock; i++){
        resultado[i] += carry*BASE;
        carry = resultado[i] % denom;
        resultado[i] /= denom;
    }
}

//Escreve o resultado no ecrã
void escreve(long *resultado){
    char s[10];
    std::cout << resultado[0] << ".\n";

    for (int i = 1; i < nblock; i++){
        sprintf(s, "%4ld ", resultado[i]);

        for (int k = 0; k < 5; k++)
            if(s[k] == ' ') 
                s[k] = '0';

        std::cout << s[0] << s[1] << s[2] << s[3];
        if(i%15 == 0)
            std::cout << '\n';
    }
    std::cout << '\n';
}
