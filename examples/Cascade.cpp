/* -*-c++-*- 
 *
 *    file: Cascade.cpp
 *  author: ShpakovDmitry
 *    date: 2023-6-18
 * licence: CC0
 * summary: Usage example of Cascading filters.
 *
 */

#include "../filters"
#include <iostream>

using namespace std;
using namespace Filters;

extern float getSample();
extern vector<float> getSamples(int num);

constexpr float ALPHA = 0.5f;
constexpr unsigned SMA_SAMPLES_TO_FILTER = 10;
constexpr int SAMPLES_TO_READ_NUM = 100;


int main(int argc, char *argv[]) {
    unique_ptr<Filter> EMAFilter = FilterFactory::createEMAFilter(ALPHA);
    unique_ptr<Filter> SMAFilter = FilterFactory::createSMAFilter(SMA_SAMPLES_TO_FILTER);

    Cascade cascade;
    cascade.addFilter(std::move(EMAFilter));
    cascade.addFilter(std::move(SMAFilter));

    // filter sample by sample
    for (int i = 0; i < SAMPLES_TO_READ_NUM; ++i) {
        float input = getSample();
        float output = cascade.filterSample(input);
        cout << input << " " << output << endl;
    }

    cascade.reset();

    // filter samples 
    vector<float> samples = getSamples(SAMPLES_TO_READ_NUM);
    vector<float> filteredSamples = cascade.filterSamples(samples);
    for (int i = 0; i < samples.size(); ++i) {
        cout << samples[i] << " " << filteredSamples[i] << endl;
    }


    return 0;
}
