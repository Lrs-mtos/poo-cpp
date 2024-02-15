//essa atividade eu fiz acompanhando o vídeo. Modifiquei os personagens, seus tamanhos e fiz um toggle do grid ao apertar a letra G
//seria triste jogar um jogo com a grade na tela. Mudei alguns outros pequenos detalhes também e, caso queira as imagens para jogar: 
//https://drive.google.com/drive/folders/10VkV0SuU5jASdnChoy3GA87Uh7KOZMPi?usp=sharing

#include <SFML/Graphics.hpp>
#include <iostream>

const int STEP_DIFF {50};

void setSize(sf::Sprite& sprite, int width, int height){
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width /dim.width, (float) height / dim.height);
}

struct Entity {
    int x {0};
    int y {0};
    int step {0};
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture):
    x(x), y(y), step(step), sprite(texture) {}

    void draw(sf::RenderWindow& window) {
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }
};

struct Board
{
    int nc {0};
    int nl {0};
    int step {0};
    sf::Sprite sprite;
    sf::RectangleShape rect;
    Board(int nc, int nl, int step, sf::Texture& texture){
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);

        this->rect.setSize(sf::Vector2f(STEP_DIFF, STEP_DIFF));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Green);
        this->rect.setOutlineThickness(1);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(this->sprite);
    }

    void draw_rect(sf::RenderWindow& window) {
    for (int i = 0; i < nc*3; i++){
        for (int j = 0; j < nl*3; j++){
            rect.setPosition(i * (STEP_DIFF), j * (STEP_DIFF));
            window.draw(rect);
        }
    }
    }
};


void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys){
    if(key == move_keys[0])
        entity.y--;
    else if(key == move_keys[1])
        entity.x++;
    else if(key == move_keys[2])
        entity.y++;
    else if(key == move_keys[3])
        entity.x--;
}

sf::Texture loadTexture(std::string path){
    sf::Texture texture;
    if(!texture.loadFromFile(path)){
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    return texture;
}

int main() {

    sf::Texture cow_tex { loadTexture("cow.png")};
    sf::Texture chicken_tex { loadTexture("chicken.png")};
    sf::Texture grass_tex { loadTexture("hmfomt.png")};

    const int STEP_BOARD {150};
    const int STEP_ENTITY {50};

    Entity cow(15, 4, STEP_ENTITY, cow_tex);
    Entity chicken(7, 4, STEP_ENTITY, chicken_tex);
    Board board(7, 3, STEP_BOARD, grass_tex);

    sf::RenderWindow window(sf::VideoMode(board.nc * STEP_BOARD, board.nl * STEP_BOARD), "SFML works!");

    int grid = false;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            } else if(event.type == sf::Event::KeyPressed) {
                moveEntity(event.key.code, cow, {sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down, sf::Keyboard::Left});
                moveEntity(event.key.code, chicken, {sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S, sf::Keyboard::A});

                if(event.key.code == sf::Keyboard::G){
                    grid = !grid;
                }
            }
        }

        window.clear();
        board.draw(window);
        if(grid == true) board.draw_rect(window);
        cow.draw(window);
        chicken.draw(window);
        window.display();
    }

    return 0;
}