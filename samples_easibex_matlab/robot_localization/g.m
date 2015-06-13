function y = g(x)

% Heading is measured (with random error and bias) with a compass at all times, and sometimes position with GPS (when outside).
y = [x(1)-0.3+0.2*(rand()-0.5);x(2)+0.2+0.3*(rand()-0.5);x(3)+0.01+0.02*(rand()-0.5)];
end
