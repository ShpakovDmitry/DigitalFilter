/* -*-c++-*- 
 *
 *    file: IirFilter.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Usage example of IIR filter.
 *
 */

#include "../filters"
#include <iostream>

using namespace std;
using namespace Filters;

constexpr int SAMPLES_TO_READ_NUM = 100;
extern float getSample();
extern vector<float> getSamples(int num);

int main(int argc, char *argv[]) {
    // define Expotentially Moving Average filter with alpha=0.5;
    vector<float> feedfrontCoefficients = {0.5f};
    vector<float> feedbackCoefficients = {0.5f};

    unique_ptr<Filter> expotentiallyMovingAverageFilter =
                        FilterFactory::createIIRFilter(feedfrontCoefficients, feedbackCoefficients);

    // filter sample by sample
    for (int i = 0; i < SAMPLES_TO_READ_NUM; ++i) {
        float input = getSample();
        float output = expotentiallyMovingAverageFilter->filterSample(input);
        cout << input << " " << output << endl;
    }

    expotentiallyMovingAverageFilter->reset();

    // filter samples 
    vector<float> samples = getSamples(SAMPLES_TO_READ_NUM);
    vector<float> filteredSamples = expotentiallyMovingAverageFilter->filterSamples(samples);
    for (int i = 0; i < samples.size(); ++i) {
        cout << samples[i] << " " << filteredSamples[i] << endl;
    }

    return 0;
}

