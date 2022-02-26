#include <assert.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

class Obj {
 public:
  Obj() { cout << "default construct obj " << endl; }
  Obj(int x) : x_(x) { cout << "paramter construct obj" << endl; }
  Obj(Obj &&obj) {
    cout << "move construct obj" << endl;
    this->x_ = obj.x_;
  }
  Obj &operator=(const Obj &obj) {
    this->x_ = obj.x_;
    cout << "assign construct obj " << endl;
    return *this;
  }

  ~Obj() {}

 private:
  int x_;
};

template <typename T>
void print_vector(vector<T> arr) {
  if (arr.size() == 0) {
    return;
  }

  for (auto p : arr) {
    cout << p << " " << endl;
  }
}

int add_2(int x) { return x + 2; }

struct adder {
  adder(int n) : n_(n) {}
  int operator()(int x) const { return x + n_; }

 private:
  int n_;
};

int get_count() {
  static int count = 0;
  return ++count;
}

class Task {
 public:
  Task(int data) : data_(data) {}
  auto lazy_lunch() {
    return [this, count = get_count()]() mutable {
      ostringstream oss;
      oss << "Done work " << data_ << " (No. " << count << ") in thread "
          << this_thread::get_id() << "\n";
      msg_ = oss.str();
      caculate();
    };
  }

  void caculate() {
    this_thread::sleep_for(100ms);
    cout << msg_;
  }

  string get_msg() { return msg_; }

 private:
  int data_;
  string msg_;
};

std::map<string, function<int(int, int)>> op_dict{
    {"+", [](int x, int y) { return x + y; }},
    {"-", [](int x, int y) { return x - y; }},
    {"*", [](int x, int y) { return x * y; }},
    {"/", [](int x, int y) {
       assert(y != 0);
       return x / y;
     }}};

int main() {
  // auto t = Task{11};
  // thread t1 {t.lazy_lunch()};
  // thread t2 {t.lazy_lunch()};

  // t1.join();
  // t2.join();

  // cout << t.get_msg() << endl;

  // std::array<int,5> a{1,2,3,4,5};
  // auto s = accumulate(
  //    a.begin(), a.end(), 1,
  //    [](int x, int y) {
  //        return x * y;
  //    }
  // );

  // cout << s << endl;

  cout << op_dict["+"](1, 2) << endl;
  //     int init_mode = 1;
  //     cout << "ordinary construct : " << endl;
  //     Obj obj;
  //     switch (init_mode)
  //     {
  //     case 1:
  //         obj = Obj(2);
  //         break;
  //    default:
  //         break;
  //     }

  //     cout << "lamda construct : " << endl;
  //     auto obj_lamda = [init_mode]() {
  //         switch (init_mode)
  //         {
  //         case 1:
  //             return Obj(2);
  //             break;
  //        default:
  //             break;
  //         }
  //     }();

  // vector <int> arr = {1,2,3,4,5};
  // transform(arr.begin(), arr.end(),
  //           arr.begin(),
  //           bind2nd(plus<int>(),2));

  // print_vector(arr);

  // auto adder = [](int x) {
  //     return [x](int n) {
  //         return x + n;
  //     };
  // };

  // auto adder_2 = [](int x) {
  //     return x + 2;
  // };

  // // auto adder_2 = adder(2);
  // cout << "add_2 + 5 = " <<  add_2(5) << endl;
  // cout << "adder 3 + 5 = " << adder(3)(5) << endl;

  // auto res = [](int x) {
  //     return x * x;
  // }(9);
  // cout << res << endl;

  return 0;
}