%% Plotting display control signals
%
% *************************************************************************
%
%  @file    plot_display_signals.m
%  @author  AW    adrian.wojcik@put.poznan.pl
%  @version 2.0
%  @date    01-Jun-2022
%  @brief   Common sinal plotting function (see: Final task)
%  @remark  Testes for Octave 7.1.0
%
% *************************************************************************
function hFig = plot_display_signals(TIME, CLOCK, DATA1, DATA2, DATA3, DATA4, TS, TITLE)

% Result plotting
hFig = figure('Name', TITLE);

LW = 2; % [pt]

subplot(5, 1, 1)
    stairs(TIME, CLOCK, 'Color', '#000000', 'LineWidth', LW)
    hold on
    grid on
    ylabel('Logic state')
    title(TITLE)
    axis([TIME(1) TIME(end) -0.1 1.1])
    legend('CLOCK')
subplot(5, 1, 2)
    stairs(TIME, DATA1, 'Color', '#FF0000', 'LineWidth', LW)
    hold on
    grid on
    ylabel('Logic state')
    axis([TIME(1) TIME(end) -0.1 1.1])
    legend('DATA1')
    for i = 1 : 2 : 7
        text(TIME(2*i-1) + TS/3, 0.5, ['A' num2str((i+1)/2)]);
        text(TIME(2*i+1) + TS/3, 0.5, ['E' num2str((i+1)/2)]);
    end
subplot(5, 1, 3)
    stairs(TIME, DATA2, 'Color', '#77AC30', 'LineWidth', LW)
    hold on
    grid on
    ylabel('Logic state')
    axis([TIME(1) TIME(end) -0.1 1.1])
    legend('DATA2')
    for i = 1 : 2 : 7
        text(TIME(2*i-1) + TS/3, 0.5, ['B' num2str((i+1)/2)]);
        text(TIME(2*i+1) + TS/3, 0.5, ['F' num2str((i+1)/2)]);
    end
subplot(5, 1, 4)
    stairs(TIME, DATA3, 'Color', '#0072BD', 'LineWidth', LW)
    hold on
    grid on
    ylabel('Logic state')
    axis([TIME(1) TIME(end) -0.1 1.1])
    legend('DATA3')
    for i = 1 : 2 : 7
        text(TIME(2*i-1) + TS/3, 0.5, ['C' num2str((i+1)/2)]);
        text(TIME(2*i+1) + TS/3, 0.5, ['G' num2str((i+1)/2)]);
    end
subplot(5, 1, 5)
    stairs(TIME, DATA4, 'Color', '#EDB120', 'LineWidth', LW)
    hold on
    grid on
    ylabel('Logic state')
    xlabel('Time [ms]')
    axis([TIME(1) TIME(end) -0.1 1.1])
    legend('DATA4')
    for i = 1 : 2 : 7
        text(TIME(2*i-1) + TS/3, 0.5, ['D' num2str((i+1)/2)]);
        text(TIME(2*i+1) + TS/3, 0.5, ['H' num2str((i+1)/2)]);
    end
