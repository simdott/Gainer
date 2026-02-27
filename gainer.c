/*
 * Gainer LV2 Plugin - Simple stereo gain plugin
 * Copyright (C) 2025 Your Name
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * (rest of license boilerplate...)
 */

#include <lv2/core/lv2.h>
#include <math.h>
#include <stdlib.h>

#define GAINER_URI "urn:simdott:gainer"

typedef enum {
    INPUT_LEFT = 0,
    INPUT_RIGHT = 1,
    OUTPUT_LEFT = 2,
    OUTPUT_RIGHT = 3,
    VOLUME = 4
} PortIndex;

typedef struct {
    const float* input_left;
    const float* input_right;
    const float* volume;
    float* output_left;
    float* output_right;
    float prev_volume;
} Gainer;

static LV2_Handle instantiate(
    const LV2_Descriptor* descriptor,
    double sample_rate,
    const char* bundle_path,
    const LV2_Feature* const* features) {
    
    Gainer* self = (Gainer*)malloc(sizeof(Gainer));
    if (!self) return NULL;
    
    self->prev_volume = 1.0f;
    
    return (LV2_Handle)self;
}

static void connect_port(LV2_Handle instance, uint32_t port, void* data) {
    Gainer* self = (Gainer*)instance;
    
    switch ((PortIndex)port) {
        case INPUT_LEFT: 
            self->input_left = (const float*)data; 
            break;
        case INPUT_RIGHT: 
            self->input_right = (const float*)data; 
            break;
        case OUTPUT_LEFT: 
            self->output_left = (float*)data; 
            break;
        case OUTPUT_RIGHT: 
            self->output_right = (float*)data; 
            break;
        case VOLUME:
            self->volume = (const float*)data;
            break;
    }
}

static void run(LV2_Handle instance, uint32_t n_samples) {
    Gainer* self = (Gainer*)instance;
    
    float current_volume = *(self->volume);
    float volume_gain = current_volume / 100.0f;
    
    if (fabsf(volume_gain - self->prev_volume) < 0.0001f && fabsf(volume_gain - 1.0f) < 0.0001f) {
        for (uint32_t i = 0; i < n_samples; i++) {
            self->output_left[i] = self->input_left[i];
            self->output_right[i] = self->input_right[i];
        }
        return;
    }
    
    self->prev_volume = volume_gain;
    
    for (uint32_t i = 0; i < n_samples; i++) {
        self->output_left[i] = self->input_left[i] * volume_gain;
        self->output_right[i] = self->input_right[i] * volume_gain;
    }
}

static void cleanup(LV2_Handle instance) {
    free(instance);
}

static const LV2_Descriptor descriptor = {
    GAINER_URI,
    instantiate,
    connect_port,
    NULL,
    run,
    NULL,
    cleanup,
    NULL
};

LV2_SYMBOL_EXPORT
const LV2_Descriptor* lv2_descriptor(uint32_t index) {
    return (index == 0) ? &descriptor : NULL;
}
