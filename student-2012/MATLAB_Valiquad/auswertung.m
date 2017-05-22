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


for i=1:100

    switch id(i)
    case -12287 %accX = -12287  accXRaw = -12288
         
         accX(x) = daten(i);
         xAchseAccX(x) = x;

         figure(1)
         plot(xAchseAccX, accX);
         title('accX')
         axis auto;
         grid on;
         x = x + 1;

    case  -12285 %accY = -12285    accYRaw = -12286
         
         accY(y) = daten(i);
         xAchseAccY(y) = y;

         figure(2)
         plot(xAchseAccY, accY);
         title('accY')
         axis auto;
         grid on;

         

         y = y + 1;

        case -12283 %accZ = -12283    accZRaw = -12284
         accZ(z) = daten(i);
         xAchseAccZ(z) = z;


         figure(3)
         plot(xAchseAccZ, accZ);
         title('accZ')
         axis auto;
         grid on;

         z = z + 1;

    end  
    i=i+1;
end