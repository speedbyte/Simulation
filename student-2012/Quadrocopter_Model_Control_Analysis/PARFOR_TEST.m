clear all;

x=0;
parfor i=1:100
    x=x+sin(i)+cos(i)
end