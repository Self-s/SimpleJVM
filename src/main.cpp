#include <cstdlib>
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <string>

#include "classloader.h"
#include "classviewer.h"
#include "utils.h"
#include "methodarea.h"
#include "classinstance.h"
#include "heap.h"
#include "classruntime.h"
#include "executionengine.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage:\n");
        printf("\t./JVM file_class.class \n");
        printf("\t./JVM file_class.class class_info.out\n");
        exit(1);
    }
    
	const char *file_className = argv[1];
	const char *file_output = (argc < 3) ? NULL : argv[2];
    
    // Carregamento da classe de entrada.
    MethodArea &methodArea = MethodArea::getInstance();
    ClassRuntime *classRuntime = methodArea.loadClassNamed(file_className);
    // Fim do carregamento.
    
    // Verificação se o nome da classe de entrada é igual ao nome do arquivo.
    string className = getFormattedConstant(classRuntime->getClassFile()->constant_pool, classRuntime->getClassFile()->this_class);
    string fileName(file_className);
    if (fileName.find(".class") != fileName.npos) {
        fileName = fileName.substr(0, fileName.size() - 6);
    }
    if (className != fileName) {
        cerr << "Nome do arquivo diferente do nome da classe." << endl;
        exit(1);
    }
    // Fim da verificação
    
    // Salvando a estrutura do .class em um arquivo de saída ou realizando a execução da classe.
    if (file_output) {
        FILE *output = fopen(file_output, "w+");
        if (output == NULL) {
            cerr << "Erro ao abrir arquivo " << file_output << "." << endl;
            exit(2);
        }
        printClassFile(classRuntime->getClassFile(), output);
        fclose(output);
    } else {
        ExecutionEngine &executionEngine = ExecutionEngine::getInstance();
        executionEngine.startExecutionEngine(classRuntime);
    }
    
    return 0;
}
