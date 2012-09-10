#include <turtle/turtle.h>

class TurtleImpl {
private:
	float x;   ///< position data
	float y;   ///< position data
	float z;   ///< position data
	float rx;   ///< rotation data
	float ry;   ///< rotation data
	float rz;   ///< rotation data

public:
	TurtleImpl() : x(0), y(0), z(0), rx(0), ry(0), rz(0) {}

    void forward(float distance) {
		
	}

	void left(float angle) {
		
	}

	void right(float angle) {
		
	}
};

void Turtle::forward(float distance) {
	impl.forward(distance);
}

void Turtle::left(float angle) {
	impl.left(angle);
}

void Turtle::right(float angle) {
	impl.right(angle);
}
