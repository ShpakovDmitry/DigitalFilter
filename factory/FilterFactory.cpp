/* -*-c++-*- 
 *
 *    file: FilterFactory.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Factory to create instances of various filters implementation.
 *
 */

#include "FilterFactory"

namespace Filters {

    std::unique_ptr<Filter> FilterFactory::createFIRFilter(const std::vector<float> &coefficients) {
        std::unique_ptr<FIRFilter> filter = std::make_unique<FIRFilter>(coefficients);
    
        return filter;
    }

} // namespace Filters

