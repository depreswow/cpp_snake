#include "Snake.h"

Snake::Snake() 
	: body(), direction(1) {
	body.push_front(coordinates(4, 4));
	body.push_front(coordinates(4, 3));
	body.push_front(coordinates(4, 2));
}

Snake::Snake(const coordinates& in_coordinates) : body(), direction(1) {
	body.push_front(in_coordinates);
}

Snake::coordinates Snake::getHead() const {
	return body.back();
}

int Snake::getDirection() const {
	return direction;
}

void Snake::setDirection(int in_direction) {
	direction = in_direction;
}

bool Snake::move(int field_width, int field_height, const coordinates& food) {

	bool eat = false;
	coordinates head = getHead();


	switch (direction) {

	case 0: //up
		if (head.first > 0 && (coordinates(head.first - 1, head.second) == *body.begin() || !has(coordinates(head.first - 1, head.second)))) {
			if (food == coordinates(head.first - 1, head.second))
				eat = true;
		}
		else
			return false;
		break;

	case 1: //right
		if (head.second < field_width - 1 && (coordinates(head.first, head.second + 1) == *body.begin() || !has(coordinates(head.first, head.second + 1)))) {
			if (food == coordinates(head.first, head.second + 1))
				eat = true;
		}
		else
			return false;
		break;

	case 2: //down
		if (head.first < field_height - 1 && (coordinates(head.first + 1, head.second) == *body.begin() || !has(coordinates(head.first + 1, head.second)))) {
			if (food == coordinates(head.first + 1, head.second))
				eat = true;
		}
		else
			return false;
		break;

	case 3: //left
		if (head.second > 0 && (coordinates(head.first, head.second - 1) == *body.begin() || !has(coordinates(head.first, head.second - 1)))) {
			if (food == coordinates(head.first, head.second - 1))
				eat = true;
		}
		else
			return false;
		break;

	}

	decltype(body.begin()) next;

	for (auto iter = body.begin(); iter != body.end(); ++iter) {
		if (*iter == head) {

			switch (direction) {

			case 0: //up
				(*iter).first--;
				break;

			case 1: //right
				(*iter).second++;
				break;

			case 2: //down
				(*iter).first++;
				break;

			case 3: //left
				(*iter).second--;
				break;

			}
		}
		else {
			
			if (iter == body.begin() && eat)
				body.push_front(*iter);

			next = iter;
			(*iter) = *(++next);

		}
	}
	return true;
}

bool Snake::has(const coordinates& in_coordinates) const {
	return std::find(body.begin(), body.end(), in_coordinates) != body.end();
}