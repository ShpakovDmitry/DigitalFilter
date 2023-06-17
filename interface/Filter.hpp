/* -*-c++-*- 
 *
 *    file: Filter.hpp
 *  author: ShpakovDmitry
 *    date: 2023-6-15
 * licence: CC0
 * summary: Filter interface class. Filter parameters will be set in
 *          derived classes.
 *
 */

#ifndef _FILTER_HPP_
#define _FILTER_HPP_

namespace Filters {

    class Filter {
        public:
            virtual ~Filter() {};

            virtual float filterSample(float sample) = 0;
        private:
    };

} // namespace Filters

#endif//_FILTER_HPP_

