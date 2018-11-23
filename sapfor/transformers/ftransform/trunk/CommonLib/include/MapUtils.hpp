//
// Created by baa on 16.12.17.
//

#ifndef FTRANSFORM_MAPUTILS_HPP
#define FTRANSFORM_MAPUTILS_HPP

#include <map>

namespace SageTransform {

    namespace MapUtils {
        template<typename K, typename V>
        V getOrDefault(const std::map<K, V> &inMap, const K &key, const V &defaultValue) {
            //implementation must be visible to compiler 
            auto it = inMap.find(key);
            if (it == inMap.end())
                return defaultValue;
            else
                return it->second;
        };
    }
}
#endif //FTRANSFORM_MAPUTILS_HPP
