#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include "./chat_structs.cpp"
#include "./json.hpp"

using json = nlohmann::json;

std::string json2string(json j) {
    std::string s = j.dump();
    return s;
}

json string2json(std::string s) {
    json j = json::parse(s);
    return j;
}

int menuOptions()
{
    printf("1. Chatear con todos los usuarios (broadcasting).\n");
    printf("2. Enviar y recibir mensajes directos, privados, aparte del chat general.\n");
    printf("3. Cambiar de status.\n");
    printf("4. Listar los usuarios conectados al sistema de chat.\n");
    printf("5. Desplegar información de un usuario en particular.\n");
    printf("6. Ayuda.\n");
    printf("7. Salir.\n");
    printf("\n");
    printf("Ingrese una opción: ");
    int option;
    scanf("%d", &option);
    return option;
}

// gcc -o client client.cpp -std=c++11 -lstdc++

int main(int argc, char *argv[])
{

    //    if (argc != 5){
    //        return 1;
    //    }
    //
    //    // nombre del cliente
    //    char *clientName = argv[1];
    //
    //    // nombre de usuario
    //    char *userName = argv[2];
    //
    //    // ip del servidor
    //    char *serverIP = argv[3];
    //
    //    // puerto del servidor
    //    int serverPort = atoi(argv[4]);

    std::string jsonTest = R"({"type":"login","userName":"user1","password":"pass1"})";

    json j = string2json(jsonTest);

    std::cout << j["type"] << std::endl;


    bool running = true;

    while (running)
    {

        int option = menuOptions();

        switch (option)
        {
        case 4:
            printf("Listar usuarios conectados.\n");
            break;
        case 7:
            running = false;
            break;
        default:
            continue;
        }
    }

    return 0;
}
