function [ Out ] = myserial( In )
%SERIAL Summary of this function goes here
%   Detailed explanation goes here
s = serial('COM2')
fopen(s)
fclose(s)

Out = In;

end

