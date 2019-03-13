#include "Screens.h"



Screens::Screens()
{
	loadFiles();

	m_backgroundSprite.setTexture(m_backgroundTexture);

	m_buttonSprite.setTexture(m_buttonTexture);
	m_buttonSprite.setTextureRect(sf::IntRect{ BUTTON_WIDTH,45,BUTTON_WIDTH,BUTTON_HEIGHT });
	m_buttonSprite.setOrigin(m_buttonSprite.getGlobalBounds().width / 2, m_buttonSprite.getGlobalBounds().height / 2);
	m_buttonSprite.setScale(1.8f, 1.8f);

	m_titleText.setFont(m_pacFont);
	m_titleText.setCharacterSize(80u);
	m_titleText.setString("PACMAN");
	m_titleText.setPosition(400.0f, 80.0f);
	m_titleText.setOrigin(m_titleText.getGlobalBounds().width / 2, 0);

	m_buttonText.setFont(m_pacFont);
	m_buttonText.setFillColor(sf::Color::Black);
	m_buttonText.setCharacterSize(40u);
}

void Screens::loadFiles()
{
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\pacmanBackground.jpg"))
	{
		// Error loading background sprite
	}
	if (!m_buttonTexture.loadFromFile("ASSETS\\IMAGES\\yellowSheet.png"))
	{
		// Error loading background sprite
	}
	if (!m_pacFont.loadFromFile("ASSETS\\FONTS\\PAC-FONT.TTF"))
	{
		// Error loading font file
	}
}

void Screens::processEvents(sf::Event t_event)
{
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (sf::Mouse::Left == t_event.mouseButton.button)
		{
			// Check that the click was within the horisontal bounds of the buttons
			if (t_event.mouseButton.x > BUTTON_ONE_POSITION.x - BUTTON_WIDTH / 2 && t_event.mouseButton.x < BUTTON_ONE_POSITION.x + BUTTON_WIDTH / 2)
			{
				// Check that the click is within the vertical bounds of the first the button
				if (t_event.mouseButton.y > BUTTON_ONE_POSITION.y - BUTTON_HEIGHT / 2 && t_event.mouseButton.y < BUTTON_ONE_POSITION.y + BUTTON_HEIGHT / 2)
				{
					s_currentState = GameState::Gameplay;
				}
			}
		}
	}
}

void Screens::draw(sf::RenderWindow & t_window)
{
	t_window.draw(m_backgroundSprite);

	m_buttonText.setString("start");
	m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 1.5);
	m_buttonText.setPosition(BUTTON_ONE_POSITION);
	m_buttonSprite.setPosition(BUTTON_ONE_POSITION);
	t_window.draw(m_buttonSprite);
	t_window.draw(m_buttonText);

	m_buttonText.setString("help");
	m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 1.5);
	m_buttonText.setPosition(BUTTON_TWO_POSITION);
	m_buttonSprite.setPosition(BUTTON_TWO_POSITION);
	t_window.draw(m_buttonSprite);
	t_window.draw(m_buttonText);

	m_buttonText.setString("exit");
	m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 1.5);
	m_buttonText.setPosition(BUTTON_THREE_POSITION);
	m_buttonSprite.setPosition(BUTTON_THREE_POSITION);
	t_window.draw(m_buttonSprite);
	t_window.draw(m_buttonText);

	t_window.draw(m_titleText);
}

