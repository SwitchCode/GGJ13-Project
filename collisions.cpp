#include "config.hpp"

bool AABBvSAABB(sf::Rect<float> rect1, sf::Rect<float> rect2)
{
   return !((rect2.left >= rect1.left + rect1.width)
	|| (rect2.left + rect2.width <= rect1.left)
	|| (rect2.top >= rect1.top + rect1.height)
	|| (rect2.top + rect2.height <= rect1.top));
}
