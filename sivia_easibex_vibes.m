%%% To use this example, the ../src/+vibes package must be in your MATLAB PATH variable
%%% Do not forget to launch VIBes-viewer.exe!
function sivia_easibex()
%------------------------------------------------------------------------
function b=inside(X) 
  X1=X(1,:); X2=X(2,:); 
  Y=i_Add(i_Sqr(X1),i_Sqr(X2));
  b=i_In(Y,[1,2]);
end
%------------------------------------------------------------------------
function r=Cout(X) 
  X1=X(1,:); X2=X(2,:); c=[2,2];
  %[X2,X1,c]=i_Csub(X2,X1,c);
  %[X2,X1]=i_Ctan(X2,X1);
  %[X1,X2]=i_CinRing(X1,X2,1,2,[1,1.5]);
  %r=[X1;X2];
  [X1,X2]=i_SinRing(X1,X2,1,2,[1,1.5],1);
  r=[X1;X2];
end
%------------------------------------------------------------------------
function r=Cin(X) 
  X1=X(1,:); X2=X(2,:);
  %[Xa1,Xa2]=i_CinRing(X1,X2,1,2,[-1,1]);
  %[Xb1,Xb2]=i_CinRing(X1,X2,1,2,[1.5,Inf]);
  %r=i_Union({[Xa1;Xa2];[Xb1;Xb2]});
  [X1,X2]=i_SinRing(X1,X2,1,2,[1,1.5],0);
  r=[X1;X2];
end
%------------------------------------------------------------------------
function sivia(X)
     X0=X;
     vibes.drawBox(X,'blue','black');
     X=Cout(X);
     vibes.drawBox(X,'red','magenta');
     X=Cin(X);
     %b=inside(X);
     %if b==[1 1], vibes.drawBox(X,'red','magenta');
     %elseif b==[0 0], vibes.drawBox(X,'blue','black');
     %elseif (i_Width(X)<0.1), vibes.drawBox(X,'yellow','yellow');
     if (i_Width(X)<0.25), vibes.drawBox(X,'yellow','yellow');
     %if (i_decrease(X,X0)<0.1), vibes.drawBox(X,'yellow','yellow');
     else
         [X1,X2]=i_Bisect(X);
         sivia(X1);
         sivia(X2);
     end
     %drawnow();
end
% ----------------------  main   ----------------------------
vibes.beginDrawing(); % Initialize VIBes connection
vibes.newFigure('SIVIA using EASIBEX and VIBes'); % Create a new VIBes figure
X=[[-4,4];[-4,4]];
vibes.drawBox(X,'green','black');
vibes.axisAuto();
sivia(X);
vibes.endDrawing(); % Closes VIBes connection
end
