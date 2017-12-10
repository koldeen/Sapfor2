//
// Created by baa on 10.12.17.
//

#ifndef FTRANSFORM_LINEREORDERER_HPP
#define FTRANSFORM_LINEREORDERER_HPP

#include "LineReorderRecord.hpp"
#include "../../../../../../dvm/fdvm/trunk/Sage/lib/include/libSage++.h"

namespace SageTransform {
    class LineReorderer {
    public:        
        static void apply(SgStatement *baseStatement, LineReorderRecord * lrr);
    };
}

#endif //FTRANSFORM_LINEREORDERER_HPP
