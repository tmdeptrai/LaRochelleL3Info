pkg load signal;
fs = 100E9;
% sample freq
D = [2.5 10 17.5]' * 1e-9;
% pulse delay times
t = 0 : 1/fs : 2500/fs;
% signal evaluation time
w = 1e-9;
% width of each pulse
yp = pulstran(t,D,@rectpuls,w);