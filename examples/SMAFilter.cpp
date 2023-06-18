/* -*-c++-*- 
 *
 *    file: SMAFilter.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Usage example of Simple Moving Average filter.
 *
 */

#include "../filters"
#include <iostream>

using namespace std;
using namespace Filters;

constexpr unsigned SAMPLES_TO_FILTER = 10;
constexpr int SAMPLES_TO_READ_NUM = 100;
extern float getSample();
extern vector<float> getSamples(int num);

int main(int argc, char *argv[]) {
    
    unique_ptr<Filter> SMAFilter = FilterFactory::createSMAFilter(SAMPLES_TO_FILTER);

    // filter sample by sample
    for (int i = 0; i < SAMPLES_TO_READ_NUM; ++i) {
        float input = getSample();
        float output = SMAFilter->filterSample(input);
        cout << input << " " << output << endl;
    }

    SMAFilter->reset();

    // filter samples 
    vector<float> samples = getSamples(SAMPLES_TO_READ_NUM);
    vector<float> filteredSamples = SMAFilter->filterSamples(samples);
    for (int i = 0; i < samples.size(); ++i) {
        cout << samples[i] << " " << filteredSamples[i] << endl;
    }

    return 0;
}
