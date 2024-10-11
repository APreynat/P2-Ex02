#include "pch.h"

class SFMLUtility {
public:

	SFMLUtility();
	~SFMLUtility();

	sf::Vector2i getMousePosition(sf::RenderWindow& window);
};