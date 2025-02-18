//
// Created by ryen on 12/29/24.
//

#ifndef MECORE_H
#define MECORE_H

namespace me {
    enum class MECoreSystems {
        None = 0,
        Log = 1,
        Input = Log << 1,
        Haxe = Input << 1,
        SDLRender = Haxe << 1,
        Physics = SDLRender << 1,
        Scene = Physics << 1,
        Time = Scene << 1,

        All = Log | SDLRender | Physics | Scene | Time | Haxe | Input,
    };

    // Initializes specified engine subsystems
    bool Core_Initialize(const MECoreSystems& systems);
    void Core_Shutdown();
}

#endif //MECORE_H
