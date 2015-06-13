function draw_hat(x_hat)
M = [1 -1  0  0 -2 -2 0 0 -1 1 0 0 3  3  0;
    -2 -2 -2 -1 -1  1 1 2  2 2 2 1 1 -1 -1;
    1  1  1  1  1  1 1 1  1 1 1 1 1  1  1];
%M_hat = [cos(x_hat(3)),-sin(x_hat(3)),x_hat(1);sin(x_hat(3)),cos(x_hat(3)),x_hat(2);0 0 1]*M;
%plot(M_hat(1,:),M_hat(2,:),'r');
drawbox([x_hat(1,:);x_hat(2,:)],'r','r');
end
