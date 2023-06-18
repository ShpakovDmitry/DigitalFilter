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

std::unique_ptr<Filters::Filter> createFIRFilter(const std::vector<float> &coefficients) {
    std::unique_ptr<Filters::FIRFilter> filter = std::make_unique<Filters::FIRFilter>(coefficients);

    return filter;
}

