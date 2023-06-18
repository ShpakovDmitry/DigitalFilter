/* -*-c++-*- 
 *
 *    file: IIRFilter.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Finite Impulse Response digital filter class implementation.
 *
 */

#include "IIRFilter"

namespace Filters {

    IIRFilter::IIRFilter() {}

    IIRFilter::IIRFilter(const std::vector<float> &feedforwardCoefficients,
              const std::vector<float> &feedbackCoefficients) {
        setCoefficients(feedforwardCoefficients, feedbackCoefficients);
    }

    void IIRFilter::reset() {
        for (int i = 0; i < m_inputDelayLine.size(); ++i) {
            m_inputDelayLine[i] = 0.0f;
        }
        for (int i = 0; i < m_outputDelayLine.size(); ++i) {
            m_outputDelayLine[i] = 0.0f;
        }
    }

    void IIRFilter::setCoefficients(const std::vector<float> &feedforwardCoefficients,
                                    const std::vector<float> &feedbackCoefficients) {
        m_inputDelayLine.resize(feedforwardCoefficients.size());
        m_feedforwardCoefficients.resize(feedforwardCoefficients.size());
        m_feedforwardCoefficients = feedforwardCoefficients;
        m_outputDelayLine.resize(feedbackCoefficients.size());
        m_feedbackCoefficients.resize(feedbackCoefficients.size());
        m_feedbackCoefficients = feedbackCoefficients;

    }

    float IIRFilter::filterSample(float sample) {
        float feedforwardSum = 0.0f;
        m_inputDelayLine.pop_back();
        m_inputDelayLine.push_front(sample);
        for (size_t i = 0; i < m_feedforwardCoefficients.size(); ++i) {
            feedforwardSum += m_feedforwardCoefficients[i] * m_inputDelayLine[i];
        }

        float feedbackSum = 0.0f;
        for (size_t i = 0; i < m_feedbackCoefficients.size(); ++i) {
            feedbackSum += m_feedbackCoefficients[i] * m_outputDelayLine[i];
        }

        float filteredOutput = feedforwardSum - feedbackSum;

        m_outputDelayLine.pop_back();
        m_outputDelayLine.push_front(filteredOutput);
        
        return filteredOutput;
    }

    std::vector<float> IIRFilter::filterSamples(const std::vector<float> &samples) {
        std::vector<float> filteredSamples;
        filteredSamples.reserve(samples.size());
        
        for (const auto &sample : samples) {
            float filteredSample = filterSample(sample);
            filteredSamples.push_back(filteredSample);
        }
        return filteredSamples;
    }

}

