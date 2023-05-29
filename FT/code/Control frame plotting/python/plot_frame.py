## Plotting display control frame
#
# *************************************************************************
#
#  @file    plot_frame.py
#  @author  AW    adrian.wojcik@put.poznan.pl
#  @version 2.0
#  @date    02-Jun-2022
#  @brief   Function for plotting display control frame (see: Final task)
#  @remark  Testes for Python 3.10
#           Requires: math, numpy, matplotlib
#
# *************************************************************************

import math
import numpy as np

from plot_display_signals import plot_display_signals

def plot_frame(number, clock_period):
    
    number = round(number)
    
    # Input validation
    if number < 0 or number > 9999:
        raise ValueError("Input argument must be from range <0, 9999>!")
        
    # Sample time validation
    if clock_period < 0:
        raise ValueError("Clock period must be positive!")
        
    # Main logic: number to timeseries
    clock_period = clock_period * 1000 # [ms]
    TS = clock_period / 2
    TIME = np.r_[0, TS * np.arange(0,17)]
    CLOCK = np.r_[0, np.squeeze(np.tile([0,1], [1,math.floor(len(TIME)/2)-1]))]

    DEC_DIGITS_CHAR = "%4u" % number
    DEC_DIGITS = np.zeros(4,dtype=int)
    for i in np.arange(0,4):
        if DEC_DIGITS_CHAR[i] >= '0' and DEC_DIGITS_CHAR[i] <= '9':
            DEC_DIGITS[i] = int(DEC_DIGITS_CHAR[i]) - int('0')
        else:
            DEC_DIGITS[i] = 10

    DEC_DIGIT_2_SEG = [0xC0, 0xF9, 0xA4, 0xB0, 0x99, \
                       0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF] # Common anode
    # TODO: add common cathode 

    DATA1 = np.zeros(np.size(CLOCK))
    DATA2 = np.zeros(np.size(CLOCK))
    DATA3 = np.zeros(np.size(CLOCK))
    DATA4 = np.zeros(np.size(CLOCK))
    k = 1
    for i in np.arange(0,4,dtype=int):
        digit = DEC_DIGIT_2_SEG[DEC_DIGITS[i]]
        for n in np.arange(0,2):
            DATA1[k] = (digit >> 0) & 1
            DATA2[k] = (digit >> 1) & 1
            DATA3[k] = (digit >> 2) & 1
            DATA4[k] = (digit >> 3) & 1
            k = k + 1
        for n in np.arange(0,2):
            DATA1[k] = (digit >> 4) & 1
            DATA2[k] = (digit >> 5) & 1
            DATA3[k] = (digit >> 6) & 1
            DATA4[k] = (digit >> 7) & 1
            k = k + 1    
            
    # Result plotting
    hFig = plot_display_signals(TIME, CLOCK, DATA1, DATA2, DATA3, DATA4, TS,\
               'CONTROL FRAME FOR NUMBER: '+DEC_DIGITS_CHAR);

if __name__ == '__main__':
    plot_frame(1234, 0.5)
