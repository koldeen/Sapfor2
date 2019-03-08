//
// Created by baa on 25.12.17.
//

#ifndef FTRANSFORM_LOOP_WRAP_TRANSFORM_HPP
#define FTRANSFORM_LOOP_WRAP_TRANSFORM_HPP

#include "BaseTransform.hpp"
#include <user.h>

namespace SageTransform {
    class LoopWrapTransform : public BaseTransform {
    public:
        /**
         * Wrap aroung given range of statements, including both ends into new fake loop.
         * Fake loop has one iteration with given index variable of its own value.
         * @param symbol symbol to use as index for new loop
         * @param start first statement to include to fake loop, inclusive
         * @param end last statement to include to fake loop, inclusive
         *   `end` must be same as start or lexically after `start`.
         * @return reference to SgStatement with new fake loop
         */
        SgForStmt *wrapWithOneIteration(SgSymbol *symbol, SgStatement *start, SgStatement *end);

        /**
         * Short cut to wrap a given loop into one more nested layer.
         * @see LoopWrapTransform::wrapWithOneIteration(SgSymbol *, SgStatement *, SgStatement *)
         */
        SgForStmt *wrapWithOneIteration(SgSymbol *symbol, SgForStmt *loop);
    private:
    };
}
#endif //FTRANSFORM_LOOP_WRAP_TRANSFORM_HPP
