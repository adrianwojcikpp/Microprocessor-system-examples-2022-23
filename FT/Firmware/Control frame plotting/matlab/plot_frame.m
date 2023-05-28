%% Plotting display control frame
%
% *************************************************************************
%
%  @file    plot_frame.m
%  @author  AW    adrian.wojcik@put.poznan.pl
%  @version 2.0
%  @date    01-Jun-2022
%  @brief   Function for plotting display control frame (see: Final task)
%  @remark  Testes for MATLAB R2021b
%
% *************************************************************************
function hFig = plot_frame(number, clock_period)

number = round(number);

% Input validation
if number < 0 || number > 9999 
    error("Input argument must be from range <0, 9999>!")
end

% Sample time validation
if clock_period < 0
    error("Clock period must be positive!")
end

% Main logic: number to timeseries
clock_period = clock_period * 1000; % [ms]
TS = clock_period / 2;
TIME = TS * (0 : 16); 
CLOCK = [repmat([0 1],1, floor(length(TIME)/2)) 0];

DEC_DIGITS_CHAR = sprintf('%4u',number);
DEC_DIGITS = zeros(4,1);
for i = 1 : 4
    if DEC_DIGITS_CHAR(i) >= '0' && DEC_DIGITS_CHAR(i) <= '9'
        DEC_DIGITS(i) = double(DEC_DIGITS_CHAR(i) - '0') + 1;
    else
        DEC_DIGITS(i) = 11;
    end
end

DEC_DIGIT_2_SEG = [0xC0, 0xF9, 0xA4, 0xB0, 0x99, ... % Common anode
                   0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF];
% TODO: add common cathode 

DATA1 = zeros(size(CLOCK));
DATA2 = zeros(size(CLOCK));
DATA3 = zeros(size(CLOCK));
DATA4 = zeros(size(CLOCK));
k = 1;
for i = 1 : 4
    digit = DEC_DIGIT_2_SEG(DEC_DIGITS(i));
    for n  = 1 :2
        DATA1(k) = bitand(bitshift(digit, 0),1);
        DATA2(k) = bitand(bitshift(digit,-1),1);
        DATA3(k) = bitand(bitshift(digit,-2),1);
        DATA4(k) = bitand(bitshift(digit,-3),1);
        k = k + 1;
    end
    for n  = 1 :2
        DATA1(k) = bitand(bitshift(digit,-4),1);
        DATA2(k) = bitand(bitshift(digit,-5),1);
        DATA3(k) = bitand(bitshift(digit,-6),1);
        DATA4(k) = bitand(bitshift(digit,-7),1);
        k = k + 1;
    end
end
   
% Result plotting
hFig = plot_display_signals(TIME, CLOCK, DATA1, DATA2, DATA3, DATA4, TS, ...
               ['CONTROL FRAME FOR NUMBER: ' DEC_DIGITS_CHAR]);