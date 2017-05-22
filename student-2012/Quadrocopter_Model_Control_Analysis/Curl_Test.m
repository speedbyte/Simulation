CM=[-1+1i -1-1i; 1-1i -1-1i];

[R C]=size(CM);
[x,y]=meshgrid(-R/2:1:R/2);
x_v=real(CM);
y_v=imag(CM);

quiver(x,y,x_v,y_v)
cav2=curl(x,y,x_v,y_v)