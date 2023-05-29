## Plotting firmware test result
#
# *************************************************************************
#
#  @file    plot_result.py
#  @author  AW    adrian.wojcik@put.poznan.pl
#  @version 2.0
#  @date    02-Jun-2022
#  @brief   Function for plotting firmware test result (see: Final task)
#  @remark  Testes for Python 3.10
#           Requires: csv, numpy, matplotlib
#
# *************************************************************************

import csv
import numpy as np

from plot_display_signals import plot_display_signals
    
def plot_result(filename):

    # Open file
    logfile = open(filename) 
    data = csv.reader(logfile)
    n = sum(1 for r in data) - 1
    logfile.seek(0)

    TIME = np.zeros(n+1)
    CLOCK = np.zeros(n)
    DATA1 = np.zeros(n)
    DATA2 = np.zeros(n)
    DATA3 = np.zeros(n)
    DATA4 = np.zeros(n)

    k = 1;
    for samples in data:
        try:
            TIME[k+1] = float(samples[0])
            CLOCK[k] = float(samples[1])
            DATA1[k] = float(samples[2])
            DATA2[k] = float(samples[3])
            DATA3[k] = float(samples[4])
            DATA4[k] = float(samples[5])
            k = k + 1
        except:
            pass

    logfile.close() 
    
    TIME = TIME * 1000 # [ms]
    TS = np.mean(TIME[2:]-TIME[1:-1])

    # Result plotting
    hFig = plot_display_signals(TIME, CLOCK, DATA1, DATA2, DATA3, DATA4, TS,\
               'FIRMWARE TEST RESULT');
            
if __name__ == '__main__':
    plot_result('../../Firmware template/result.csv')
