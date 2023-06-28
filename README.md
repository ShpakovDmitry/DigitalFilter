WIP.
### TOC

### About
This repository hold various digital filters implementation. The
architecture is designed in such way that it is easy to extend library when
new kind of digital filter is added. Also, it is easy to use every filter,
because all filters have the same usage interface. Filters may be cascaded
to achieve desired goals.

### Installation
Simply copy DigitalFilter directory into project directory and add library to
your source file:
```cpp
// ...
#include "DigitalFilter/filters"
// ...
```

### Usage
There are two ways to filter the data available:
* filter one sample at a time
* filter number of samples at a time

To filter one sample at a time use the
```cpp
float filterSample(float sample);
```
method. This method takes input `sample` and returns filtered sample.

But to filter number of samples at a time use the
```cpp
std::vector<float> filterSamples(const std::vector<float> &samples);
```
method. This method takes the vctor of input samples and return vector of
filtered samples.

To reset the filter call
```cpp
void reset();
```
method. This method just resets the internal delay line, sets it's values to 
0.0f`.

Every filter instance is created using `FilterFactory`, which takes all
neccessary filter initialisation parameters. For example, **S**imple **M**oving
**A**verage or **SMA** filter on 20 samples to be filtered is created using the
following `FilterFactory` static method:
```cpp
constexpr unsigned SAMPLES_TO_FILTER = 20;
unique_ptr<Filter> smaFilter = FilterFactory::createSMAFilter(SAMPLES_TO_FILTER);
```

Combining all of this, the usage example in case of `FIR` filter, is shown
below:
```cpp
// your source code file
#include "DigitalFilter/filters"

usign namespace Filters;

extern unsigned SAMPLES_TO_READ_NUM;
extern float getSample(); // this function returns new sample and should be
                          // defined by you

int main(int argc, char *argv[]) {
    vector<float> coefficients = {0.2f, 0.2f, 0.2f, 0.2f, 0.2f};

    unique_ptr<Filter> filter = FilterFactory::createFIRFilter(coefficients);

    for (int i = 0; i < SAMPLES_TO_READ_NUM; ++i) {
        float input = getSample();
        float output = filter->filterSample(input);
        // use filtered output sample
    }

    return 0;
}
```

To filter number of sample at a time use the fiollowing example as a reference:
```cpp
// your source code file
#include "DigitalFilter/filters"

usign namespace Filters;

extern vector<float> getSamples(unsigned);
extern unsigned SAMPLES_TO_READ_NUM;

int main(int argc, char *argv[]) {
    vector<float> coefficients = {0.2f, 0.2f, 0.2f, 0.2f, 0.2f};

    unique_ptr<Filter> filter = FilterFactory::createFIRFilter(coefficients);

    vector<float> inputSamples = getSamples(SAMPLES_TO_READ_NUM);
    vector<float> outputSamples = filter->filterSamples(inputSamples);
    // use filtered samples

    return 0;
}
```

More usage examples could be found in `examples` directory.

### Cascading filters
    To cascade the filters one after the other use the following code:
```cpp
#include "DigitalFilter/filters"

using namespace Filters;

extern float getSample();
extern vector<float> getSamples(unsigned);

constexpr float ALPHA = 0.5f;
constexpr unsigned SMA_SAMPLES_TO_FILTER = 10;
constexpr int SAMPLES_TO_READ_NUM = 100;


int main(int argc, char *argv[]) {
    unique_ptr<Filter> EMAFilter = FilterFactory::createEMAFilter(ALPHA);
    unique_ptr<Filter> SMAFilter = FilterFactory::createSMAFilter(SMA_SAMPLES_TO_FILTER);

    Cascade cascade;
    // filter sample through EMA filter and then through SMA filter
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
```
You can cascade as many filter as you want, just dont forget create filter
instance and add it to `Cascade` by calling `addFilter()` method.

### Available filters
Currently filters available (list will be updated when new filter will be added):
* FIR filter
* IIR filter
* Simple Moving Average (SMA) filter
* Exponentially Moving Average (EMA) filter

### How to add new filter
All filters rely on the same interface defined in abstract class located in
`interface/Filter` file. To create new filter class you should inherit base
`Filter` class. As example, there are already implemented two types of filters
**I**nfinite **I**mpulse **R**esponse or **IIR** and **F**inite **I**mpulse
**R**esponse or **FIR** filters. Those kind of filters cover huge amount of
filter use cases. After the new king of filter is inherited from base class you
should add new `static` method to `FilterFactory` class, which actually creates
the instance of a filter. Example how it is done could be found in `factory`
directory. and finally include new filter header file into `filters` file.

### Dependencies

The library is dependant on the following libraries: `vector`, `deque`,
`memory`.

### License

The library is provided under CC0 terms, meaning that `No Rights are reserved`
and do whatever you want with this library.

