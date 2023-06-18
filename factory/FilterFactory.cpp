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

    //FIR filters
    std::unique_ptr<Filter> FilterFactory::createFIRFilter(const std::vector<float> &coefficients) {
        std::unique_ptr<FIRFilter> filter = std::make_unique<FIRFilter>(coefficients);
    
        return filter;
    }
    
    std::unique_ptr<Filter> FilterFactory::createSimpleMovingAverageFilter(unsigned numSamples) {
        if (numSamples == 0) {
            numSamples = 1;
        }
        float coefficient = 1.0f/static_cast<float>(numSamples);
        std::vector<float> SMACoefficients(numSamples, coefficient);
        std::unique_ptr<FIRFilter> filter = std::make_unique<FIRFilter>(SMACoefficients);
        return filter;
    }

    //IIR filters
    std::unique_ptr<Filter> FilterFactory::createIIRFilter(const std::vector<float> &feedfrontCoefficients,
                                                           const std::vector<float> &feedbackCoefficients) {
        std::unique_ptr<IIRFilter> filter = std::make_unique<IIRFilter>(feedfrontCoefficients, feedbackCoefficients);
    
        return filter;
    }

    std::unique_ptr<Filter> FilterFactory::createEMAFilter(float alpha) {
        if (alpha < 0.0f) {
            alpha = 0.0f;
        }
        if (alpha > 1.0f) {
            alpha = 1.0f;
        }
        std::vector<float> feedfrontCoefficients = {alpha};
        std::vector<float> feedbackCoefficients = {alpha - 1.0f};

        std::unique_ptr<IIRFilter> filter = std::make_unique<IIRFilter>(feedfrontCoefficients, feedbackCoefficients);
    
        return filter;
    }

} // namespace Filters

