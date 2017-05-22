function strCat=numStrCat(num)
    if(num< 10)
        strCat = strcat('00',num2str(num));
    elseif(num < 100)
        strCat = strcat('0',num2str(num));
    elseif(num<1000)
        strCat = num2str(num, 3);
    else
        strCat='Error_StrCat';
    end
end