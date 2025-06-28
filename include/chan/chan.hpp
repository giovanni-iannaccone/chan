#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
#include <memory>
#include <stdexcept>
#include <utility>

template<typename T>
struct ChanState {
    std::mutex               mtx;
    std::condition_variable  cv;
    std::queue<T>            q;
};

template<typename T>
class chan {

public:
    std::shared_ptr<ChanState<T>> st;

    chan()
      : st(std::make_shared<ChanState<T>>())
    {}

    chan(std::shared_ptr<ChanState<T>> state)
      : st(std::move(state))
    {}

    ~chan() = default;

    virtual void operator<<(T value) {
        std::lock_guard lock(st->mtx);
        st->q.push(std::move(value));
        st->cv.notify_all();
    }

    virtual bool operator>>(T &out) {
        std::unique_lock lock(st->mtx);
        st->cv.wait(lock, [&]{ 
            return !st->q.empty(); 
        });

        out = std::move(st->q.front());
        st->q.pop();
        return true;
    }
};

template<typename T>
class send_chan : public chan<T> {

public:
    send_chan(std::shared_ptr<ChanState<T>> state)
      : chan<T>(std::move(state))
    {}

    bool operator>>(T&) override {
        throw std::logic_error("can't receive (>>) using send_chan");
    }
};

template<typename T>
class recv_chan : public chan<T> {

public:
    recv_chan(std::shared_ptr<ChanState<T>> state)
      : chan<T>(std::move(state))
    {}

    void operator<<(T) override {
        throw std::logic_error("can't send (<<) using recv_chan");
    }
};


class chanpair {

public:
    template<typename T>
    static std::pair< send_chan<T>, recv_chan<T> > get_new() {
        auto state = std::make_shared<ChanState<T>>();

        auto tx = send_chan<T>(state);
        auto rx = recv_chan<T>(state);

        return {
            std::move(tx),
            std::move(rx)
        };
    }
};
