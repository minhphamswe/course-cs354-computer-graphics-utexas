#include <math.h>
#include <vector>
#include "./turtle.h"

double degree(double rad) {
  return rad * INV_PI * 180;
}

double radian(double deg) {
  return deg * INV_180 * PI;
}

class TurtleImpl {
 private:
  Point location;
  Vector orientation;
  Color color;
  std::vector<Point> *points;
  std::vector<Color> *colors;
  bool drawing;
  enum {BLACK, RED, GREEN, BLUE};

 public:
  TurtleImpl()
      : location(0.f, 0.f, 0.f), orientation(0, 1, 0), color(0.f, 0.f, 0.f),
      drawing(true) {}

  void setPoints(std::vector<Point> *points_) {
    points = points_;
  }

  void setColors(std::vector<Color> *colors_) {
    colors = colors_;
  }

  void forward(float distance) {
    mark();     // start a new line
    location = location + distance * orientation;
    mark();     // finish the line
  }

  void left(float deg) {
    double rad = radian(deg);
    float x, y;

    x = orientation.x * cos(rad) - orientation.y * sin(rad);
    y = orientation.y * cos(rad) + orientation.x * sin(rad);

    orientation.x = x;
    orientation.y = y;
  }

  void right(float deg) {
    left(deg * -1);
  }

  void origin() {
    location = Point(0.f, 0.f, 0.f);
    orientation = Vector(0.f, 1.f, 0.f);
  }

  void up() {
    drawing = false;
  }

  void down() {
    drawing = true;
  }

  void changeColor(int colNum) {
    switch (colNum) {
      case BLACK:
        color = Color(0.f, 0.f, 0.f);
        break;
      case RED:
        color = Color(1.f, 0.f, 0.f);
        break;
      case GREEN:
        color = Color(0.f, 1.f, 0.f);
        break;
      case BLUE:
        color = Color(0.f, 0.f, 1.f);
        break;
    }
  }

  void mark() {
    if (drawing) {
      points->push_back(location);
      colors->push_back(color);
    }
  }

  void reset() {
    points->clear();
    colors->clear();
    color = Color(0.f, 0.f, 0.f);
    drawing = true;
    origin();
  }
};

TurtleImpl* Turtle::impl = new TurtleImpl();

Turtle::Turtle() {}

Turtle::Turtle(std::vector< Point > *points_, std::vector< Color > *colors_) {
  impl->setPoints(points_);
  impl->setColors(colors_);
}

void Turtle::forward(float distance) {
  impl->forward(distance);
}

void Turtle::left(float deg) {
  impl->left(deg);
}

void Turtle::right(float deg) {
  impl->right(deg);
}

void Turtle::origin() {
  impl->origin();
}

void Turtle::up() {
  impl->up();
}

void Turtle::down() {
  impl->down();
}

void Turtle::color(int colNum) {
  impl->changeColor(colNum);
}


void Turtle::reset() {
  impl->reset();
}
