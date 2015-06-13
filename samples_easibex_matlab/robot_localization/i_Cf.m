% Not used for the moment...
function [x_hatp,x_hat,u_hat] = i_Cf(x_hatp_p,x_hat_p,u_hat_p)

% Contract f forward and backward.

x_hatp = x_hatp_p;
x_hat = x_hat_p;
u_hat = u_hat_p;

cosx3=[-Inf,Inf];
sinx3=[-Inf,Inf];
x4cosx3=[-Inf,Inf];
x4sinx3=[-Inf,Inf];

[cosx3,x_hat] = i_Cos(cosx3,x_hat);
[sinx3,x_hat] = i_Sin(sinx3,x_hat);
[x4cosx3,x_hat(4,:),cosx3] = i_Cmul(x4cosx3,x_hat(4,:),cosx3);
[x4sinx3,x_hat(4,:),cosx3] = i_Cmul(x4sinx3,x_hat(4,:),sinx3);

% State noise of [-0.001,0.001] to handle model uncertainties, etc.
[x_hatp(1,:),x4cosx3,tmp] = i_Cadd(x_hatp(1,:),x4cosx3,[-0.001,0.001]);
[x_hatp(2,:),x4sinx3,tmp] = i_Cadd(x_hatp(2,:),x4sinx3,[-0.001,0.001]);
[x_hatp(3,:),u_hat(1,:),tmp] = i_Cadd(x_hatp(3,:),u_hat(1,:),[-0.001,0.001]);
[x_hatp(4,:),u_hat(2,:),tmp] = i_Cadd(x_hatp(4,:),u_hat(2,:),[-0.001,0.001]);

[x4cosx3,x_hatp(1,:),tmp] = i_Csub(x4cosx3,x_hatp(1,:),[-0.001,0.001]);
[x4sinx3,x_hatp(2,:),tmp] = i_Csub(x4sinx3,x_hatp(2,:),[-0.001,0.001]);

[x4cosx3,x_hat(4,:),cosx3] = i_Cmul(x4cosx3,x_hat(4,:),cosx3);
[x4sinx3,x_hat(4,:),cosx3] = i_Cmul(x4sinx3,x_hat(4,:),sinx3);

[cosx3,x_hat] = i_Cos(cosx3,x_hat);
[sinx3,x_hat] = i_Sin(sinx3,x_hat);
end
