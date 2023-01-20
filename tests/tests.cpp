#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// #include "Deque.hpp"
#include <string>
#include <tuple>
#include <vector>

#include "Deque.cpp"  //костыль. надо симейк пофиксить

TEMPLATE_TEST_CASE("deque can be created", "[deque][constructor]", int,
                   std::string, (std::tuple<int, char>)) {
  using namespace fefu_laboratory_two;

  SECTION("default constructor") {
    Deque<TestType> d;

    REQUIRE(d.size() == 0);
  }

  SECTION("with allocator") {
    Allocator<TestType> alloc;

    Deque<TestType> d(alloc);

    REQUIRE(d.size() == 0);
  }

  SECTION("with start default values") {
    size_t size = 1000;
    Deque<TestType> d(size);

    REQUIRE(d.size() == size);
    for (auto it = d.begin(); it != d.end(); ++it) {
      REQUIRE(*it == TestType());
    }
  }

  SECTION("with start values") {
    size_t size = 1000;
    Deque<TestType> d(size, TestType());

    REQUIRE(d.size() == size);
    for (auto it = d.begin(); it != d.end(); ++it) {
      REQUIRE(*it == TestType());
    }
  }

  SECTION("with initialize iterators") {
    std::vector<int> v = {1, 3, 5, 7, 9, 11};

    Deque<int> d(v.begin(), v.end());
    auto it1 = d.begin();
    auto it2 = v.begin();

    REQUIRE(d.size() == v.size());
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }

  SECTION("with other deque") {
    std::vector<int> v = {1, 3, 5, 7, 9, 11};
    Deque<int> other(v.begin(), v.end());

    Deque<int> d(other);
    auto it1 = d.begin();
    auto it2 = other.begin();

    REQUIRE(d.size() == other.size());
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
    // REQUIRE( d == other );
  }

  SECTION("with other deque and allocator") {
    std::vector<int> v = {1, 3, 5, 7, 9, 11};
    Deque<int> other(v.begin(), v.end());
    Allocator<int> alloc;

    Deque<int> d(other, alloc);
    auto it1 = d.begin();
    auto it2 = other.begin();

    REQUIRE(d.size() == other.size());
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }

  SECTION("with move other deque") {
    std::vector<int> v = {1, 3, 5, 7, 9, 11};
    Deque<int> other(v.begin(), v.end());
    size_t size = other.size();

    Deque<int> d(std::move(other));
    auto it1 = d.begin();
    auto it2 = v.begin();

    REQUIRE(d.size() == size);
    REQUIRE(other.size() == 0);
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }

  SECTION("with move other deque") {
    std::vector<int> v = {1, 3, 5, 7, 9, 11};
    Deque<int> other(v.begin(), v.end());
    size_t size = other.size();
    Allocator<int> alloc;

    Deque<int> d(std::move(other), alloc);
    auto it1 = d.begin();
    auto it2 = v.begin();

    REQUIRE(d.size() == size);
    REQUIRE(other.size() == 0);
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }

  SECTION("with initializer list") {
    std::initializer_list<int> list = {10, 4, 34, 100, -70, 9};

    Deque<int> d(list);
    auto it1 = d.begin();
    auto it2 = list.begin();

    REQUIRE(d.size() == list.size());
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }
}

TEST_CASE("deque can be copied and moved", "[deque][copy][move]") {
  using namespace fefu_laboratory_two;

  SECTION("copy other deque elements") {
    std::vector<int> v = {1, 3, 5, 7, 9, 11};
    Deque<int> other(v.begin(), v.end());
    Deque<int> d({1, 2, 3});

    d = other;
    auto it1 = d.begin();
    auto it2 = other.begin();

    REQUIRE(d.size() == other.size());
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }

  SECTION("move other deque elements") {
    std::vector<int> v = {1, 3, 5, 7, 9, 11};
    Deque<int> other(v.begin(), v.end());
    Deque<int> d({1, 2, 3});
    size_t size = other.size();

    d = other;
    auto it1 = d.begin();
    auto it2 = v.begin();

    REQUIRE(d.size() == size);
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }

  SECTION("copy initializer list") {
    std::initializer_list<int> list = {10, 4, 34, 100, -70, 9};
    Deque<int> d;

    d = list;
    auto it1 = d.begin();
    auto it2 = list.begin();

    REQUIRE(d.size() == list.size());
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }
}

