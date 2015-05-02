% r = i_In([[10,15];[10,15]], [[11,12];[11,12]])
% iboolean : itrue -> [1,1], ifalse -> [0,0], iperhaps -> [0,1].
% Return an iboolean.
function r = i_In(X_p, Y_p)
r = i_defaultibooleanfn2arg(X_p, Y_p, 'Inx');
