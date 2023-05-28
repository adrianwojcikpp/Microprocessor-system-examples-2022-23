figure('Name','0x3A with 19200/O/8/1.5');

data = '3A';     % data bits as hexadecimal integer
data_bits = 8;   % { 5, 6, 7, 8, 9 }
stop_bits = 1.5; % { 1, 1.5, 2 }
parity = 'odd';  % 'even'
baud = 19200;    % baud rate in bit/s

plot_uart_frame(data, data_bits, stop_bits, parity, baud);

figure('Name','0x3A with 19200/E/8/1.5');

parity = 'even'; % 'odd'

plot_uart_frame(data, data_bits, stop_bits, parity, baud);
