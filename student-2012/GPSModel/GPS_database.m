load GPS;
Data_rate_Height = 4; %How many reading per second, here 4Hz
Data_rate_Latitude = 1;
Data_rate_Longitude = 1;

% Latitude and Longitude has 1 readings per second
Latitude = Latitude - mean(Latitude);
LeLat = length(Latitude);
LatitudeX = (1:(1/Data_rate_Latitude):(LeLat+Data_rate_Latitude-1)*(1/Data_rate_Latitude))';
TimeLa = ceil((LeLat+Data_rate_Latitude-1)*(1/Data_rate_Latitude));


Longitude = Longitude - mean(Longitude);
LeLong = length(Longitude);
LongitudeX = (1:(1/Data_rate_Longitude):(LeLong+Data_rate_Longitude-1)*(1/Data_rate_Longitude))';
TimeLo = ceil((LeLong+Data_rate_Longitude-1)*(1/Data_rate_Longitude));

% Height has 4 readings per second
Height = Height - mean(Height);
LeHeigLatitudeht = length(Height);
HeightX = (1:(1/Data_rate_Height):(LeHeight+Data_rate_Height-1)*(1/Data_rate_Height))';
TimeHe = ceil((LeHeight+3)*(1/Data_rate_Height));