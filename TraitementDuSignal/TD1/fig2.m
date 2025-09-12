% Example: Clock signal analysis in Octave
pkg load signal;
fs = 1e6;                  % sampling frequency [Hz]
t = 0:1/fs:5e-3;           % 5 ms time vector
fclk = 1.25e3;             % clock frequency [Hz]
clock2 = square(2*pi*fclk*t);  % square wave clock
time2 = t;

% ---- Pulse width (high time) ----
% Find rising edges and falling edges
rising = find(diff(clock2) > 0);
falling = find(diff(clock2) < 0);

% Align edges
N = min(length(rising), length(falling));
widths = time2(falling(1:N)) - time2(rising(1:N));
disp("Pulse widths (s):");
disp(widths(1:4));   % show first 4 like your prof

% ---- Duty cycle ----
periods = diff(time2(rising));
duty = widths(1:min(length(widths), length(periods))) ./ periods(1:min(length(widths), length(periods)));
disp("Duty cycle:");
disp(duty(1:3));

% ---- Pulse period ----
pp = periods;
disp("Pulse periods (s):");
disp(pp(1:4));

% ---- Average frequency ----
avgFreq = 1 ./ mean(pp);
disp("Average frequency (Hz):");
disp(avgFreq);

% ---- Total jitter ----
totalJitter = std(pp);
disp("Total jitter (s):");
disp(totalJitter);
