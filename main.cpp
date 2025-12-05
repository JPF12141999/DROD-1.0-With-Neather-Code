#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "DROD:AE");
    sf::Clock clock;
    bool ContinueIsWaitingtoDisappear = false;
    bool ContinueButtonClicked = false;
    sf::Texture MainMenu("Title.bmp");
    sf::Sprite MainMenuSprite(MainMenu);
    sf::Sprite ContinueHighlightSprite(MainMenu);
    sf::Sprite ContinuePressedSprite(MainMenu);
    sf::IntRect ContinueHighlight({641, 27}, {117, 41});
    sf::IntRect ContinuePressed({641, 69}, {126, 50});
    ContinueHighlightSprite.setPosition({430.f, 90.f});
    ContinuePressedSprite.setPosition({424.f, 86.f});
    sf::FloatRect ContinueAreaFloat({430.f, 90.f}, {126.f, 50.f});
    sf::Vector2i mousePos;

    while (window.isOpen())

    {

        window.clear();
        window.draw(MainMenuSprite);

        while (const std::optional event = window.pollEvent())
        {

            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f floatmousePos(mousePos);
                if (ContinueAreaFloat.contains(floatmousePos))
                    ContinueHighlightSprite.setTextureRect(ContinueHighlight);
            }

            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }
        }

        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f floatmousePos(mousePos);
            if (ContinueAreaFloat.contains(floatmousePos))
            {
                ContinueHighlightSprite.setTextureRect(ContinueHighlight);
                window.draw(ContinueHighlightSprite);
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f floatmousePos(mousePos);
            if (ContinueAreaFloat.contains(floatmousePos))
            {
                ContinueButtonClicked = true;
                ContinueIsWaitingtoDisappear = true;
                clock.restart();
            }
        }

        if (ContinueIsWaitingtoDisappear && clock.getElapsedTime().asSeconds() >= 1.f)
        {
            window.draw(MainMenuSprite);
            ContinueButtonClicked = false;
        }
        else
        {
            if (ContinueButtonClicked == true)
            {
                ContinuePressedSprite.setTextureRect(ContinuePressed);
                window.draw(ContinuePressedSprite);
            }
        }

        window.display();
    }
}
