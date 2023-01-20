#include "Deque.hpp"

#include <cmath>
#include <compare>
#include <stdexcept>

namespace fefu_laboratory_two {

template <typename T>
typename Allocator<T>::pointer Allocator<T>::allocate(size_type size) {
  return new T[size];
}

template <typename T>
void Allocator<T>::deallocate(pointer p, size_type n) noexcept {
  delete[] p;
}

/***************************************************************************************************/

template <typename ValueType>
Deque_iterator<ValueType>::Deque_iterator() noexcept {}

template <typename ValueType>
Deque_iterator<ValueType>::Deque_iterator(pointer* nodes, size_type node, size_type cell, size_type cell_size)
  noexcept : nodes(nodes), node(node), cell(cell), cell_size(cell_size) {}

template <typename ValueType>
Deque_iterator<ValueType>::Deque_iterator(const Deque_iterator &other) noexcept
    : Deque_iterator(other.nodes, other.node, other.cell, other.cell_size) {}

template <typename ValueType>
Deque_iterator<ValueType> &Deque_iterator<ValueType>::operator=(
    const Deque_iterator &other) {
  nodes = other.nodes;
  node = other.node;
  cell = other.cell;
  cell_size = other.cell_size;
  return *this;
}

template <typename ValueType>
Deque_iterator<ValueType>::~Deque_iterator() {}

template <typename ValueType>
void swap(Deque_iterator<ValueType> &left, Deque_iterator<ValueType> &right) {
  Deque_iterator<ValueType> temp(right);
  right = left;
  left = temp;
}

template <typename ValueType>
typename Deque_iterator<ValueType>::reference
Deque_iterator<ValueType>::operator*() const {
  return (nodes[node][cell]);
}

template <typename ValueType>
typename Deque_iterator<ValueType>::pointer
Deque_iterator<ValueType>::operator->() const {
  return (nodes[node][cell]);
}

template <typename ValueType>
Deque_iterator<ValueType> &Deque_iterator<ValueType>::operator++() {
  *this = *this + 1;
  return *this;
}

template <typename ValueType>
Deque_iterator<ValueType> Deque_iterator<ValueType>::operator++(int) {
  Deque_iterator<ValueType> temp = *this;
  ++(*this);
  return temp;
}

template <typename ValueType>
Deque_iterator<ValueType> &Deque_iterator<ValueType>::operator--() {
  *this = *this - 1;
  return *this;
}

template <typename ValueType>
Deque_iterator<ValueType> Deque_iterator<ValueType>::operator--(int) {
  Deque_iterator<ValueType> temp = *this;
  --(*this);
  return temp;
}

template <typename ValueType>
Deque_iterator<ValueType> Deque_iterator<ValueType>::operator+(
    const Deque_iterator::difference_type &offset) const {
  Deque_iterator<ValueType> temp = *this;
  temp.node += (offset + temp.cell) / cell_size;
  temp.cell = (offset + temp.cell) % cell_size;
  return temp;
}

template <typename ValueType>
Deque_iterator<ValueType> &Deque_iterator<ValueType>::operator+=(
    const Deque_iterator::difference_type &offset) {
  *this = *this + offset;
  return *this;
}

template <typename ValueType>
Deque_iterator<ValueType> Deque_iterator<ValueType>::operator-(
    const Deque_iterator::difference_type &offset) const {
  Deque_iterator<ValueType> temp = *this;
  if (offset > static_cast<difference_type>(temp.cell)) {
    temp.node -= (offset - temp.cell) / cell_size + 1;
    temp.cell = (cell_size - offset % cell_size + temp.cell) % cell_size;
  } else {
    temp.cell = (temp.cell - offset) % cell_size;
  }
  return temp;
}

template <typename ValueType>
Deque_iterator<ValueType> &Deque_iterator<ValueType>::operator-=(
    const Deque_iterator::difference_type &offset) {
  *this = *this - offset;
  return *this;
}

template <typename ValueType>
typename Deque_iterator<ValueType>::difference_type
Deque_iterator<ValueType>::operator-(const Deque_iterator<ValueType> &iterator) const {
  Deque_iterator<ValueType>::difference_type
  diff = iterator.cell > this->cell ? iterator.cell - this->cell : this->cell - iterator.cell;
  diff += cell_size * (iterator.node > this->node ? iterator.node - this->node : this->node - iterator.node);
  return diff;
}

template <typename ValueType>
typename Deque_iterator<ValueType>::reference
Deque_iterator<ValueType>::operator[](
    const Deque_iterator<ValueType>::difference_type &offset) {
  return *(*this + offset);
}

/***************************************************************************************************/

template <typename ValueType>
Deque_const_iterator<ValueType>::Deque_const_iterator() noexcept {}

template <typename ValueType>
Deque_const_iterator<ValueType>::Deque_const_iterator(
    const Deque_iterator<ValueType>& other) noexcept
    : iter(other) {}

template <typename ValueType>
Deque_const_iterator<ValueType>::Deque_const_iterator(
    const Deque_const_iterator& other) noexcept
    : Deque_const_iterator(other.iter) {}

template <typename ValueType>
Deque_const_iterator<ValueType> &Deque_const_iterator<ValueType>::operator=(
    const Deque_iterator<ValueType> &other) {
  iter = other;
  return *this;
}

template <typename ValueType>
Deque_const_iterator<ValueType>::~Deque_const_iterator() {}

template <typename ValueType>
void swap(Deque_const_iterator<ValueType> &left,
          Deque_const_iterator<ValueType> &right) {
  Deque_const_iterator<ValueType> temp(right);
  right = left;
  left = temp;
}

template <typename ValueType>
typename Deque_const_iterator<ValueType>::reference
Deque_const_iterator<ValueType>::operator*() const {
  return *iter;
}

template <typename ValueType>
typename Deque_const_iterator<ValueType>::pointer
Deque_const_iterator<ValueType>::operator->() const {
  return *iter;
}

template <typename ValueType>
Deque_const_iterator<ValueType> &Deque_const_iterator<ValueType>::operator++() {
  iter = iter + 1;
  return *this;
}

template <typename ValueType>
Deque_const_iterator<ValueType> Deque_const_iterator<ValueType>::operator++(
    int) {
  Deque_const_iterator<ValueType> temp = *this;
  ++(*this);
  return temp;
}

template <typename ValueType>
Deque_const_iterator<ValueType> &Deque_const_iterator<ValueType>::operator--() {
  iter = iter - 1;
  return *this;
}

template <typename ValueType>
Deque_const_iterator<ValueType> Deque_const_iterator<ValueType>::operator--(
    int) {
  Deque_const_iterator<ValueType> temp = *this;
  --(*this);
  return temp;
}

template <typename ValueType>
Deque_const_iterator<ValueType> Deque_const_iterator<ValueType>::operator+(
    const Deque_const_iterator::difference_type &offset) const {
  Deque_const_iterator<ValueType> temp = *this;
  temp.iter = temp.iter + offset;
  return temp;
}

template <typename ValueType>
Deque_const_iterator<ValueType> &Deque_const_iterator<ValueType>::operator+=(
    const Deque_const_iterator::difference_type &offset) {
  iter = iter + offset;
  return *this;
}

template <typename ValueType>
Deque_const_iterator<ValueType> Deque_const_iterator<ValueType>::operator-(
    const Deque_const_iterator::difference_type &offset) const {
  Deque_const_iterator<ValueType> temp = *this;
  temp.iter = temp.iter - offset;
  return temp;
}

template <typename ValueType>
Deque_const_iterator<ValueType> &Deque_const_iterator<ValueType>::operator-=(
    const Deque_const_iterator::difference_type &offset) {
  iter = iter - offset;
  return *this;
}

template <typename ValueType>
typename Deque_const_iterator<ValueType>::difference_type
Deque_const_iterator<ValueType>::operator-(
    const Deque_const_iterator<ValueType> &iterator) const {
  return iter - iterator.iter;
}

template <typename ValueType>
typename Deque_const_iterator<ValueType>::reference
Deque_const_iterator<ValueType>::operator[](
    const Deque_const_iterator<ValueType>::difference_type &offset) {
  return *(iter + offset);
}

/***************************************************************************************************/

template<class Iter>
constexpr Deque_reverse_iterator<Iter>::Deque_reverse_iterator() {}

template <class Iter>
constexpr Deque_reverse_iterator<Iter>::Deque_reverse_iterator(
    Deque_reverse_iterator::iterator_type x)
    : iter(x) {}

template <class Iter>
template <class U>
constexpr Deque_reverse_iterator<Iter>::Deque_reverse_iterator(
    const Deque_reverse_iterator<U>& other)
    : Deque_reverse_iterator(other.base()) {}

template <class Iter>
template <class U>
Deque_reverse_iterator<Iter>& Deque_reverse_iterator<Iter>::operator=(const Deque_reverse_iterator<U>& other) {
  iter = other.base();
  return *this;
}

template <class Iter>
typename Deque_reverse_iterator<Iter>::iterator_type Deque_reverse_iterator<Iter>::base() const {
  return iter;
}

template <class Iter>
typename Deque_reverse_iterator<Iter>::reference Deque_reverse_iterator<Iter>::operator*() const {
  return *(iter - 1);
}

template <class Iter>
typename Deque_reverse_iterator<Iter>::pointer Deque_reverse_iterator<Iter>::operator->() const {
  return *(iter - 1);
}

template <class Iter>
typename Deque_reverse_iterator<Iter>::reference Deque_reverse_iterator<Iter>::operator[](Deque_reverse_iterator<Iter>::difference_type n) {
  return *(iter - 1 + n);
}

template <class Iter>
Deque_reverse_iterator<Iter>& Deque_reverse_iterator<Iter>::operator++() {
  --iter;
  return *this;
}

template <class Iter>
Deque_reverse_iterator<Iter> Deque_reverse_iterator<Iter>::operator++(int) {
  auto temp = *this;
  --iter;
  return temp;
}

template <class Iter>
Deque_reverse_iterator<Iter>& Deque_reverse_iterator<Iter>::operator--() {
  ++iter;
  return *this;
}

template <class Iter>
Deque_reverse_iterator<Iter> Deque_reverse_iterator<Iter>::operator--(int) {
  auto temp = *this;
  ++iter;
  return temp;
}

template <class Iter>
Deque_reverse_iterator<Iter> Deque_reverse_iterator<Iter>::operator+(difference_type n) const {
  return Deque_reverse_iterator(iter - n);
}

template <class Iter>
Deque_reverse_iterator<Iter>& Deque_reverse_iterator<Iter>::operator+=(difference_type n) {
  iter -= n;
  return *this;
}

template <class Iter>
Deque_reverse_iterator<Iter> Deque_reverse_iterator<Iter>::operator-(difference_type n) const {
  return Deque_reverse_iterator(iter + n);
}

template <class Iter>
Deque_reverse_iterator<Iter>& Deque_reverse_iterator<Iter>::operator-=(difference_type n) {
  iter += n;
  return *this;
}

template <class IterT>
Deque_reverse_iterator<IterT> operator+(
    typename Deque_reverse_iterator<IterT>::difference_type n,
    const Deque_reverse_iterator<IterT>& it) {
  return it - n;
}

template <class Iterator>
auto operator-(const Deque_reverse_iterator<Iterator>& lhs,
                      const Deque_reverse_iterator<Iterator>& rhs) {
  return lhs.iter - rhs.iter;
}

template <class Iter>
Deque_reverse_iterator<Iter> make_reverse_iterator(Iter i) {
  return Deque_reverse_iterator(i);
}

/***************************************************************************************************/

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque() : _alloc(fefu_laboratory_two::Allocator<T>()) {
  _nodes = _nalloc.allocate(_nodes_size);
  _nodes[_last_node] = _alloc.allocate(MAX_CELL_SIZE);
}

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque(const Alloc& alloc) : _alloc(alloc) {
  _nodes = _nalloc.allocate(_nodes_size);
  _nodes[_last_node] = _alloc.allocate(MAX_CELL_SIZE);
}

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque(size_type count, const T& value, const Alloc& alloc)
  : Deque(alloc) {
  for(auto i = 0; i < count; ++i) {
    this->push_back(value);
  }
}

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque(size_type count, const Alloc& alloc)
  : Deque(alloc) {
    this->resize(count);
  }

template <typename T, typename Alloc>
template <class InputIt>
Deque<T, Alloc>::Deque(InputIt first, InputIt last, const Alloc& alloc)
  : Deque(alloc) {
    for(auto it = first; it != last; ++it) {
      this->push_back(*it);
    }
  }

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque(const Deque& other) : Deque() {
  this->assign(other.begin(), other.end());
}

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque(const Deque& other, const Alloc& alloc)
  : Deque(alloc) {
  this->assign(other.begin(), other.end());
}

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque(Deque&& other) : Deque() {
  this->swap(other);
}

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque(Deque&& other, const Alloc& alloc) : Deque(alloc) {
  this->swap(other);
}

template <typename T, typename Alloc>
Deque<T, Alloc>::Deque(std::initializer_list<T> init, const Alloc& alloc)
  : Deque(alloc) {
    this->assign(init);
}

template <typename T, typename Alloc>
Deque<T, Alloc>::~Deque() {
  for (size_type i = _first_node; i <= _last_node; ++i) {
    _alloc.deallocate(_nodes[i], MAX_CELL_SIZE);
  }
  _nalloc.deallocate(_nodes, _nodes_size);
} 

template <typename T, typename Allocator>
Deque<T, Allocator>& Deque<T, Allocator>::operator=(const Deque& other) {
  this->clear();
  this->assign(other.begin(), other.end());
  return *this;
} 

template <typename T, typename Allocator>
Deque<T, Allocator>& Deque<T, Allocator>::operator=(Deque&& other) {
  this->clear();
  this->swap(other);
  return *this;
} 

template <typename T, typename Allocator>
Deque<T, Allocator>& Deque<T, Allocator>::operator=(std::initializer_list<T> ilist) {
  this->clear();
  this->assign(ilist);
  return *this;
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::assign(size_type count, const T& value) {
  this->clear();
  for (auto i = 0; i < count; ++i) {
    this->push_back(value);
  }
} 

template <typename T, typename Allocator>
template <class InputIt>
void Deque<T, Allocator>::assign(InputIt first, InputIt last) {
  this->clear();
  for (auto it = first; it != last; ++it) {
    this->push_back(*it);
  }
} 

template <typename T, typename Allocator>
void Deque<T, Allocator>::assign(std::initializer_list<T> ilist) {
  this->assign(ilist.begin(), ilist.end());
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::allocator_type Deque<T, Allocator>::get_allocator() const noexcept {
  return _alloc;
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reference Deque<T, Allocator>::at(size_type pos) {
  if (pos >= _size) {
    throw std::out_of_range("pos out of range");
  }
  return *(this->begin() + pos);
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reference Deque<T, Allocator>::at(size_type pos) const {
  if (pos >= _size) {
    throw std::out_of_range("pos out of range");
  }
  return *(this->begin() + pos);
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reference Deque<T, Allocator>::operator[](size_type pos) {
  if (pos >= _size) {
    throw std::out_of_range("pos out of range");
  }
  return *(this->begin() + pos);
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reference Deque<T, Allocator>::operator[](size_type pos) const {
  if (pos >= _size) {
    throw std::out_of_range("pos out of range");
  }
  return *(this->begin() + pos);
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reference Deque<T, Allocator>::front() {
  return _nodes[_first_node][_first_cell];
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reference Deque<T, Allocator>::front() const {
  return _nodes[_first_node][_first_cell];
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reference Deque<T, Allocator>::back() {
  return *(this->end() - 1);
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reference Deque<T, Allocator>::back() const {
  return *(this->end() - 1);
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::begin() noexcept {
  return iterator(_nodes, _first_node, _first_cell, MAX_CELL_SIZE);
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_iterator Deque<T, Allocator>::begin()
    const noexcept {
  return const_iterator(
      iterator(_nodes, _first_node, _first_cell, MAX_CELL_SIZE));
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_iterator Deque<T, Allocator>::cbegin()
    const noexcept {
  return this->begin();
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::end() noexcept {
  return iterator(_nodes, _last_node, _last_cell, MAX_CELL_SIZE);
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_iterator Deque<T, Allocator>::end()
    const noexcept {
  return const_iterator(
      iterator(_nodes, _last_node, _last_cell, MAX_CELL_SIZE));
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_iterator Deque<T, Allocator>::cend() const noexcept {
  return this->end();
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reverse_iterator
Deque<T, Allocator>::rbegin() noexcept {
  return reverse_iterator(this->end());
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reverse_iterator
Deque<T, Allocator>::rbegin() const noexcept {
  return const_reverse_iterator(this->cend());
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reverse_iterator Deque<T, Allocator>::crbegin() const noexcept {
  return this->rbegin();
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::reverse_iterator
Deque<T, Allocator>::rend() noexcept {
  return reverse_iterator(this->begin());
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reverse_iterator Deque<T, Allocator>::rend()
    const noexcept {
  return const_reverse_iterator(this->cbegin());
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::const_reverse_iterator Deque<T, Allocator>::crend() const noexcept {
  return this->rend();
} 

template <typename T, typename Allocator>
bool Deque<T, Allocator>::empty() const noexcept {
  return this->size() == 0;
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::size_type Deque<T, Allocator>::size() const noexcept {
  return this->_size;
} 

template <typename T, typename Allocator>
typename Deque<T, Allocator>::size_type Deque<T, Allocator>::max_size() const noexcept {
  return static_cast<size_t>(-1); //no limit?
} 

template <typename T, typename Allocator>
void Deque<T, Allocator>::shrink_to_fit() {
  // haha. no
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::clear() noexcept {
  for (size_type i = _first_node; i <= _last_node; ++i) {
    _alloc.deallocate(_nodes[i], MAX_CELL_SIZE);
  }
  _first_cell = 0;
  _last_cell = 0;
  _first_node = _nodes_size / 2;
  _last_node = _first_node;
  _nodes[_last_node] = _alloc.allocate(MAX_CELL_SIZE);
  _size = 0;
}

// этот код выглядит куда лучше и аккуратней, но работает медленней
/*
template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, const T& value) {
  difference_type offset = pos - this->begin();
  iterator ncpos = this->begin() + offset;
  value_type temp = *ncpos;
  for (auto it = ncpos; it != this->end(); ++it) {
    std::swap(*it, temp);
  }
  this->push_back(std::move(temp));
  *(ncpos) = value; 
  return ncpos;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, T&& value) {
  difference_type offset = pos - this->begin();
  iterator ncpos = this->begin() + offset;
  value_type temp = *ncpos;
  for (auto it = ncpos; it != this->end(); ++it) {
    std::swap(*it, temp);
  }
  this->push_back(std::move(temp));
  *(ncpos) = std::move(value); 
  return ncpos;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, size_type count, const T& value) {
  difference_type offset = pos - this->begin();
  iterator ncpos = this->begin() + offset;
  for (size_type i = 0; i < count; ++i) {
    this->insert(pos + i, value);
  }
  return ncpos + count - 1;
}

template <typename T, typename Allocator>
template <class InputIt>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
  difference_type offset = pos - this->begin();
  iterator ncpos = this->begin() + offset;
  size_type i = 0;
  for (auto it = first; it != last; ++it) {
    this->insert(pos + (i++), *it);
  }
  return ncpos + i - 1;
}
*/

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, const T& value) {
  difference_type offset = pos - this->begin();
  iterator it = this->begin() + offset;
  if (it == this->begin()) {
    this->push_front(value);
    return this->begin();
  }
  if (it == this->end()) {
    this->push_back(value);
    return this->end() - 1;
  }
  value_type temp = value;
  while (it != this->end()) {
    std::swap(*it, temp);
    ++it;
  }
  this->push_back(std::move(temp));
  return this->begin() + offset;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, T&& value) {
  difference_type offset = pos - this->begin();
  iterator it = this->begin() + offset;
  if (it == this->begin()) {
    this->push_front(std::move(value));
    return this->begin();
  }
  if (it == this->end()) {
    this->push_back(std::move(value));
    return this->end() - 1;
  }
  value_type temp = value;
  while (it != this->end()) {
    std::swap(*it, temp);
    ++it;
  }
  this->push_back(std::move(temp));
  return this->begin() + offset;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, size_type count, const T& value) {
  difference_type offset = pos - this->begin();
  iterator ncpos = this->begin() + offset;
  if (count == 0) {
    return ncpos;
  }
  if (ncpos == this->begin()) {
    for (size_type i = 0; i < count; ++i) { this->push_front(value); }
    return this->begin();
  }
  if (ncpos == this->end()) {
    for (size_type i = 0; i < count; ++i) { this->push_back(value); }
    return this->end() - count;
  }
  difference_type temp_size = pos - this->end();
  value_type* temp = _alloc.allocate(temp_size + count);
  size_type i = 0;
  for (; i < count; ++i) {
    temp[i] = value;
  }
  for (auto it = ncpos; i < temp_size + count; ++i, ++it) {
    temp[i] = std::move(*it);
  }
  i = 0;
  for (auto it = ncpos; it != this->end(); ++i, ++it) {
    *it = std::move(temp[i]);
  }
  for (; i < temp_size + count; ++i) {
    this->push_back(std::move(temp[i]));
  }
  _alloc.deallocate(temp, temp_size + count);
  auto first_pos = this->begin() + offset;
  return first_pos;
}

template <typename T, typename Allocator>
template <class InputIt>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
  difference_type offset = pos - this->begin();
  iterator ncpos = this->begin() + offset;
  if (last - first == 0) {
    return ncpos;
  }
  if (ncpos == this->begin()) {
    for (auto it = last - 1; it >= first; --it) {
      this->push_front(*it);
    }
    return this->begin();
  }
  if (ncpos == this->end()) {
    for (auto it = first; it != last; ++it) { this->push_back(*it); }
    return this->end() - (last - first);
  }
  difference_type temp_size = pos - this->end();
  difference_type count = (last - first);
  value_type* temp = _alloc.allocate(temp_size + count);
  difference_type i = 0;
  for (auto it = first; it != last; ++i, ++it) {
    temp[i] = *it;
  }
  for (auto it = ncpos; i < temp_size + count; ++i, ++it) {
    temp[i] = std::move(*it);
  }
  i = 0;
  for (auto it = ncpos; it != this->end(); ++i, ++it) {
    *it = std::move(temp[i]);
  }
  for (; i < temp_size + count; ++i) {
    this->push_back(std::move(temp[i]));
  }
  _alloc.deallocate(temp, temp_size + count);
  auto first_pos = this->begin() + offset;
  return first_pos;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> ilist) {
  return this->insert(pos, ilist.begin(), ilist.end());
}

template <typename T, typename Allocator>
template <class... Args>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::emplace(const_iterator pos, Args&&... args) {
  (this->insert(pos, args), ...);
  return pos - 1;
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::erase(const_iterator pos) {
  value_type temp = *(this->end() - 1);
  for (auto it = this->end() - 1; it >= pos; --it) {
    std::swap(*it, temp);
  }
  this->pop_back();
  return this->begin() + (pos - this->begin());
}

template <typename T, typename Allocator>
typename Deque<T, Allocator>::iterator Deque<T, Allocator>::erase(const_iterator first, const_iterator last) {
  difference_type range = last - first;
  for (difference_type i = 0; i < range; ++i) {
    this->erase(first);
  }
  return this->begin() + (first - this->begin());
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::push_back(const T& value) {
  *(this->end()) = value;
  ++_size;
  if (_last_node == _nodes_size - 1) {
    this->_reserve(_nodes_size * 2);
  }
  if (_last_cell == MAX_CELL_SIZE - 1) {
    _nodes[++_last_node] = _alloc.allocate(MAX_CELL_SIZE);
    _last_cell = 0;
  } else {
    ++_last_cell;
  }
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::push_back(T&& value) {
  *(this->end()) = std::move(value);
  ++_size;
  if (_last_node == _nodes_size - 1) {
    this->_reserve(_nodes_size * 2);
  }
  if (_last_cell == MAX_CELL_SIZE - 1) {
    _nodes[++_last_node] = _alloc.allocate(MAX_CELL_SIZE);
    _last_cell = 0;
  } else {
    ++_last_cell;
  }
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::_reserve(size_type new_size) {
  size_type new_first_node;
  size_type new_last_node;
  if (new_size > _nodes_size) {
    new_first_node = (new_size - _nodes_size) / 2;
    new_last_node = (new_size - _nodes_size) / 2 + _last_node - _first_node;
  }
  else if (new_size < _nodes_size) {
    new_first_node = 1;
    new_last_node = new_size + 1;
    for (size_type i = new_size + 1; i <= _last_node; ++i) {
      _alloc.deallocate(_nodes[i], MAX_CELL_SIZE);
    }
    new_size += 2;
  }
  else {
    return;
  }
  value_type** new_nodes = _nalloc.allocate(new_size);
  for (size_type i = new_first_node, j = _first_node; i <= new_last_node && j <= _last_node; ++i, ++j) {
    new_nodes[i] = _nodes[j];
  }
  _nalloc.deallocate(_nodes, _nodes_size);
  _first_node = new_first_node;
  _last_node = new_last_node;
  _nodes_size = new_size;
  _nodes = new_nodes;
}

template <typename T, typename Allocator>
template <class... Args>
typename Deque<T, Allocator>::reference Deque<T, Allocator>::emplace_back(Args&&... args) {
  (this->push_back(args), ...);
  return this->back();
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::pop_back() {
  --_size;
  if (_last_cell == 0) {
    _alloc.deallocate(_nodes[_last_node], MAX_CELL_SIZE);
    --_last_node;
  }
  _last_cell = (MAX_CELL_SIZE + _last_cell - 1) % MAX_CELL_SIZE;
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::push_front(const T& value) {
  if (_first_node == 0) {
    this->_reserve(_nodes_size * 2);
  }
  if (_first_cell == 0) {
    _nodes[--_first_node] = _alloc.allocate(MAX_CELL_SIZE);
    _first_cell = MAX_CELL_SIZE - 1;
  } else {
    --_first_cell;
  }
  *(this->begin()) = value;
  ++_size;
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::push_front(T&& value) {
  if (_first_node == 0) {
    this->_reserve(_nodes_size * 2);
  }
  if (_first_cell == 0) {
    _nodes[--_first_node] = _alloc.allocate(MAX_CELL_SIZE);
    _first_cell = MAX_CELL_SIZE - 1;
  } else {
    --_first_cell;
  }
  *(this->begin()) = std::move(value);
  ++_size;
}

template <typename T, typename Allocator>
template <class... Args>
typename Deque<T, Allocator>::reference Deque<T, Allocator>::emplace_front(Args&&... args) {
  (this->push_front(std::forward<Args>(args)), ...);
  return this->front();
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::pop_front() {
  --_size;
  if (_first_cell == MAX_CELL_SIZE - 1) {
    _alloc.deallocate(_nodes[_first_node], MAX_CELL_SIZE);
    ++_first_node;
  }
  _first_cell = (_first_cell + 1) % MAX_CELL_SIZE;
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::resize(size_type count) {
  this->resize(count, T());
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::resize(size_type count, const value_type& value) {
  Deque<T, Allocator> deque;
  size_type difference = this->size() < count ? 0 : this->size() - count;
  deque.assign(this->begin(), this->end() - difference);
  if (deque.size() < count) {
    deque.insert(this->end(), count - deque.size(), value);
  }
  this->swap(deque);
}

template <typename T, typename Allocator>
void Deque<T, Allocator>::swap(Deque& other) {
  std::swap(this->_nodes, other._nodes);
  std::swap(this->_nodes_size, other._nodes_size);
  std::swap(this->_first_node, other._first_node);
  std::swap(this->_first_cell, other._first_cell);
  std::swap(this->_last_node, other._last_node);
  std::swap(this->_last_cell, other._last_cell);
  std::swap(this->_alloc, other._alloc);
  std::swap(this->_nalloc, other._nalloc);
  std::swap(this->_size, other._size);
}

template<class T, class Alloc>
auto Deque<T, Alloc>::operator<=>(const Deque& other) const {
    if (auto cmp = this->size() <=> other.size(); cmp != 0) {
      return cmp;
    }
    auto itl = this->begin();
    auto itr = other.begin();
    for (; itl != this->end(); ++itl, ++itr) {
      if (auto cmp = *itl <=> *itr; cmp != 0) {
        return cmp;
      }
    }
    return this->size() <=> other.size();
}

template<class T, class Alloc>
bool Deque<T, Alloc>::operator==(const Deque& other) const {
  return !((*this < other) || (*this > other));
}

template<class T, class Alloc>
bool Deque<T, Alloc>::operator!=(const Deque& other) const {
  return !(*this == other);
}

template <class T, class Alloc>
void swap(Deque<T, Alloc>& lhs, Deque<T, Alloc>& rhs) {
  lhs.swap(rhs);
}

template <class T, class Alloc, class U>
typename Deque<T, Alloc>::size_type erase(Deque<T, Alloc>& c, const U& value) {
  typename Deque<T, Alloc>::size_type number = 0;
  for (auto it = c.begin(); it != c.end(); ++it) {
    if (*it == value) {
      it = c.erase(it) - 1;
      ++number;
    }
  }
  return number;
}

template <class T, class Alloc, class Pred>
typename Deque<T, Alloc>::size_type erase_if(Deque<T, Alloc>& c, Pred pred) {
  typename Deque<T, Alloc>::size_type number = 0;
  for (auto it = c.begin(); it != c.end(); ++it) {
    if (pred(*it)) {
      it = c.erase(it) - 1;
      ++number;
    }
  }
  return number;
}

}  // namespace fefu_laboratory_two