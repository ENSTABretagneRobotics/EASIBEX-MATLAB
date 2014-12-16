function sivia_easibex()
%------------------------------------------------------------------------
% function  b=inside(X) 
%   X1=X(1,:); X2=X(2,:); 
%   Y=Add(Sqr(X1),Sqr(X2));
%   b=i_belongs(Y,[1,2]);
% end
%------------------------------------------------------------------------
function r=Cout(X) 
  X1=X(1,:); X2=X(2,:); c=[2,2];
  %[X2,X1,c]=i_Csub(X2,X1,c);
  %[X2,X1]=i_Ctan(X2,X1);
  [X1,X2]=i_CinRing(X1,X2,1,2,[1,1.5]);
  r=[X1;X2];
end
%------------------------------------------------------------------------
function r=Cin(X) 
  X1=X(1,:); X2=X(2,:);
  [Xa1,Xa2]=i_CinRing(X1,X2,1,2,[-1,1]);
  [Xb1,Xb2]=i_CinRing(X1,X2,1,2,[1.5,Inf]);
  r=i_Union({[Xa1;Xa2];[Xb1;Xb2]});
end
%------------------------------------------------------------------------
function sivia(X)
     X0=X;
     drawbox(X,'blue','black');  
     X=Cout(X);
     drawbox(X,'red','magenta');  
     X=Cin(X);
     %b=inside(X);
     %if     	b==[1 1], drawbox(X,'red','magenta');  
     %elseif 	b==[0 0], drawbox(X,'blue','black');  
     if (i_Width(X)<0.25), drawbox(X,'yellow','yellow');    
     %if (i_decrease(X,X0)<0.1), drawbox(X,'yellow','yellow');    
     else
         [X1,X2]=i_Bisect(X);
         sivia(X1);
         sivia(X2);
     end
     drawnow();
end
% ----------------------  main   ----------------------------
clf(); hold on; 
axis([-4,4,-4,4]);   
axis('square'); 
X=[[-4,4];[-4,4]];
drawbox(X,'green','black');
sivia(X);
end
