#pragma once

#include <exception>
#include <memory>
#include <string>
#include <vector>

class StrBlog;

class StrBlogPtr {
public:
  StrBlogPtr() : curr(0) {}
  StrBlogPtr(StrBlog &a, std::size_t sz = 0) : wptr(a.data), curr(sz) {}

  std::string &operator*();
  StrBlogPtr &operator++();

private:
  std::shared_ptr<std::vector<std::string>> check(std::size_t,
                                                  const std::string &) const;

  std::weak_ptr<std::vector<std::string>> wptr;
  std::size_t curr;
};

// =============================================================================

class StrBlog {
  friend class StrBlogPtr;

public:
  typedef std::vector<std::string>::size_type size_type;

  StrBlog();
  StrBlog(std::initializer_list<std::string> il);

  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }

  void push_back(const std::string &t) { data->push_back(t); }
  void pop_back();

  std::string &front();
  std::string &back();
  const std::string &front() const;
  const std::string &back() const;

  StrBlogPtr begin() { return StrBlogPtr(*this); }

private:
  std::shared_ptr<std::vector<std::string>> data;

  void check(size_type idx, const std::string &msg) const;
};

// =============================================================================

std::string &StrBlogPtr::operator*() {
  auto ptr = check(curr, "dereference past end");
  return (*ptr)[curr];
}

StrBlogPtr &StrBlogPtr::operator++() {
  check(curr, "increment past end of StrBlogPtr");
  ++curr;
  return *this;
}

std::shared_ptr<std::vector<std::string>>
StrBlogPtr::check(std::size_t idx, const std::string &msg) const {
  auto ptr = wptr.lock();
  if (!ptr) {
    throw std::runtime_error("unbound StrBlogPtr");
  }
  if (idx >= ptr->size()) {
    throw std::out_of_range(msg);
  }
  return ptr;
}

// =============================================================================

void StrBlog::check(size_type idx, const std::string &msg) const {
  if (idx >= data->size()) {
    throw std::out_of_range(msg);
  }
}

StrBlog::StrBlog() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlog::StrBlog(std::initializer_list<std::string> il)
    : data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlog::pop_back() {
  check(0, "pop back of empty StrBlog");
  data->pop_back();
}

std::string &StrBlog::front() {
  return const_cast<std::string &>(static_cast<const StrBlog &>(*this).front());
}

std::string &StrBlog::back() {
  return const_cast<std::string &>(static_cast<const StrBlog &>(*this).back());
}

const std::string &StrBlog::front() const {
  check(0, "front of empty StrBlog");
  return data->front();
}

const std::string &StrBlog::back() const {
  check(0, "back of empty StrBlog");
  return data->back();
}