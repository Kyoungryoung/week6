#include <iostream>
#include <vector>

template <class T_VECTOR>
class Vector2D {
public:
	T_VECTOR x_, y_;

	Vector2D(const T_VECTOR& x_input, const T_VECTOR& y_input)
		:x_(x_input), y_(y_input)
	{}

	void print() {
		std::cout << x_ << " " << y_<< std::endl;
	}
};

int main()
{
	Vector2D<int> int_vector(1, 1);
	int_vector.print();
	Vector2D<int> float_vector(1.0f, 1.0f);
	int_vector.print();
	return 0;
}