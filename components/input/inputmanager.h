#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <functional>

#include <boost/lockfree/spsc_queue.hpp>

#include "keys.h"

#include <fa_nuklear.h>


namespace Input
{
    enum Modifier
    {
        FAMOD_CTRL = 1,
        FAMOD_ALT = 2,
        FAMOD_SHIFT = 4
    };

    class InputManager
    {
        public:
            InputManager(std::function<void(Key)> keyPress, std::function<void(Key)> keyRelease,
                std::function<void(uint32_t, uint32_t, Key, bool)> mouseClick,
                std::function<void(uint32_t, uint32_t, Key)> mouseRelease,
                std::function<void(uint32_t, uint32_t, uint32_t, uint32_t)> mouseMove,
                std::function<void(std::string)> textInput);

            void processInput(bool paused);
            void poll();

            uint32_t getModifiers();

            static InputManager* get();

        private:
            
            ///< Basically a copy of the subset of SDL_Event that we actually use
            struct Event
            {
                size_t type;

                union _vals
                {
                    int32_t key;
                    
                    struct _mouseButton
                    {
                        int32_t key;
                        int32_t x;
                        int32_t y;
                        int32_t numClicks;
                    } mouseButton;

                    struct _mouseMove
                    {
                        int32_t x;
                        int32_t y;
                        int32_t xrel;
                        int32_t yrel;
                    } mouseMove;

                    struct _textInput
                    {
                        std::string* text;
                    } textInput;

                } vals;
            };

            boost::lockfree::spsc_queue<Event, boost::lockfree::capacity<500> > mQueue;
            std::function<void(Key)> mKeyPress;
            std::function<void(Key)> mKeyRelease;
            std::function<void(uint32_t, uint32_t, Key, bool)> mMouseClick;
            std::function<void(uint32_t, uint32_t, Key)> mMouseRelease;
            std::function<void(uint32_t, uint32_t, uint32_t, uint32_t)> mMouseMove;
            std::function<void(std::string)> mTextInput;

            static InputManager* instance;

            uint32_t mModifiers;
    };
}

#endif