TEST_CASE("deque can assign elements", "[deque][assign]") {
  using namespace fefu_laboratory_two;

  SECTION("assign count copies") {
    size_t count = 1001;
    std::string value = "str";
    Deque<std::string> d;

    d.assign(count, value);

    REQUIRE(d.size() == count);
    for (auto it = d.begin(); it != d.end(); ++it) {
      REQUIRE(*it == value);
    }
  }

  SECTION("assign values from range") {
    std::vector<char> v = {'f', 's', 'a', 'n', 'v', 'r'};
    Deque<char> d({'s', 'o', 'c'});

    d.assign(v.begin(), v.end());
    auto it1 = d.begin();
    auto it2 = v.begin();

    REQUIRE(d.size() == v.size());
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }

  SECTION("assign values from initializer list") {
    std::initializer_list<char> v = {'f', 's', 'a', 'n', 'v', 'r'};
    Deque<char> d({'r', 'a', 'w'});

    d.assign(v.begin(), v.end());
    auto it1 = d.begin();
    auto it2 = v.begin();

    REQUIRE(d.size() == v.size());
    for (; it1 != d.end(); ++it1, ++it2) {
      REQUIRE(*it1 == *it2);
    }
  }
}

TEST_CASE("possible to access deque elements", "[deque][at][front][back]") {
  using namespace fefu_laboratory_two;

  SECTION("at method access") {
    Deque<int> d = {0, 1, 2, 3, 4, 5, 6, 7};

    SECTION("valid pos") {
      size_t pos = 0;

      REQUIRE_NOTHROW(d.at(pos));
    }

    SECTION("invalid pos") {
      size_t pos = d.size();

      REQUIRE_THROWS_AS(d.at(pos), std::out_of_range);
    }
  }

  SECTION("operator[] access") {
    Deque<int> d = {0, 1, 2, 3, 4, 5, 6, 7};

    SECTION("valid pos") {
      size_t pos = 0;

      REQUIRE_NOTHROW(d[pos]);
    }

    SECTION("invalid pos") {
      size_t pos = d.size();

      REQUIRE_THROWS_AS(d[pos], std::out_of_range);
    }
  }

  SECTION("front element") {
    Deque<int> d = {0, 1, 2, 3, 4, 5, 6, 7};

    auto ref = d.front();

    REQUIRE(ref == 0);
  }

  SECTION("back element") {
    Deque<int> d = {0, 1, 2, 3, 4, 5, 6, 7};

    auto ref = d.back();

    REQUIRE(ref == 7);
  }
}

TEST_CASE("deque can be iterated", "[begin][end][iterator][reverse_iterator]") {
  using namespace fefu_laboratory_two;

  SECTION("begin iterator") {
    Deque<int> d = {0, 1, 2, 3, 4, 5, 6, 7};

    auto it = d.begin();

    REQUIRE(*it == 0);
  }

  SECTION("end iterator") {
    Deque<int> d = {0, 1, 2, 3, 4, 5, 6, 7};

    auto it = d.end();

    REQUIRE(*(it - 1) == 7);
  }

  SECTION("begin == end with empty deque") {
    Deque<double> d;

    auto begin = d.begin();
    auto end = d.end();

    REQUIRE(begin == end);
  }

  SECTION("rbegin iterator") {
    Deque<int> d = {0, 1, 2, 3, 4, 5, 6, 7};

    auto it = d.rbegin();

    REQUIRE(*it == 7);
  }

  SECTION("rend iterator") {
    Deque<int> d = {0, 1, 2, 3, 4, 5, 6, 7};

    auto it = d.rend();

    REQUIRE(*(it - 1) == 0);
  }

  SECTION("rbegin == rend with empty deque") {
    Deque<double> d;

    auto rbegin = d.rbegin();
    auto rend = d.rend();

    REQUIRE(rbegin == rend);
  }
}

TEMPLATE_TEST_CASE("deque has capacity", "[empty][size]", int, double,
                   std::string, std::vector<int>) {
  using namespace fefu_laboratory_two;

  SECTION("can be empty") {
    Deque<TestType> d;

    REQUIRE(d.size() == 0);
    REQUIRE(d.empty());
  }

  SECTION("can be not empty") {
    size_t size = 100000;
    Deque<TestType> d(size);

    REQUIRE(d.size() == size);
    REQUIRE_FALSE(d.empty());
  }
}

