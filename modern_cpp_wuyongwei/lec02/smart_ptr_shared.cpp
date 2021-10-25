class shared_count {
 public:
  shared_count() : m_count(1) {}
  void add_count() { ++m_count; }
  long reduce_count() { return --m_count; }
  long get_count() const { return m_count; }

 private:
  long m_count;
};

#include <utility>

template <typename T>
class smart_ptr {
  template <typename U>
  friend class smart_ptr;

 public:
  explicit smart_ptr(T *ptr = nullptr) : m_ptr(ptr) {
    if (m_ptr) {
      m_shared_count = new shared_count();
    }
  }

  ~smart_ptr() {
    if (m_ptr && !m_shared_count->reduce_count()) {
      delete m_ptr;
      delete m_shared_count;
    }
  }

  smart_ptr(const smart_ptr &other) : m_ptr(other.m_ptr) {
    if (m_ptr) {
      other.m_shared_count->add_count();
      m_shared_count = other.m_shared_count;
    }
  }

  /**
   * 动态绑定的时候用
   */
  template <typename U>
  smart_ptr(const smart_ptr<U> &other) noexcept : m_ptr(other.m_ptr) {
    if (m_ptr) {
      other.m_shared_count->add_count();
      m_shared_count = other.m_shared_count;
    }
  }

  template <typename U>
  smart_ptr(smart_ptr<U> &&other) noexcept : m_ptr(other.m_ptr) {
    if (m_ptr) {
      m_shared_count = other.m_shared_count;
      other.m_ptr = nullptr;
    }
  }

  /**
   * 类型转换的时候用
   */
  template <typename U>
  smart_ptr(const smart_ptr<U> &other, T *ptr) noexcept : m_ptr(ptr) {
    if (ptr) {
      other.m_shared_count->add_count();
      m_shared_count = other.m_shared_count;
    }
  }

  smart_ptr &operator=(smart_ptr rhs) noexcept {
    rhs.swap(*this);
    return *this;
  }

  T &operator*() const noexcept { return *m_ptr; }
  T *operator->() const noexcept { return m_ptr; }
  operator bool() const noexcept { return m_ptr; }

  T *get() const noexcept { return m_ptr; }

  void swap(smart_ptr &other) noexcept {
    using std::swap;
    swap(m_ptr, other.m_ptr);
    swap(m_shared_count, other.m_shared_count);
  }

  long use_count() const noexcept {
    if (m_ptr) {
      return m_shared_count->get_count();
    } else {
      return 0;
    }
  }

 private:
  shared_count *m_shared_count;
  T *m_ptr;
};

template <typename T>
void swap(smart_ptr<T> &lhs, smart_ptr<T> &rhs) noexcept {
  lhs.swap(rhs);
}

template <typename T, typename U>
smart_ptr<T> static_pointer_cast(smart_ptr<U> &other) noexcept {
  T *ptr = static_cast<T *>(other.get());
  return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(smart_ptr<U> &other) noexcept {
  T *ptr = reinterpret_cast<T *>(other.get());
  return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> const_pointer_cast(smart_ptr<U> &other) noexcept {
  T *ptr = const_cast<T *>(other.get());
  return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(smart_ptr<U> &other) noexcept {
  T *ptr = dynamic_cast<T *>(other.get());
  return smart_ptr<T>(other, ptr);
}

#ifdef TEST

#include <iostream>

enum class ShapeType { circle, triangle, rectangle };

class Shape {
 public:
  Shape() {}
  virtual ~Shape() {}
};

class Circle : public Shape {
 public:
  ~Circle() { puts("~Circle()"); }
};

class Triangle : public Shape {
 public:
  ~Triangle() { puts("~Triangle()"); }
};

class Rectangle : public Shape {
 public:
  ~Rectangle() { puts("~Rectangle()"); }
};

int main() {
  smart_ptr<Circle> ptr1(new Circle());
  printf("use count of ptr1 is %ld\n", ptr1.use_count());

  smart_ptr<Shape> ptr2;
  printf("use count of ptr2 was %ld\n", ptr2.use_count());

  ptr2 = ptr1;
  /**
   * 这里会先执行依次copy-constructor，然后执行move
   * constructor，最后执行assignment 理由：
   *   这里先执行类型转换，将ptr1从smart_ptr<Circle>转到smart_ptr<Shape>，
   *   产生临时对象(temp)，然后将temp赋值给ptr2，
   *   由于temp是临时对象，编译器将其作为右值引用传到assignment运算符中，执行赋值操作。
   */
  printf("use count of ptr2 is now %ld\n", ptr2.use_count());

  smart_ptr<Circle> ptr3 = dynamic_pointer_cast<Circle>(ptr2);
  printf("use count of ptr3 is %ld\n", ptr3.use_count());

  if (ptr1) {
    fputs("ptr1 is not empty\n", stdout);
  }

  return 0;
}

#endif