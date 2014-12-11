function drawbox(X,colin,colout)
   x1=X(1,1); x2=X(1,2); 
   y1=X(2,1); y2=X(2,2); 
   M=[x1, x2, x2, x1, x1;  
      y1, y1, y2, y2, y1] ;
   plot([x1, x2, x2, x1, x1],[y1, y1, y2, y2, y1],colout);            
   fill([x1, x2, x2, x1, x1],[y1, y1, y2, y2, y1],colin);
   drawnow();  
end
  
  
   