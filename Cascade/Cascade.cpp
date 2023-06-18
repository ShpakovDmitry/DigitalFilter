/* -*-c++-*- 
 *
 *    file: Cascade.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Class for Filter cascading implementation.
 *
 */

#include "Cascade"

namespace Filters {

    Cascade::Cascade() {}

    void Cascade::reset() {
        for (auto &filter : m_filters) {
            filter->reset();
        }
    }

    float Cascade::filterSample(float sample) {
        float filteredSample = sample;
        for (auto &filter : m_filters) {
            filteredSample = filter->filterSample(filteredSample);
        }
        return filteredSample;
    }

    std::vector<float> Cascade::filterSamples(const std::vector<float> &samples) {
        std::vector<float> filteredSamples;
        filteredSamples.reserve(samples.size());
        
        for (const auto &sample : samples) {
            float filteredSample = filterSample(sample);
            filteredSamples.push_back(filteredSample);
        }
        return filteredSamples;
    }

    void Cascade::addFilter(std::unique_ptr<Filter> filter) {
        m_filters.push_back(std::move(filter));
    }

}

