function [] = saveSimResults()


yout = evalin('base','yout');
tout = evalin('base','tout');
quadModel = evalin('base','quadModel');
IC = evalin('base','IC');
pathExist = 'exist(''path'',''var'')';
if evalin('base',pathExist)
    path = evalin('base','path');
    data = {'yout', 'tout', 'quadModel', 'IC', 'path'};
else
    data = {'yout', 'tout', 'quadModel', 'IC'};
end
uisave(data,'simResults_1')
