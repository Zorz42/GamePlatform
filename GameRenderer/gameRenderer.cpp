//
//  gameRenderer.cpp
//  GamePlatform
//
//  Created by Jakob Zorz on 28/10/2020.
//

#include "swl.h"
#include "gameRenderer.h"
#include "joystickDriver.h"
#include "mainScreen.h"

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <queue>

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 5732

void game_event(SDL_Event& event);
void game_main();

Swl::scene game_scene(&game_main, &game_event);
gameLoader::game* curr_game = nullptr;
sockaddr_in address;
int server_fd, new_socket, addrlen = sizeof(address), opt = 1;
std::queue<std::string> data_queue;
bool game_running = false;
std::thread gameThread;

void receiveLoop() {
    ssize_t valread = 1;
    char buffer[1024] = {0};
    while(valread) {
        valread = read(new_socket, buffer, 1024);
        if(valread)
            std::cout << "socket traffic: " << buffer << std::endl;
    }
    game_running = false;
}

void gameRenderer::init() {
    if(!(server_fd = socket(AF_INET, SOCK_STREAM, 0))) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if(bind(server_fd, (sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if(listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
}

void runCurrGame() {
    system(("\"" + curr_game->dir_path + curr_game->exec_path + "\"").c_str());
}

void gameRenderer::launchGame(gameLoader::game& game) {
    game_running = true;
    curr_game = &game;
    swl.switchScene(game_scene);
    
    gameThread = std::thread(runCurrGame);
    gameThread.detach();
    
    if((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    std::thread receiveThread(receiveLoop);
    receiveThread.detach();
}

void game_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
    else if(jd::handleEvents(event));
    else if(event.type == SDL_JOYBUTTONDOWN && event.jbutton.button == jd::button::cross)
        swl.switchScene(mainScreen::main_screen_scene);
}


void game_main() {
    if(!game_running)
        swl.switchScene(mainScreen::main_screen_scene);
}
