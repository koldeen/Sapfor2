//
// Created by baa on 28.08.17.
//

#ifndef FTRANSFORM_SIGNALHANDLING_HPP
#define FTRANSFORM_SIGNALHANDLING_HPP

namespace SageTransform {
    class SignalHandling {
    public:
        SignalHandling();

    private:
        static void abortHandler(int signum);
    };
}


#endif //FTRANSFORM_SIGNALHANDLING_HPP
