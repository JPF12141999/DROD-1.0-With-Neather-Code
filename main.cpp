#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "DROD:AE");
    sf::Clock clock;
    bool ContinueIsWaitingtoDisappear = false;
    bool ContinueIsClicked = false;
    bool Draw = false;
    sf::Texture MainMenu("Title.bmp");
    sf::Sprite MainMenuSprite(MainMenu);
    sf::Sprite ContinueHighlightSprite(MainMenu);
    sf::Sprite ContinuePressedSprite(MainMenu);
    sf::IntRect ContinueHighlight({641, 27}, {117, 41});
    sf::IntRect ContinuePressed({641, 69}, {126, 50});
    ContinueHighlightSprite.setPosition({430.f, 90.f});
    ContinuePressedSprite.setPosition({424.f, 86.f});
    sf::FloatRect ContinueAreaFloat(ContinueHighlightSprite.getGlobalBounds());
    ContinuePressedSprite.getGlobalBounds();
    sf::Vector2i mousePos;

    while (window.isOpen())

    {

        window.clear();
        window.draw(MainMenuSprite);

        while (const std::optional event = window.pollEvent())
        {

            if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                {
                    mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f floatmousePos(mousePos);
                    if (ContinueAreaFloat.contains(floatmousePos))
                    {
                        ContinueIsClicked = true;
                        ContinueIsWaitingtoDisappear = true;
                        clock.restart();
                    }
                }
            }

            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f floatmousePos(mousePos);
                if (ContinueAreaFloat.contains(floatmousePos) && !ContinueIsClicked)
                {
                    ContinueHighlightSprite.setTextureRect(ContinueHighlight);
                    Draw = true;
                }
                else
                {
                    Draw = false;
                }
            }


            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (ContinueIsClicked && clock.getElapsedTime().asSeconds() >= 1.f)
        {
            window.draw(MainMenuSprite);
            ContinueIsClicked = false;
            ContinueIsWaitingtoDisappear = false;
        }
        else
        {
            if (ContinueIsClicked)
            {
                ContinuePressedSprite.setTextureRect(ContinuePressed);
                window.draw(ContinuePressedSprite);
            }
        }

        if (Draw)
        {
            ContinueHighlightSprite.setTextureRect(ContinueHighlight);
            window.draw(ContinueHighlightSprite);
        }

        window.display();
    }
}
