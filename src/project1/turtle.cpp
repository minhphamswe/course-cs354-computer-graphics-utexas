#include <math.h>
#include <project1/turtle.h>

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

 public:
  TurtleImpl()
      : location(0.f, 0.f, 0.f), orientation(0, 1, 0), color(0.f, 0.f, 0.f),
      drawing(true) {}

  void setPoints(std::vector<Point> *points_) {
    points = points_;
    points->push_back(location);
  }

  void setColors(std::vector<Color> *colors_) {
    colors = colors_;
    colors->push_back(color);
  }

  void forward(float distance) {
    location = location + distance * orientation;
    mark();
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
    mark();
  }

  void up() {
    drawing = false;
  }

  void down() {
    drawing = true;
    mark();
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

void Turtle::reset() {
  impl->reset();
}