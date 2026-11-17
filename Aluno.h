#pragma once

#include <iostream>
#include <fstream>
#include <cstring> // Necessário para manipulação de char[]
class Aluno {
private:
    char nome[50]; 
    int matricula;
    float nota1; 
    float nota2;

public:
    // Construtor opcional para inicializar valores
    Aluno() {
        matricula = 0;
        nota1 = 0.0f;
        nota2 = 0.0f;
        std::memset(nome, 0, sizeof(nome));
    }

    int getMatricula() const {
    return matricula;
}

    void cadastrarAluno(int &nMatricula); 
    float calcularMedia(int matBuscada) ;

    void alterarNota(int matBuscada); };