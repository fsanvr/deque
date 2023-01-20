#include "Deque.cpp"

#include <iostream>
#include <deque>

int main() { 
  int** arr = new int*[8];
  for (auto i = 0; i < 8; ++i) {
    arr[i] = new int[32];
    for (auto j = 0; j < 32; ++j) {
      arr[i][j] = i * 100 + j;
    }
  }

  {
    fefu_laboratory_two::Deque<int> d;
    std::cout << d.max_size() << std::endl;
    for (int i = 0; i < 120; ++i) {
      d.push_back(i * 10);
    }
    for (int i = 0; i < 40; ++i) {
      d.pop_back();
      d.pop_front();
    }
    for (int i = 1; i < 100; ++i) {
      d.push_front(i * 1000);
    }
    d.emplace_back(1, 6, 4, 9);

    for (auto it = d.begin(); it != d.end(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    for (auto it = d.cbegin(); it != d.cend(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    for (auto it = d.end() - 1; it >= d.begin(); --it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    for (auto it = d.rbegin(); it != d.rend(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    fefu_laboratory_two::Deque<int> dd(d);

    std::cout << d.at(10) << std::endl;

    for (auto it = d.crbegin(); it != d.crend(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
  }

  {
    fefu_laboratory_two::Deque_iterator<int> i1(arr, 0, 2, 32);
    fefu_laboratory_two::Deque_iterator<int> i2(arr, 1, 20, 32);
    std::cout << (i1 - i2) << std::endl;

    fefu_laboratory_two::Deque_const_iterator<int> i3(i1);
    fefu_laboratory_two::Deque_const_iterator<int> i4(i2);
    std::cout << (i3 - i4) << std::endl << std::endl;
    std::cout << *(i3++) << std::endl << std::endl;
  }

  {
    fefu_laboratory_two::Deque_iterator<int> i1(arr, 0, 20, 32);
    fefu_laboratory_two::Deque_iterator<int> i2(arr, 1, 2, 32);
    std::cout << (i1 - i2) << std::endl;

    fefu_laboratory_two::Deque_const_iterator<int> i3(i1);
    fefu_laboratory_two::Deque_const_iterator<int> i4(i2);
    std::cout << (i3 - i4) << std::endl << std::endl;
  }

  {
    fefu_laboratory_two::Deque_iterator<int> i1(arr, 0, 31, 32);
    fefu_laboratory_two::Deque_iterator<int> i2(arr, 1, 15, 32);
    fefu_laboratory_two::Deque_iterator<int> i3(arr, 1, 0, 32);
    std::cout << *(++i1) << std::endl;
    std::cout << *(++i2) << std::endl;
    std::cout << *(i3++) << std::endl;

    fefu_laboratory_two::Deque_const_iterator<int> i4(i1);
    fefu_laboratory_two::Deque_const_iterator<int> i5(i2);
    fefu_laboratory_two::Deque_const_iterator<int> i6(i3);
    std::cout << *(++i4) << std::endl;
    std::cout << *(++i5) << std::endl;
    std::cout << *(i6++) << std::endl << std::endl;
  }

  {
    fefu_laboratory_two::Deque<int> d = {1, 3, 5};
    for (auto it = d.begin(); it != d.end(); ++it) {
      std::cout << *it << ' ';
    }
    std::cout << std::endl;

    std::cout << (*(d.insert(d.end(), 7)) == 7) << std::endl;

    for (auto it = d.begin(); it != d.end(); ++it) {
      std::cout << *it << ' ';
    }
    std::cout << std::endl;

    auto it = d.end();
    std::cout << (d.insert(d.end() - 2, {10, 10, 10, 10}) == (it + 1)) << std::endl;
    for (auto it = d.begin(); it != d.end(); ++it) {
      std::cout << *it << ' ';
    }
    std::cout << std::endl;

    fefu_laboratory_two::erase_if(d, [](int i){ return i == 10; });

    for (auto it = d.begin(); it != d.end(); ++it) {
      std::cout << *it << ' ';
    }
    std::cout << std::endl;
  }
  
  
  for (auto i = 0; i < 8; ++i) {
    delete[] arr[i];
  }
  delete[] arr;

  std::cout << "hh" << std::endl;
  
  return 0;
}