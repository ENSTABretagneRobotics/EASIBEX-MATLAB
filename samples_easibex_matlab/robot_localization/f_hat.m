function x_hatp = f_hat(x_hat,u)

% The inputs are supposed to be known.

cosx3 = i_Cos(x_hat(3,:));
sinx3 = i_Sin(x_hat(3,:));

x4cosx3 = i_Mul(x_hat(4,:),cosx3);
x4sinx3 = i_Mul(x_hat(4,:),sinx3);

% State noise of [-0.001,0.001] to handle model uncertainties, etc.
x_hatp = [i_Add(x4cosx3,[-0.001,0.001]);
    i_Add(x4sinx3,[-0.001,0.001]);
    [u(1)-0.001,u(1)+0.001];
    [u(2)-0.001,u(2)+0.001]];
end
