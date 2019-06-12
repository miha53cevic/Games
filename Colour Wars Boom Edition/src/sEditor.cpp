#include "sEditor.h"

sEditor::sEditor(sf::Vector2u screenSize)
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
	sButton save({ 0,  0 }, 32, "Save", sf::Color(255, 216, 0));
	sButton load({ 32*4, 0 }, 32, "Load", sf::Color(255, 216, 0));

	m_buttons.push_back(save);
	m_buttons.push_back(load);
}

void sEditor::Update(sf::RenderWindow* window)
{
	for (auto &i : m_buttons)
	{
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
	}
}

void sEditor::HandleInput()
{

}

void sEditor::Draw(sf::RenderWindow* window)
{
	// Draw cells
	for (auto &i : m_map)
	{
		i.Draw(window);
	}

	// Draw Buttons / UI
	for (auto &i : m_buttons)
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
