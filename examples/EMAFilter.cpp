/* -*-c++-*- 
 *
 *    file: EMAFilter.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Usage example of EMA filter.
 *
 */

#include "../filters"
#include <iostream>

using namespace std;
using namespace Filters;

constexpr float ALPHA = 0.5f;
constexpr int SAMPLES_TO_READ_NUM = 100;
extern float getSample();
extern vector<float> getSamples(int num);

int main(int argc, char *argv[]) {
    unique_ptr<Filter> EMAFilter = FilterFactory::createEMAFilter(ALPHA);

    // filter sample by sample
    for (int i = 0; i < SAMPLES_TO_READ_NUM; ++i) {
        float input = getSample();
        float output = EMAFilter->filterSample(input);
        cout << input << " " << output << endl;
    }

    EMAFilter->reset();

    // filter samples 
    vector<float> samples = getSamples(SAMPLES_TO_READ_NUM);
    vector<float> filteredSamples = EMAFilter->filterSamples(samples);
    for (int i = 0; i < samples.size(); ++i) {
        cout << samples[i] << " " << filteredSamples[i] << endl;
    }

    return 0;
}

