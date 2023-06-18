/* -*-c++-*- 
 *
 *    file: FirFilter.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Usage example of FIR filter.
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
    // define 5 sample moving average filter coefficients
    vector<float> movingAverageCoefficients = {0.2f, 0.2f, 0.2f, 0.2f, 0.2f};
    
    unique_ptr<Filter> movingAverageFilter = FilterFactory::createFIRFilter(movingAverageCoefficients);

    // filter sample by sample
    for (int i = 0; i < SAMPLES_TO_READ_NUM; ++i) {
        float input = getSample();
        float output = movingAverageFilter->filterSample(input);
        cout << input << " " << output << endl;
    }

    movingAverageFilter->reset();

    // filter samples 
    vector<float> samples = getSamples(SAMPLES_TO_READ_NUM);
    vector<float> filteredSamples =  movingAverageFilter->filterSamples(samples);
    for (int i = 0; i < samples.size(); ++i) {
        cout << samples[i] << " " << filteredSamples[i] << endl;
    }

    return 0;
}
