#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "../include/chan/chan.hpp"

#define BAR_MAX_WIDTH 38

std::string repeat(std::string s, int n) {
    std::string s1 = s;

    for (int i = 1; i < n; i++)
        s += s1;

    return s;
}

void show_progress_bar(recv_chan<bool>& rx, int n_tasks) {
    bool value;
    int bar_width, loop_index {0};
    float progress;

    while (rx >> value) {
        loop_index++;
        bar_width =  BAR_MAX_WIDTH * loop_index / n_tasks;
        progress = float(loop_index) / float(n_tasks) * 100;

        const std::string bar = repeat("|", bar_width) + repeat("-", BAR_MAX_WIDTH - bar_width);
        std::cout << "[" << bar << "] " << progress << " %    \r";
        
        if (loop_index == n_tasks)
            return;
    }
}

void worker(send_chan<bool>& tx, int i) {
    // heavy calculation of any type
    std::this_thread::sleep_for(std::chrono::milliseconds(i));

    // send done status to chan
    tx << true;
}

int main() {
    auto [tx, rx] = chanpair::get_new<bool>();
    int n_tasks {150};

    std::vector<std::thread> threads;

    for (int i = 0; i < n_tasks; i++)
        threads.emplace_back(worker, std::ref(tx), i);

    std::cout << "Starting " << n_tasks << " tasks\n\n";
    show_progress_bar(rx, n_tasks);

    for (auto& th: threads)
        th.join();
        
    std::cout << "\n\n";
    return 0;
}