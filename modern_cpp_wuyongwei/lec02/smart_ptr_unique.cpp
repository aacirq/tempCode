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

#include <utility>

template <typename T>
class smart_ptr {
 public:
  smart_ptr(T *ptr = nullptr) : m_ptr(ptr) {}
  ~smart_ptr() { delete m_ptr; }

  smart_ptr(smart_ptr &other) = delete;

  template <typename U>
  smart_ptr(smart_ptr<U> &&other) {
    m_ptr = other.release();
  }

  smart_ptr &operator=(smart_ptr rhs) {
    rhs.swap(*this);
    return *this;
  }

  T &operator*() const { return *m_ptr; }
  T *operator->() const { return m_ptr; }
  operator bool() const { return m_ptr; }  // 类型转换运算符：无形参，无显式返回值类型

  T *get() const { return m_ptr; }

  T *release() {
    T *ptr = m_ptr;
    m_ptr = nullptr;
    return ptr;
  }

  void swap(smart_ptr &other) {
    using std::swap;
    swap(m_ptr, other.m_ptr);
  }

 private:
  T *m_ptr;
};

int main() {
  smart_ptr<Shape> ptr1{create_shape(ShapeType::circle)};
  // smart_ptr<Shape> ptr2{ptr1};   // ERROR, have no copy-constructor
  smart_ptr<Shape> ptr3;
  // ptr3 = ptr1;   // ERROR, have no copy-assignment
  ptr3 = std::move(ptr1);
  smart_ptr<Shape> ptr4{std::move(ptr3)};

  smart_ptr<Circle> ptr_circle{new Circle};

  ptr1 = std::move(ptr_circle);

  smart_ptr<int> ptr_int{new int(1)};

  // error: cannot convert ‘int*’ to ‘Shape*’ in assignment
  // ptr3 = std::move(ptr_int);

  return 0;
}