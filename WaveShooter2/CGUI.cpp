#include "CGui.h"


//////////////////////////////////////////////////////////////////////////
// IGUIObject

IGUIObject::IGUIObject(sf::Font* pFont, sf::RenderWindow* pWindow)
{
	m_pFont = pFont;
	m_pWindow = pWindow;
	((sf::Texture&)m_pFont->getTexture(8)).setSmooth(false);
	m_text.setFont(*m_pFont);

}

bool IGUIObject::isInside(sf::Vector2i pos)
{
	if (pos.x < m_pos.x)
		return false;

	if (pos.y < m_pos.y)
		return false;

	if (pos.x > m_pos.x + m_size.x)
		return false;

	if (pos.y > m_pos.y + m_size.y)
		return false;

	return true;
}

void IGUIObject::setFontSize(int fontSize)
{
	m_text.setCharacterSize(fontSize);
}

void IGUIObject::setColor(sf::Color color)
{
	m_text.setFillColor(color);
}

void IGUIObject::setPosition(float x, float y)
{
	m_pos = sf::Vector2f(x,y);
	m_rectangle.setPosition(m_pos);
	m_text.setPosition(m_pos);
}

//////////////////////////////////////////////////////////////////////////
// CText
CText::CText(sf::Font* pFont, sf::RenderWindow* pWindow)
	:IGUIObject(pFont, pWindow)
{
	m_text.setPosition(m_pos);
	m_text.setCharacterSize(25);
	m_text.setFillColor(sf::Color::White);

}

void CText::render()
{
	//m_pWindow->draw(m_rectangle);
	m_pWindow->draw(m_text);
}

//////////////////////////////////////////////////////////////////////////
// CInputBox

CInputBox::CInputBox(sf::Font* pFont, sf::RenderWindow* pWindow)
	:IGUIObject(pFont, pWindow)
{
	m_size.y = 40;
	m_size.x = 200;

	m_text.setFillColor(sf::Color::Black);
	m_rectangle.setFillColor(sf::Color::White);
	m_rectangle.setSize(m_size); // todo: Göra smart.

	m_rectangle.setOutlineColor(sf::Color::Red);
	m_rectangle.setOutlineThickness(2);
	m_active = false;
}

void CInputBox::activate()
{
	m_text.setFillColor(sf::Color::White);
	m_rectangle.setFillColor(sf::Color::Blue);
	m_active = true;
}

void CInputBox::deactivate()
{
	m_text.setFillColor(sf::Color::Black);
	m_rectangle.setFillColor(sf::Color::White);
	m_active = false;
}

void CInputBox::render()
{
	m_pWindow->draw(m_rectangle);
	m_pWindow->draw(m_text);
}

void CInputBox::addChar(char c)
{
	if (!m_active)
		return;

	if (c == 8)
	{
		if (m_input.getSize() > 0)
		{
			m_input.erase(m_input.getSize() - 1);
			m_text.setString(m_input);
		}

	}
	else
	{
		m_input += c;
		m_text.setString(m_input);
	}

}



CGui::CGui(sf::RenderWindow* pWindow)
{
	m_pWindow = pWindow;
	m_pActiveInput = 0;

	if (!m_font.loadFromFile("resources/fonts/pixelmix.ttf"))
	{
		return; // ERROR
	}

}

CGui::~CGui()
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		delete m_objects[i];
		m_objects[i] = 0;
	}
	m_objects.clear();
}

CInputBox* CGui::createInput(int x, int y)
{
	CInputBox* pInput = new CInputBox(&m_font, m_pWindow);
	sf::Vector2f inputpos(x, y);
	pInput->setPosition(inputpos.x, inputpos.y);

	m_objects.push_back(pInput);
	return pInput;
}

CText* CGui::createText(int x, int y, string text)
{
	CText* pText = new CText(&m_font, m_pWindow);
	sf::Vector2f inputpos(x, y);
	pText->setPosition(inputpos.x,inputpos.y);
	pText->setString(text);

	m_objects.push_back(pText);
	return pText;
}

void CGui::deleteObject(IGUIObject* pObject)
{
	for (int i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i] == pObject)
		{
			// 1: Delete
			// 2: Ta bort pekare ur vector
			delete m_objects[i];
			iter_swap(m_objects.begin() + i, m_objects.end() - 1);
			m_objects.pop_back();
			//swap(m_texts.begin()+i, m_texts.end());
		}
	}
}

void CGui::render()
{
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		m_objects[i]->render();
	}
}

void CGui::update()
{
	for (unsigned int i = 0; i < m_objects.size(); i++)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_objects[i]->isInside(sf::Mouse::getPosition(*m_pWindow)))
			{
				/*if (is input object)
				{
					if (m_pActiveInput != 0)
					{
						m_pActiveInput->deactivate();
					}
					m_pActiveInput = m_objects[i];
					m_objects[i]->activate();
				}*/
				
			}
		}
	}
}

void CGui::handleEvent(sf::Event event)
{
	/*for (int i = 0; i < m_objects.size(); i++)
	{
		if (event.type == sf::Event::TextEntered)
		{
			m_objects[i]->addChar(event.text.unicode);
		}
	}*/

	if (event.type == sf::Event::TextEntered && m_pActiveInput != 0)
	{
		if (event.text.unicode == 13)
		{
			m_pActiveInput->deactivate();
			m_pActiveInput = 0;
		}
		else
		{
			m_pActiveInput->addChar(event.text.unicode);
		}
	}
}