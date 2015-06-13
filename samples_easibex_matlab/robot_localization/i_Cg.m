% Not used for the moment...
function [y_hat,x_hat] = i_Cg(y_hat_p,x_hat_p)

% Contract x_hat.
x_hat(1,:) = i_Inter({x_hat_p(1,:);y_hat_p(1,:)}); 
x_hat(2,:) = i_Inter({x_hat_p(2,:);y_hat_p(2,:)}); 
x_hat(3,:) = i_Inter({x_hat_p(3,:);y_hat_p(3,:)});

% y_hat does not need to be contracted.
y_hat = y_hat_p;
end
