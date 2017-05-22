clear all;
close all;
clc;

javaaddpath('Valiquad.jar');

import valiquad.comm.*
import valiquad.general.*
import java.io.*
import java.lang.*
import gnu.io.*

clear java

con = ConnectionAsync();    % baut eine asynchrone Verbindung auf
con.getPortList             % gibt die vorhandenen COM-Ports aus


cp = 'COM8'                 % COM-Port der genutzt wird
time = now;                 % 


an = Analyzer.getInstance();    % Analysiert die empfangenen Daten

msg = Messager(an, con);        % regelt das Messaging für das Protokol
comm = Communication(msg);      % regelt die Kommunikation zwischen Quadrokopter und Analysiersoftware 
conf = Configuration(comm);     % regelt die Konfiguration der Frames und Parameter

con.open(cp, msg);              % öffnet COM-Port um eine Verbindung aufzubauen
an.setConfigurationService(conf); % setzt den Konfigurations-Service für den Analyzer 

str = 'null';

while (strcmp(str, 'exit') ~= 1) 
        
        str = String(input('was soll gemacht werden? = ','s'));
        
        if (str.startsWith('start'))
            
            msg.sendMessage(cast(1, 'uint8'), cast(10, 'uint8')); %Kommunikation starten
            
            x = 1;
            i = 1;
            k = 1;
            y = 1;
            z = 1;
            xAchseAccX = 0;
            accX = 0;
            xAchseAccY = 0;
            accY = 0;
            xAchseAccZ = 0;
            accZ = 0;
            
            figure(1)
            plotHandleAccX = plot(xAchseAccX, accX);
            title('accX')
            axis auto;
            grid on;
             
             
            figure(2)
            plotHandleAccY = plot(xAchseAccY, accY);
            title('accY')
            axis auto;
            grid on;
             
            figure(3)
            plotHandleAccZ = plot(xAchseAccZ, accZ);
            title('accZ')
            axis auto;
            grid on;
            
            
            while (i < 1000)
                
                buffer = msg.readMessage(); %Stream empfangen
                msg.notify(buffer); %auf Richtigkeit prüfen
                
                id(i) = an.id;
                daten(i) = an.longdaten;
                switch id(i)
                    case -12287 %accX = -12287  accXRaw = -12288
                     accX(x) = an.longdaten;
                     xAchseAccX(x) = x;
                     
                     set(plotHandleAccX,'XData',[1:x]);
                     set(plotHandleAccX,'YData',accX(1:x));
                     drawnow
                     
                     x = x + 1;
                     
                    case  -12285 %accY = -12285    accYRaw = -12286
                     accY(y) = an.longdaten;
                     xAchseAccY(y) = y;
                     
                     
                     set(plotHandleAccY,'XData',[1:y]);
                     set(plotHandleAccY,'YData',accY(1:y));
                     drawnow

                     y = y + 1;
                     
                    case -12283 %accZ = -12283    accZRaw = -12284
                     accZ(z) = an.longdaten;
                     xAchseAccZ(z) = z;
                     
                     
                     set(plotHandleAccZ,'XData',[1:z]);
                     set(plotHandleAccZ,'YData',accZ(1:z));
                     drawnow

                     z = z + 1;
                     
                end     
                i=i+1;
            end
            
% 			conf.setSubPeriod(cast(10, 'uint8')) % !!!! Original !!!!
            
        elseif (str.startsWith('debug')) 
			conf.debug()
        elseif (str.startsWith('stop')) 
			conf.setSubPeriod(cast(0, 'uint8'))
        elseif (str.startsWith('config'))
			conf.clearObservables();
			% observable, int16, group 0, seq. 1, factor 1 -> accXRaw
% 			conf.addObservable(cast(53249,'uint16'), 1);
			% accYRaw
% 			conf.addObservable(cast(53251,'uint16'), 1);
			% accZRaw
			conf.addObservable(cast(53253,'uint16'), 4);
% 			
% 			% angR
% 			conf.addObservable(cast(32776,'uint16'), 1, Configuration.FRAME_D);
% 			% angP
% 			conf.addObservable(cast(32779,'uint16'), 1, Configuration.FRAME_D);
			conf.sendConfiguration();
        end
end

con.close();
