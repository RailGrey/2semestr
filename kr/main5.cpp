#include <iostream>
#include <math.h>

uint32_t get_results(uint32_t channel)
{
    static uint32_t calls = 0;
    calls++;
    if (calls > 25) return static_cast<uint32_t>(-1);

    static uint32_t min = 10, max = 255760;
    static uint32_t min_channel = 50, max_channel = 250;
    static uint32_t zero = 100000;

    if (channel <= min_channel)
        return static_cast<uint32_t>(zero - channel*((double)zero - min)/min_channel);
    if (channel <= max_channel)
        return static_cast<uint32_t>(min + ((double)channel - min_channel)*((double)max - min)/((double)max_channel - min_channel));
    if (channel <= 360)
        return static_cast<uint32_t>(max - ((double)channel - max_channel)*((double)max - zero)/((double)360 - max_channel));
    return static_cast<uint32_t>(-1);
}

int get_channel(int cur_channel, int step) {
    if ((cur_channel + step) > 359) {
        return cur_channel + step - 360;
    } else if ((cur_channel + step) < 0) {
        return cur_channel + step + 360;
    } else {
        return cur_channel + step;
    }
}

void detect() {
    float lr = 0.5;
    int step = 1, cur_channel = 180, max_channel, start_step = 30;
    uint32_t max;
    uint32_t attempts[25];
    attempts[0] = get_results(cur_channel);
    cur_channel++;
    attempts[1] = get_results(cur_channel);
    if (attempts[1] > attempts[0]) {
        step = start_step;
        max = attempts[1];
        max_channel = cur_channel;
    } else {
        step = -start_step;
        max = attempts[0];
        max_channel = cur_channel;
    }
    for (int i = 2; i < 25; i++) {
        cur_channel = get_channel(cur_channel, step);
        attempts[i] = get_results(cur_channel);
        if (attempts[i] < attempts[i-1]) {
            if ((step > 1) || (step < -1)) {
                if ((step > 2) || (step < -2)) {
                    step = -roundf(step * lr);
                } else {
                    if (step > 0) {
                        step = -step + 1;
                    } else {
                        step = -step - 1;
                    }
                }
            } else {
                step = -step;
            }
        } else {
            max = attempts[i];
            max_channel = cur_channel;
        }
        std::cout << step << '\n';
    }
    std::cout << max << " " << max_channel;
}

int main() {
    detect();
    return 0;
}

