#pragma once
#include <list>
#include <algorithm>

class Snake {
public:
	using coordinates = std::pair<int, int>;

private:

	std::list<coordinates> body;

	int direction; //0-up, 1-right, 2-down, 3-left

public:

	Snake();
	Snake(const coordinates& in_coordinates);

	coordinates getHead() const; //lmao

	int getDirection() const;
	void setDirection(int in_direction);

	bool move(int field_width, int field_height, const coordinates& food);

	bool has(const coordinates& in_coordinates) const;

	void add_part();

};