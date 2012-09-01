#ifndef TURTLE_TURTLE_H_
#define TURTLE_TURTLE_H_

class TurtleImpl;

class Turtle {
private:
	static TurtleImpl& impl;

public:
	void forward(float distance);
	void right(float angle);
	void left(float angle);
};

#endif