#include <iostream>
#include <fstream>
#include <string>
#include "Aluno.cpp"
#include "Aluno.h"

int main(){


int menu; // opção do menu pra usar no switch
int nCadastrados=0; //controle do número de alunos cadastrados e matrícula do aluno
Aluno cadastrados[30]; //array definindo com o class aluno, com limite de 30 alunos
int matricula; //variável para receber a matrícula do aluno para calcular a média






std::cout<<"Bom dia!, o que deseja fazer?\ndigite 1 para mátricular um aluno\ndigite 2 para ver a média de um aluno\ndigite 3 para refazer a matricula uma nota\ndigite 4 para sair\n";
std::cin>>menu;

while(menu!=4){

switch (menu) {
case 1:
cadastrados[nCadastrados].cadastrarAluno(nCadastrados);
nCadastrados++;
break;

case 2:
std::cout<<"digite a matrícula do aluno para calcular a média: ";


std::cin>>matricula;
if(cadastrados[matricula].calcularMedia(matricula)==-1.0f){std::cout<<"matricula invalida";
}
else{std::cout<<cadastrados[matricula].calcularMedia(matricula);}
break;

case 3:
std::cout<<"digite a matrícula do aluno para alterar a nota: ";
std::cin>>matricula;
cadastrados[matricula].alterarNota(matricula);
break;

case 4:
return 0;
break;

}
std::cout<<"\ndigite 1 para mátricular um aluno\ndigite 2 para ver a média de um aluno\ndigite 3\ndigite 4 para sair\n";
std::cin>>menu;
}
}