#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({640, 480}), "DROD:AE");
    sf::Clock clock;
    sf::Time elapsed = clock.getElapsedTime();
    enum class ContinueButtonState
    {
        nothing,
        hovered,
        pressed
    };
    ContinueButtonState ContinueState = ContinueButtonState::nothing;
    sf::Texture MainMenu("Title.bmp");
    sf::Sprite MainMenuSprite(MainMenu);
    sf::Sprite Continue(MainMenu);
    sf::IntRect ContinueRect({424, 86}, {126, 49});
    sf::IntRect ContinueHighlight({641, 27}, {117, 41});
    sf::IntRect ContinuePressed({641, 69}, {126, 50});
    Continue.setPosition({424.f, 86.f});
    Continue.setTextureRect(ContinueRect);
    sf::Vector2f mousePos;

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
                    if (Continue.getGlobalBounds().contains(mousePos))
                    {
                        ContinueState = ContinueButtonState::pressed;
                        clock.restart();
                    }
                }
            }


            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if ((ContinueState == ContinueButtonState::pressed) && (elapsed.asSeconds() <= 1.f))
        {
            ContinueState = ContinueButtonState::pressed;
        }

        if (ContinueState != ContinueButtonState::pressed)
        {
            if (Continue.getGlobalBounds().contains(sf::Vector2f(mousePos)))
            {
                Continue.setTextureRect(ContinueHighlight);
                ContinueState = ContinueButtonState::hovered;
            }
            else
            {
                ContinueState = ContinueButtonState::nothing;
            }
        }

        window.draw(Continue);
        window.display();
    }
}
