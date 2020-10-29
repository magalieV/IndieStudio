/*
 * Project Name = bomberman
 *
 * Author = ${GROUP_DEV}
 * Object = Core
 *
 * File creation = 06/06/2020
 * Last modification = 06/06/2020
 */

#ifndef __BOMBERMAN_CORE_HPP__
#define __BOMBERMAN_CORE_HPP__

#include "Window.hpp"

namespace indie::engine {
    class Core {
        public:
            Core();
            ~Core();
            Core(const Core &other) = delete;
            Core(const Core && other) = delete;
            Core& operator=(const Core &other) = delete;
            void run() const;

        private:
            void run_menu() const;
            void run_game() const;

        private:
            indie::object::Window *_device;
    };
}

#endif //__BOMBERMAN_CORE_HPP__
