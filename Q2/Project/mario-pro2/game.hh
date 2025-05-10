#ifndef GAME_HH
#define GAME_HH

#include <vector>
#include <list>
#include "mario.hh"
#include "platform.hh"
#include "coin.hh"
#include "window.hh"
#include "utils.hh"

class Game {
    Mario                 mario_;
    Mario                 mario2_;
    std::vector<Platform> platforms_;
    std::list<Coin> coins_;

    bool finished_;
    bool paused_;
    int num_coins_;

    void process_keys(pro2::Window& window);
    void update_objects(pro2::Window& window);
    void update_camera(pro2::Window& window);

 public:
    Game(int width, int height);

    void update(pro2::Window& window);
    void paint(pro2::Window& window);

    bool is_finished() const {
        return finished_;
    }

 private:
    static constexpr int sky_blue = 0x5c94fc;
};

#endif