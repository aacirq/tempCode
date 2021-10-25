/**
 * RAII特性，利用类来管理资源，发生异常时，析构函数仍然执行，保证资源的正确释放
 */

// 限定作用域的枚举类型
enum class ShapeType { circle, triangle, rectangle };

class Shape {};
class Circle : public Shape {};
class Triangle : public Shape {};
class Rectangle : public Shape {};

Shape *create_shape(ShapeType type) {
  switch (type) {
    case ShapeType::circle:
      return new Circle();
      break;

    case ShapeType::triangle:
      return new Triangle();
      break;

    case ShapeType::rectangle:
      return new Rectangle();
      break;

    default:
      break;
  }
}

class ShapeWrapper {
 public:
  explicit ShapeWrapper(Shape *ptr = nullptr) : m_ptr(ptr) {}
  ~ShapeWrapper() { delete m_ptr; }  // 可以delete空指针
  Shape *get() const { return m_ptr; }

 private:
  Shape *m_ptr;
};

void foo() { ShapeWrapper ptr_wrapper(create_shape(ShapeType::triangle)); }

int main() { return 0; }