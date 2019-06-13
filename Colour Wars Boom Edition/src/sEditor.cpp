#include "sEditor.h"

sEditor::sEditor(sf::Vector2u screenSize)
	: m_toolbarKey(sf::Keyboard::Key::G, 0.2f)
{
	m_mapSize.x = screenSize.x;
	m_mapSize.y = screenSize.y;
	
	for (int y = 0; y < m_mapSize.y / CELL_SIZE; y++)
	{
		for (int x = 0; x < m_mapSize.x / CELL_SIZE; x++)
		{
			// Outer walls
			if (y == 0 || x == 0 || y == (m_mapSize.y / CELL_SIZE) - 1 || x == (m_mapSize.x / CELL_SIZE) - 1)
				m_map.push_back(sCell(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE), "default_wall"));
			else
				m_map.push_back(sCell(sf::Vector2f(x * CELL_SIZE, y * CELL_SIZE), "default_floor"));
		}
	}

	// Save and load buttons
	m_UI.push_back(sButton({ 0,  0 }, 32, "Save", sf::Color(255, 216, 0)));
	m_UI.push_back(sButton({ 32 * 4, 0 }, 32, "Load", sf::Color(255, 216, 0)));
	m_UI.push_back(sButton({ (float)screenSize.x - (32 * 4), 48 }, 32, "Wall", sf::Color(0, 148, 255)));
	m_UI.push_back(sButton({ (float)screenSize.x - (32 * 4), 96 }, 32, "Floor", sf::Color(0, 148, 255)));
	m_UI.push_back(sButton({ (float)screenSize.x - (32 * 4), 144 }, 32, "Spawn", sf::Color(0, 148, 255)));
	m_UI.push_back(sButton({ (float)screenSize.x - (32 * 4), 192 }, 32, "Empty", sf::Color(0, 148, 255)));

	// Default settings
	m_selectedType	= "empty_cell";
}

void sEditor::Update(sf::RenderWindow* window)
{
	for (auto &i : m_UI)
	{
		// If the UI has been clicked set flag
		if (i.isClicked(window))
			m_selecting = true;

		if (i.getString() == "Save")
		{
			if (i.isClicked(window))
			{
				std::cout << "Enter map name: ";
				std::string name;
				std::cin >> name;

				Save(name);
			}
		}
		else if (i.getString() == "Load")
		{
			if (i.isClicked(window))
			{
				std::cout << "Enter map name: ";
				std::string name;
				std::cin >> name;

				Load(name);
			}
		}
		else if (i.getString() == "Wall")
		{
			if (i.isClicked(window))
				m_selectedType = "default_wall";
		}
		else if (i.getString() == "Floor")
		{
			if (i.isClicked(window))
				m_selectedType = "default_floor";
		}
		else if (i.getString() == "Spawn")
		{
			if (i.isClicked(window))
				m_selectedType = "default_spawn_point";
		}
		else if (i.getString() == "Empty")
		{
			if (i.isClicked(window))
				m_selectedType = "empty_cell";
		}
	}
}

void sEditor::HandleInput(sf::RenderWindow& window)
{
	// Hide or show UI
	if (m_toolbarKey.isKeyPressed())
	{
		for (auto &i : m_UI)
		{
			if (i.isVisible())
				i.setVisible(false);
			else i.setVisible(true);
		}
	}

	// Place Selected Cell Type
	// m_selecting is used because if you choose something on the UI
	// it places the cell even do you didn't want that
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_selecting)
	{
		// Get selected cell COORDS
		int x = sf::Mouse::getPosition(window).x / CELL_SIZE;
		int y = sf::Mouse::getPosition(window).y / CELL_SIZE;

		int coord = Convert2Dto1D::convert(x, y, m_mapSize.x / CELL_SIZE);

		m_map.at(coord).ChangeTexture(m_selectedType);

		if (m_selectedType == "default_wall")
			m_map.at(coord).setBlocking(true);
		else m_map.at(coord).setBlocking(false);
	}
	else m_selecting = false;
}

void sEditor::Draw(sf::RenderWindow* window)
{
	// Draw cells
	for (auto &i : m_map)
	{
		i.Draw(window);
	}

	// Draw Buttons / UI
	for (auto &i : m_UI)
	{
		i.Draw(window);
	}
}

void sEditor::Save(std::string mapName)
{
	std::ofstream writer("maps/" + mapName + ".txt");
	writer << m_mapSize.x << " " << m_mapSize.y << "\n";

	for (auto &i : m_map)
	{
		writer << i.getTexName() << " " << i.getPosition().x << " " << i.getPosition().y << " " << i.isBlocking() << "\n";
	}

	std::cout << "Saved map " << mapName << "\n";

	// Close file
	writer.close();
}

void sEditor::Load(std::string mapName)
{
	std::ifstream reader;
	reader.open("maps/" + mapName + ".txt");
	if (reader.fail())
	{
		std::cout << "Map " << mapName << " does not exist!\n";
	}
	else
	{
		// Clear current map vector and read in map data until the end of the file is hit
		m_map.clear();

		std::string line;

		// Get map size first
		reader >> m_mapSize.x >> m_mapSize.y;

		// Get the cells of the map
		while (!reader.eof())
		{
			sf::Vector2f pos;
			bool blocking;
			reader >> line >> pos.x >> pos.y >> blocking;
			
			sCell temp(pos, line);
			temp.setBlocking(blocking);
			
			m_map.push_back(temp);
		}
	}

	std::cout << "Loaded map " << mapName << "\n";

	// Close file
	reader.close();
}