TEST_CASE(
    "deque can be modified",
    "[insert][emplace][push_back][emplace_back][push_front][emplace_front]"
    "[pop_back][pop_front][erase][resize][swap][clear]") {
  using namespace fefu_laboratory_two;

  SECTION("add elements") {
    SECTION("insert value to random pos") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto pos = GENERATE(range(0, 10 - 1));

      SECTION("insert") {
        auto old_pos = d.begin() + pos;
        int value = *old_pos - 5;

        d.insert(old_pos, value);
        auto new_pos = d.begin() + pos;

        REQUIRE(*new_pos == value);
      }
    }

    SECTION("insert value to begin") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto old_pos = d.begin();
      int value = -5;

      d.insert(old_pos, value);
      auto new_pos = d.begin();

      REQUIRE(*new_pos == value);
    }

    SECTION("insert value to end") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto old_pos = d.end();
      int value = 95;

      d.insert(old_pos, value);
      auto new_pos = d.end() - 1;

      REQUIRE(*new_pos == value);
    }

    SECTION("insert count values to random pos") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto pos =
          GENERATE(range(static_cast<size_t>(0), static_cast<size_t>(10 - 1)));
      auto count =
          GENERATE(range(static_cast<size_t>(0), static_cast<size_t>(100)));

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.begin() + pos;
        int value = 10;

        auto new_pos = d.insert(old_pos, count, value);

        REQUIRE(d.size() == old_size + count);
        for (auto it = new_pos; it != (new_pos + count); ++it) {
          REQUIRE(*it == value);
        }
      }
    }

    SECTION("insert count values to begin") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto count =
          GENERATE(range(static_cast<size_t>(0), static_cast<size_t>(100)));

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.begin();
        int value = 10;

        auto new_pos = d.insert(old_pos, count, value);

        REQUIRE(d.size() == old_size + count);
        for (auto it = new_pos; it != (new_pos + count); ++it) {
          REQUIRE(*it == value);
        }
      }
    }

    SECTION("insert count values to end") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto count =
          GENERATE(range(static_cast<size_t>(0), static_cast<size_t>(100)));

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.end();
        int value = 10;

        auto new_pos = d.insert(old_pos, count, value);

        REQUIRE(d.size() == old_size + count);
        for (auto it = new_pos; it != d.end(); ++it) {
          REQUIRE(*it == value);
        }
      }
    }

    SECTION("insert range to random pos") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto pos =
          GENERATE(range(static_cast<size_t>(0), static_cast<size_t>(10 - 1)));
      std::initializer_list<int> list = {41, 51, 61, 71};

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.begin() + pos;

        auto new_pos = d.insert(old_pos, list.begin(), list.end());
        auto it1 = new_pos;
        auto it2 = list.begin();

        REQUIRE(d.size() == old_size + list.size());
        for (; it1 != (new_pos + list.size()); ++it1, ++it2) {
          REQUIRE(*it1 == *it2);
        }
      }
    }

    SECTION("insert range to begin") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      std::initializer_list<int> list = {41, 51, 61, 71};

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.begin();

        auto new_pos = d.insert(old_pos, list.begin(), list.end());
        auto it1 = new_pos;
        auto it2 = list.begin();

        REQUIRE(d.size() == old_size + list.size());
        for (; it1 != (new_pos + list.size()); ++it1, ++it2) {
          REQUIRE(*it1 == *it2);
        }
      }
    }

    SECTION("insert range to end") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      std::initializer_list<int> list = {41, 51, 61, 71};

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.end();

        auto new_pos = d.insert(old_pos, list.begin(), list.end());
        auto it1 = new_pos;
        auto it2 = list.begin();

        REQUIRE(d.size() == old_size + list.size());
        for (; it1 != (new_pos + list.size()); ++it1, ++it2) {
          REQUIRE(*it1 == *it2);
        }
      }
    }

    SECTION("insert initializer list to random pos") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto pos =
          GENERATE(range(static_cast<size_t>(0), static_cast<size_t>(10 - 1)));
      std::initializer_list<int> list = {41, 51, 61, 71};

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.begin() + pos;

        auto new_pos = d.insert(old_pos, list);
        auto it1 = new_pos;
        auto it2 = list.begin();

        REQUIRE(d.size() == old_size + list.size());
        for (; it1 != (new_pos + list.size()); ++it1, ++it2) {
          REQUIRE(*it1 == *it2);
        }
      }
    }

    SECTION("insert initializer list to begin") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      std::initializer_list<int> list = {41, 51, 61, 71};

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.begin();

        auto new_pos = d.insert(old_pos, list);
        auto it1 = new_pos;
        auto it2 = list.begin();

        REQUIRE(d.size() == old_size + list.size());
        for (; it1 != (new_pos + list.size()); ++it1, ++it2) {
          REQUIRE(*it1 == *it2);
        }
      }
    }

    SECTION("insert initializer list to end") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      std::initializer_list<int> list = {41, 51, 61, 71};

      SECTION("insert") {
        size_t old_size = d.size();
        auto old_pos = d.end();

        auto new_pos = d.insert(old_pos, list);
        auto it1 = new_pos;
        auto it2 = list.begin();

        REQUIRE(d.size() == old_size + list.size());
        for (; it1 != (new_pos + list.size()); ++it1, ++it2) {
          REQUIRE(*it1 == *it2);
        }
      }
    }

    SECTION("push_back") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      size_t old_size = d.size();
      int value = 100;

      d.push_back(value);

      REQUIRE(d.size() == old_size + 1);
      REQUIRE(d.back() == value);
    }

    SECTION("emplace_back") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      size_t old_size = d.size();
      std::initializer_list<int> list = {10, 20, 30, 40};

      d.emplace_back(10, 20, 30, 40);
      auto it1 = d.begin() + old_size;
      auto it2 = list.begin();

      REQUIRE(d.size() == old_size + list.size());
      for (; it1 != d.end(); ++it1, ++it2) {
        REQUIRE(*it1 == *it2);
      }
    }

    SECTION("push_front") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      size_t old_size = d.size();
      int value = -10;

      d.push_front(value);

      REQUIRE(d.size() == old_size + 1);
      REQUIRE(d.front() == value);
    }

    /*SECTION( "emplace_front" ) {
        Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
        size_t old_size = d.size();
        std::initializer_list<int> list = {10, 20, 30, 40};

        d.emplace_front(10, 20, 30, 40);
        auto it1 = d.begin();
        auto it2 = list.begin();

        REQUIRE( d.size() == old_size + list.size() );
        for (; it1 != d.begin() + list.size(); ++it1, ++it2) {
          REQUIRE( *it1 == *it2 );
        }
    }*/
  }

  SECTION("delete elements") {
    SECTION("erase elements from random pos") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto pos = GENERATE(range(0, 10 - 1));

      SECTION("erase") {
        auto old_pos = d.begin() + pos;
        int value = *old_pos;
        size_t old_size = d.size();

        auto erase_pos = d.erase(old_pos);

        REQUIRE(d.size() == old_size - 1);
      }
    }

    SECTION("erase elements from begin") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};

      SECTION("erase") {
        auto old_pos = d.begin();
        int value = *old_pos;
        size_t old_size = d.size();

        auto erase_pos = d.erase(old_pos);

        REQUIRE(d.size() == old_size - 1);
      }
    }

    SECTION("erase elements from back") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};

      SECTION("erase") {
        auto old_pos = d.end() - 1;
        int value = *old_pos;
        size_t old_size = d.size();

        auto erase_pos = d.erase(old_pos);

        REQUIRE(d.size() == old_size - 1);
      }
    }

    SECTION("erase range from random pos") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      auto pos1 = GENERATE(range(0, 5));
      auto pos2 = GENERATE(range(5, 10 - 1));

      SECTION("erase") {
        auto old_pos1 = d.begin() + pos1;
        auto old_pos2 = d.begin() + pos2;
        size_t old_size = d.size();

        auto erase_pos = d.erase(old_pos1, old_pos2);

        REQUIRE(d.size() == old_size - (old_pos2 - old_pos1));
      }
    }

    SECTION("pop_back") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      Deque<int> res = {0, 10, 20, 30, 40, 50, 60, 70, 80};
      size_t old_size = d.size();

      d.pop_back();

      REQUIRE(d.size() == old_size - 1);
      REQUIRE(d == res);
    }

    SECTION("pop_front") {
      Deque<int> d = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90};
      Deque<int> res = {10, 20, 30, 40, 50, 60, 70, 80, 90};
      size_t old_size = d.size();

      d.pop_front();

      REQUIRE(d.size() == old_size - 1);
      REQUIRE(d == res);
    }

    SECTION( "erase function" ) {
      Deque<int> d = {3, 3, 4, 5, 3, 7, 3, 9};
      Deque<int> res = {4, 5, 7, 9};
      int value = 3;

      erase(d, value);

      REQUIRE( d.size() == res.size() );
      REQUIRE( d == res);
    }

        SECTION( "erase_if function" ) {
      Deque<int> d = {3, 3, 4, 5, 3, 7, 3, 9};
      Deque<int> res = {4, 5, 7};
      auto pred = [](int v){ return (v % 3) == 0; };

      erase_if(d, pred);

      REQUIRE( d.size() == res.size() );
      REQUIRE( d == res);
    }
  }

  SECTION("resize and swap") {
    SECTION( "resize: current < count" ) {
      Deque<int> ref_deque = {10, 20, 30, 40, 50, 60, 70, 80};
      size_t old_size = ref_deque.size();
      size_t expect_size = ref_deque.size() * 2 + 1;

      Deque<int> d = ref_deque;
      d.resize(expect_size);
      auto it1 = d.begin();
      auto it2 = ref_deque.begin();

      REQUIRE( d.size() == expect_size );
      for (; it2 != ref_deque.end(); ++it1, ++it2) {
        REQUIRE( *it1 == *it2 );
      }
      for (auto it = d.begin() + ref_deque.size(); it != d.end(); ++it) {
        REQUIRE( *it == int() );
      }
    }

        SECTION( "resize: current < count with value" ) {
      Deque<int> ref_deque = {10, 20, 30, 40, 50, 60, 70, 80};
      size_t old_size = ref_deque.size();
      size_t expect_size = ref_deque.size() * 2 + 1;
      int value = -9;

      Deque<int> d = ref_deque;
      d.resize(expect_size, value);
      auto it1 = d.begin();
      auto it2 = ref_deque.begin();

      REQUIRE( d.size() == expect_size );
      for (; it2 != ref_deque.end(); ++it1, ++it2) {
        REQUIRE( *it1 == *it2 );
      }
      for (auto it = d.begin() + ref_deque.size(); it != d.end(); ++it) {
        REQUIRE( *it == value );
      }
    }

    SECTION( "resize: current > count" ) {
      Deque<int> ref_deque = {10, 20, 30, 40, 50, 60, 70, 80};
      size_t old_size = ref_deque.size();
      size_t expect_size = ref_deque.size() / 2;

      Deque<int> d = ref_deque;
      d.resize(expect_size);
      auto it1 = d.begin();
      auto it2 = ref_deque.begin();

      REQUIRE( d.size() == expect_size );
      for (; it1 != d.end(); ++it1, ++it2) {
        REQUIRE( *it1 == *it2 );
      }
    }

    SECTION( "resize: current == count" ) {
      Deque<int> ref_deque = {10, 20, 30, 40, 50, 60, 70, 80};
      size_t old_size = ref_deque.size();
      size_t expect_size = ref_deque.size();

      Deque<int> d = ref_deque;
      d.resize(expect_size);

      REQUIRE( d.size() == expect_size );
      REQUIRE( d == ref_deque);
    }

    SECTION( "swap method" ) {
      Deque<int> d1 {10, 20, 30};
      Deque<int> d2;
      auto it = d1.begin() + 1;
      int& ref = *it;

      Deque<int> test1 = d1;
      Deque<int> test2 = d2;
      test1.swap(test2);

      REQUIRE( ref == *it );
      REQUIRE( test1 == d2 );
      REQUIRE( test2 == d1 );
    }

    SECTION( "swap function" ) {
      Deque<int> d1 {10, 20, 30};
      Deque<int> d2;
      auto it = d1.begin() + 1;
      int& ref = *it;

      Deque<int> test1 = d1;
      Deque<int> test2 = d2;
      swap(test1, test2);

      REQUIRE( ref == *it );
      REQUIRE( test1 == d2 );
      REQUIRE( test2 == d1 );
    }
  }
}