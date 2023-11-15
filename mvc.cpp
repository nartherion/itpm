#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "mvc example");

    sf::Texture texture;
    if (!texture.loadFromFile("guts.png"))
        return EXIT_FAILURE;

    sf::Sprite image;
    image.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                    image.setScale(1.5, 1.5);
                else
                    image.setScale(1, 1);
            }
        }

        window.clear(sf::Color::Black);

        window.clear();
        window.draw(image);

        window.display();
    }

    return EXIT_SUCCESS;
}
