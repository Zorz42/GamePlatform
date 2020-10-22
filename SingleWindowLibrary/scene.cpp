//
//  scene.cpp
//  SingleWindowLibrary
//
//  Created by Jakob Zorz on 11/09/2020.
//

#include "swl.h"

Swl::scene::scene(void (*loopFn)(), void (*eventFn)(SDL_Event&), void (*initFn)(), void (*closeFn)()) : loopFunction(loopFn), eventFunction(eventFn), initFunction(initFn), closeFunction(closeFn) {}

void Swl::switchScene(scene& scene_) {
    _current_scene = &scene_;
}

void Swl::runScenes() {
    if_dev(!_current_scene) {
        std::cout << "[Swl::runScenes] No scene is set! Exiting!" << std::endl;
        return;
    }
    
    SDL_Event event;
    while(_running) {
        scene* curr_scene = _current_scene;
        if(curr_scene->initFunction)
            curr_scene->initFunction();
        
        while(curr_scene == _current_scene && _running) {
            while(SDL_PollEvent(&event)) {
                if(event.type == SDL_QUIT)
                    _running = false;
                else if(curr_scene->eventFunction)
                    curr_scene->eventFunction(event);
            }
            pushDrawColor(_current_scene->background_color);
            SDL_RenderClear(_renderer);
            popDrawColor();
            
            if(curr_scene->loopFunction)
                curr_scene->loopFunction();
            
            SDL_RenderPresent(_renderer);
        }
        if(curr_scene->closeFunction)
            curr_scene->closeFunction();
    }
}
