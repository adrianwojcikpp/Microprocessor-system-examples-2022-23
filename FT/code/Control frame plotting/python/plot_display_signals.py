## Plotting display control frame
#
# *************************************************************************
#
#  @file    plot_display_signals.py
#  @author  AW    adrian.wojcik@put.poznan.pl
#  @version 2.0
#  @date    02-Jun-2022
#  @brief   Common sinal plotting function (see: Final task)
#  @remark  Testes for Python 3.10
#           Requires: numpy, matplotlib
#
# *************************************************************************

import numpy as np
import matplotlib.pyplot as plt

def plot_display_signals(TIME, CLOCK, DATA1, DATA2, DATA3, DATA4, TS, TITLE):

    #plt.rcParams.update({'font.size': 7})
    hFig, hAxs = plt.subplots(5, 1)
    hFig.canvas.manager.set_window_title(TITLE)
    plt.subplots_adjust(hspace=0.5)

    hAxs[0].set_title(TITLE,fontweight='bold')
    hAxs[0].stairs(CLOCK, TIME, linewidth=2, color='#000000')
    hAxs[0].grid(True)
    hAxs[0].set_ylabel('Logic state')
    hAxs[0].set_xlim([TIME[1],TIME[-1]])
    hAxs[0].set_ylim([-0.1,1.1])  
    hAxs[0].legend(['CLOCK'])

    hAxs[1].stairs(DATA1, TIME, linewidth=2, color='#FF0000')
    hAxs[1].grid(True)
    hAxs[1].set_ylabel('Logic state')
    hAxs[1].set_xlim([TIME[1],TIME[-1]])
    hAxs[1].set_ylim([-0.1,1.1])  
    hAxs[1].legend(['DATA1'])
    for i in np.arange(1,8,2,dtype=int):
        hAxs[1].text(TIME[2*i-1] + TS/3, 0.4, 'A'+str(int((i+1)/2)));
        hAxs[1].text(TIME[2*i+1] + TS/3, 0.4, 'E'+str(int((i+1)/2)));

    hAxs[2].stairs(DATA2, TIME, linewidth=2, color='#77AC30')
    hAxs[2].grid(True)
    hAxs[2].set_ylabel('Logic state')
    hAxs[2].set_xlim([TIME[1],TIME[-1]])
    hAxs[2].set_ylim([-0.1,1.1])  
    hAxs[2].legend(['DATA2'])
    for i in np.arange(1,8,2,dtype=int):
        hAxs[2].text(TIME[2*i-1] + TS/3, 0.4, 'B'+str(int((i+1)/2)));
        hAxs[2].text(TIME[2*i+1] + TS/3, 0.4, 'F'+str(int((i+1)/2)));

    hAxs[3].stairs(DATA3, TIME, linewidth=2, color='#0072BD')
    hAxs[3].grid(True)
    hAxs[3].set_ylabel('Logic state')
    hAxs[3].set_xlim([TIME[1],TIME[-1]])
    hAxs[3].set_ylim([-0.1,1.1])  
    hAxs[3].legend(['DATA3'])
    for i in np.arange(1,8,2,dtype=int):
        hAxs[3].text(TIME[2*i-1] + TS/3, 0.4, 'C'+str(int((i+1)/2)));
        hAxs[3].text(TIME[2*i+1] + TS/3, 0.4, 'G'+str(int((i+1)/2)));

    hAxs[4].stairs(DATA4, TIME, linewidth=2, color='#EDB120')
    hAxs[4].grid(True)
    hAxs[4].set_ylabel('Logic state')
    hAxs[4].set_xlabel('Time [ms]')
    hAxs[4].set_xlim([TIME[1],TIME[-1]])
    hAxs[4].set_ylim([-0.1,1.1])  
    hAxs[4].legend(['DATA4'])
    for i in np.arange(1,8,2,dtype=int):
        hAxs[4].text(TIME[2*i-1] + TS/3, 0.4, 'D'+str(int((i+1)/2)));
        hAxs[4].text(TIME[2*i+1] + TS/3, 0.4, 'H'+str(int((i+1)/2)));
    
    plt.show()
