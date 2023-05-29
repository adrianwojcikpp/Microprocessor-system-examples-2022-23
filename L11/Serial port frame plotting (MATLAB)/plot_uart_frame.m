function plot_uart_frame(data, data_size, stop, parity, baud)
%
% PLOT_UART_FRAME funckja rysuje przebieg ramki UART
%   
%   PLOT_UART_FRAME(data, data_size, stop, parity, baud)
%   data - string z danymi w postaci heksadecymalnej
%   data_size - liczba bitów danych (5-9)
%   stop - liczba bitów stopu (1-1.5-2)
%   parity - typ bitu parzystoœci ("none"-"even"-"odd")
%   baud - predkoœc transmisji (bit/s)
%

clf;

H = 3.3;
L = 0;

%% SPRAWDZENIE WARUNKÓW
if (data_size > 9) || (data_size < 5)
    error('Nieprawid³owy rozmiar danych');
end

if ~(strcmp(parity, 'even') || strcmp(parity, 'odd') ...
        || strcmp(parity, 'none'))
    error('Nieprawid³owa parzystoœæ');
end

if ~((stop == 1) || (stop == 1.5) || (stop == 2))
    error('Nieprawid³owy liczba bitów stopu');
end

%% OBLICZENIA BITÓW RAMKI
start = 0;

bits = hexToBinaryVector(data,16);
bits = double(bits);
bits = fliplr(bits);
data_bits = bits(1 : data_size);

p = [];

if strcmp(parity, 'even')
    p = sum(bits);
    p = mod(p,2);
elseif strcmp(parity, 'odd')
    p = sum(bits);
    p = mod(p+1,2);  
end

stop = ones(1, stop*2);
idle = H;
%% RYSOWNAIE RAMKI

FRAME = [];
FRAME = [FRAME start start]; % start

for i = 1 : length(data_bits)
    FRAME = [FRAME data_bits(i) data_bits(i)]; % data
end

FRAME = [FRAME p p]; % parity

FRAME = [FRAME stop];

%FRAME = H*2*(FRAME - 0.5);
FRAME = H*FRAME;

TIME = (-1 : length(FRAME)+1)*(0.5/baud);
TIME = 1000*TIME;

marg = 0.5;
dt = 0.01;
text(TIME(2)+dt, abs(FRAME(1))+0.5*marg, 'START');

for i = 1 : data_size
   text(TIME(2+2*i)+dt, abs(FRAME(1+2*i))+0.5*marg, ['D' num2str(i-1)]); 
end
i=i+1;
text(TIME(2+2*i)+dt, abs(FRAME(1+2*i))+0.5*marg, 'PARITY'); 
i=i+1;
text(TIME(2+2*i)+dt, abs(FRAME(1+2*i))+0.5*marg, 'STOP'); 
hold on;

plot([0 0], [L-marg H+marg], 'r--', 'LineWidth', 4) % START FRAME
plot([TIME(end-1) TIME(end-1)], [L-marg H+marg], 'r--', 'LineWidth', 4) % STOP FRAME
plot([TIME(4) TIME(4)], [L-marg H+marg], 'g--', 'LineWidth', 2) % START Bit
plot([TIME(4+2*data_size) TIME(4+2*data_size)], [L-marg H+marg], 'g--', 'LineWidth', 2) % DATA Bits
if ~isempty(p)
    plot([TIME(4+2*data_size+2) TIME(4+2*data_size+2)], [L-marg H+marg], 'g--', 'LineWidth', 2) % PARITY Bits
end
stairs(TIME,[idle FRAME idle idle], 'LineWidth', 3); grid on;

xlabel('TIME [ms]');
ylabel('VOLTAGE [V]');

hold off;
set(gca,'XTick',(-5 : 30)*(1000/baud));
set(gca,'YTick',([L H]));
axis([TIME(1) TIME(end) L-marg H+marg]);
