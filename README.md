# 🧵 Golang and Rust's `chan` inside C++
The `chan` class brings the simplicity and elegance of both Golang-style and Rust-style channels into modern C++, offering an intuitive and type-safe way to pass messages between threads. Unlike traditional synchronization primitives, such as mutexes and condition variables, `chan` abstracts away the complexity, allowing developers to focus on communication rather than coordination.

## 🧪 Class Overview
At its core, `chan` uses a `std::queue` to store transmitted values and synchronizes access using a `std::mutex`.
Use `>>` operator to read data from a channel and `<<` operator to write data to it. 

## 🚀 Key Features
- Thread-safe messaging between threads
- Blocking reads that wait for data to be available
- Support for both bidirectional and unidirectional channels
- Clean, modern C++ interface via operator overloading
- Header-only and dependency-light

## 💡 How to Use chan
### Install using CMake
```cmake
cmake_minimum_required(VERSION 3.14)

PROJECT(myproject)

# fetch latest chan
include(FetchContent)
FetchContent_Declare(
    chan
    GIT_REPOSITORY https://github.com/giovanni-iannaccone/chan.git
)
FetchContent_MakeAvailable(chan)

add_executable(myproject main.cpp)
target_link_libraries(myproject chan)
```

### Include `chan` in your project
```cpp
#include <chan/chan.hpp>
```

### Usage Example
Look `examples` folder to see usage examples

1. Unidirectional (Rust-style)
```cpp
auto [tx, rx] = chanpair::get_new<int>();
```
Use `tx` to send data and `rx` to receive it.

2. Bidirectional (Golang-style)
```cpp
chan<int> ch;
```
Use `ch` for both sending and receiving data.

## 🧩 Contributing
We welcome contributions! Please follow these steps:

1. Fork the repository.
2. Create a new branch ( using <a href="https://medium.com/@abhay.pixolo/naming-conventions-for-git-branches-a-cheatsheet-8549feca2534">this</a> convention).
3. Make your changes and commit them with descriptive messages.
4. Push your changes to your fork.
5. Create a pull request to the main repository.

## ⚖ License
This project is licensed under the GPL-3.0 License. See the LICENSE file for details.

## ⚔ Contact
- For any inquiries or support, please contact <a href="mailto:iannacconegiovanni444@gmail.com"> iannacconegiovanni444@gmail.com </a>.
- Visit my site for more informations about me and my work <a href="https://giovanni-iannaccone.gith
ub.io" target=”_blank” rel="noopener noreferrer"> https://giovanni-iannaccone.github.io </a>