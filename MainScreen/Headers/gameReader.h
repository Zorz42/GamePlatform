//
//  gameReader.h
//  GamePlatform
//
//  Created by Jakob Zorz on 27/10/2020.
//

#include <vector>
#include "swl.h"

namespace gameReader {
class game {
public:
    std::string name, icon_path, dir_path;
    void loadImage();
    void renderText();
    void render(unsigned int index, float scale, int position, int selected);
private:
    Swl::texture _icon_texture, _text_texture;
};

std::pair<bool, game> loadGame(std::string path);

}
