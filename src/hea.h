#pragma once
#include <stddef.h>

#ifndef HEA_MAX_CH
#define HEA_MAX_CH 64
#endif

#ifndef HEA_MAX_TIMESTR
#define HEA_MAX_TIMESTR 16
#endif

#ifndef HEA_MAX_DATESTR
#define HEA_MAX_DATESTR 16
#endif

/* 
Struct for processing channel data from .hea file. 
Ex: s0010_re.dat 16 2000 16 0 -489 -8337 0 i
This allows the derivation of the ECG wave from the .dat files
More info: https://physionet.org/physiotools/wag/header-5.htm
*/
typedef struct {
    // file name
    char datafile[256];
    // storage format code
    int fmt;
    // samples per frame (x modifier)
    int samples_per_frame;
    // skew (colon modifier)
    int skew;
    // byte offset to sample 0 (plus modifier)
    long byte_offset;
    // ADC gain (ADC units per physical unit)
    double adc_gain;
    // baseline (ADC units)
    int baseline;
    // physical units string
    char units[32];
    // ADC resolution in bits
    int adc_res;
    // ADC zero code
    int adc_zero;
    // initial value (for difference formats)
    long init_value;
    // checksum (16-bit signed, stored as long)
    long checksum;
    // block size in bytes
    int block_size;
    // trailing description text
    char description[256];
    // short human-readable label
    char label[64];
    // internal: group index for files shared across signals
    int file_group;
} HeaSignalSpec;

/* 
Struct for processing record data from .hea file. 
Ex: s0010_re 15 1000 38400
More info: https://physionet.org/physiotools/wag/header-5.htm
*/
typedef struct {
    // Record name 
    char  record_name[256];
    // Number of segments
    int num_segments;
    // Number of HEA signals 
    int   num_signals;
    // Sampling frequency in Hz
    double fs;
    // Counter frequency in ticks / sec
    double counter_freq;
    // Specifies the counter value corresponding to sample 0
    double base_counter_value;
    // Total number of samples per signal
    size_t num_samples_per_signal;
    // Time of day that corresponds to the beginning of the record using 24 hour clock
    char base_time[HEA_MAX_TIMESTR];
    // Calendar date that corresponds to the beginning of the record
    char base_date[HEA_MAX_DATESTR];
    // Actual file names per channel group
    // TODO: Remove this!
    int   nfiles; /* number of distinct data files referenced */
    char  file_group_names[HEA_MAX_CH][256];
    // Per-signal specs in header order
    HeaSignalSpec signal_specs[HEA_MAX_CH];
} HeaRecord;

// Parse a WFDB-style header (.hea). Returns 0 on success
int hea_parse_and_validate(const char *hea_path, HeaRecord *rec);

// Utility: find group index by filename, adds if new and returns index
int hea_group_index(HeaRecord *rec, const char *fname);
