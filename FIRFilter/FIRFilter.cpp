/* -*-c++-*- 
 *
 *    file: FIRFilter.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Finite Impulse Response digital filter class implementation.
 *
 */

#include "FIRFilter"

namespace Filters {

    FIRFilter::FIRFilter() {}

    FIRFilter::FIRFilter(const std::vector<float> &coefficients) {
        setCoefficients(coefficients);
    }

    void FIRFilter::reset() {
        for (int i = 0; i < m_delayLine.size(); i++) {
            m_delayLine[i] = 0.0f;
        }
    }

    void FIRFilter::setCoefficients(const std::vector<float> &coefficients) {
        m_delayLine.resize(coefficients.size());
        m_coefficients.resize(coefficients.size());
        m_coefficients = coefficients;
    }

    float FIRFilter::filterSample(float sample) {
        float sum = 0.0f;
        m_delayLine.pop_back();
        m_delayLine.push_front(sample);
        for (size_t i = 0; i < m_coefficients.size(); ++i) {
            if (i < m_delayLine.size()) {
                sum += m_coefficients[i] * m_delayLine[i];
            }
        }
        return sum;
    }

    std::vector<float> FIRFilter::filterSamples(const std::vector<float> &samples) {
        std::vector<float> filteredSamples;
        filteredSamples.reserve(samples.size());
        
        for (const auto &sample : samples) {
            float filteredSample = filterSample(sample);
            filteredSamples.push_back(filteredSample);
        }
        return filteredSamples;
    }

}
