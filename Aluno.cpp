#include <iostream>
#include <fstream>
#include <string>
#include <cstring> // manipular de char[]
#include "Aluno.h"


    void Aluno::cadastrarAluno(int &nMatricula){
        int maiorMatricula = 0;
        const std::string nomeArquivo = "alunos.txt"; 

        // Abre o arquivo apenas para leitura para definir o numero da matrícula a ser cadastrada
        {
            std::ifstream arqLeitura(nomeArquivo, std::ios::binary);
            if (arqLeitura.is_open()) {
                Aluno temp;
                while (arqLeitura.read(reinterpret_cast<char*>(&temp), sizeof(Aluno))) {
                    if (temp.matricula > maiorMatricula) {
                        maiorMatricula = temp.matricula;
                    }
                }
                arqLeitura.close();
            }
        }

        // Define a nova matrícula
        nMatricula = maiorMatricula + 1; 
        this->matricula = nMatricula; // CORREÇÃO: Atribuindo ao atributo do objeto atual!

        // Limpa o buffer do teclado caso haja algum '\n' pendente
        std::cin.ignore(); 

        std::cout << "Digite o nome do aluno: ";
        std::cin.getline(this->nome, 50);// this usa o atributo do objeto atual

        std::cout << "Digite a nota 1 do aluno: ";
        std::cin >> this->nota1;

        std::cout << "Digite a nota 2 do aluno: ";
        std::cin >> this->nota2;

        // 2. Abre o arquivo em modo de append (anexo) para salvar o novo aluno
        std::ofstream arqEscrita(nomeArquivo, std::ios::binary | std::ios::app);
        if (!arqEscrita.is_open()) {
            std::cout << "Erro ao abrir o arquivo para gravacao!\n";
            return;
        }

        // Grava o objeto atual no arquivo binário
        arqEscrita.write(reinterpret_cast<const char*>(this), sizeof(Aluno));
        arqEscrita.close();

        std::cout << "\nAluno matriculado com sucesso!\n";
        std::cout << "A matricula gerada e: " << this->matricula << "\n\n";
    }

    float Aluno::calcularMedia(int matBuscada) {
        if (matBuscada >= 30) {
            std::cout << "Matrícula inválida. Matrícula deve ser menor que 30.\n";
            return -1.0f; // Matrícula inválida
        }
        const std::string nomeArquivo = "alunos.txt"; // Mesmo arquivo usado no cadastro

        // Abre o arquivo para leitura
        std::ifstream arq(nomeArquivo, std::ios::binary);
        if (!arq.is_open()) {
            return -.01f; // Arquivo não encontrado ou vazio
        }

        Aluno temp;
        while (arq.read(reinterpret_cast<char*>(&temp), sizeof(Aluno))) {
            if (temp.matricula == matBuscada) {
                return (temp.nota1 + temp.nota2) / 2.0f;
            }
        }

        arq.close();
        return -1.0f; // Matrícula não encontrada
    };

void Aluno::alterarNota(int matBuscada) {
    const std::string nomeArquivo = "alunos.txt"; 

    // Abre o arquivo em modo binário para leitura e escrita
    std::fstream arq(nomeArquivo, std::ios::binary | std::ios::in | std::ios::out);
    if (!arq.is_open()) {
        std::cout << "Erro ao abrir o arquivo para alteracao!\n";
        return;
    }

    Aluno temp;
    int index = 0;
    bool encontrado = false;

    // Lê o arquivo registro por registro até encontrar a matrícula desejada
    while (arq.read(reinterpret_cast<char*>(&temp), sizeof(Aluno))) {
        // getter getMatricula() para respeitar o encapsulamento, mas conseguir usar matricula que é privado
        if (temp.getMatricula() == matBuscada) {
            encontrado = true;

            std::cout << "\nAluno encontrado!\n";
            std::cout << "Digite a nova nota 1: ";
            std::cin >> temp.nota1; // Métodos membros podem acessar atributos privados de instâncias da mesma classe

            std::cout << "Digite a nova nota 2: ";
            std::cin >> temp.nota2;

            // Calcula o deslocamento exato em bytes usando o índice atual do registro
            std::streamoff posicao = index * static_cast<std::streamoff>(sizeof(Aluno));
            
            // Posiciona o ponteiro de ESCRITA (seekp) exatamente no início deste registro em disco
            arq.seekp(posicao);

            // Sobrescreve o registro antigo com os novos dados atualizados
            arq.write(reinterpret_cast<const char*>(&temp), sizeof(Aluno));

            // Tratamento de erro do fluxo
            if (arq.fail()) {
                std::cout << "Erro ao gravar a alteracao no arquivo.\n";
                arq.clear(); // Limpa a flag de erro
            } else {
                std::cout << "\nNotas alteradas com sucesso!\n\n";
            }
            break; // Encerra o loop pois o aluno já foi encontrado e atualizado
        }
        index++; // Incrementa o índice do registro
    }

    if (!encontrado) {
        std::cout << "\nMatricula nao encontrada para alteracao.\n\n";
    }

    arq.close();
}