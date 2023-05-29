%% Plotting firmware test result
%
% *************************************************************************
%
%  @file    plot_result.m
%  @author  AW    adrian.wojcik@put.poznan.pl
%  @version 2.0
%  @date    01-Jun-2022
%  @brief   Function for plotting display control frame (see: Final task)
%  @remark  Testes for Octave 7.1.0
%
% *************************************************************************
function hFig = plot_result(filename)

data = dlmread(filename);

TIME  = data(1:end-1,1)';
CLOCK = data(:,2)';
DATA1 = data(:,3)';
DATA2 = data(:,4)';
DATA3 = data(:,5)';
DATA4 = data(:,6)';

TIME  = TIME * 1000; % [ms]
TS = mean(TIME(2:end) - TIME(1:end-1));

hFig = plot_display_signals(TIME, CLOCK, DATA1, DATA2, DATA3, DATA4, TS, ...
               'FIRMWARE TEST RESULT');
