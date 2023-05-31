function coeff = downsamp(conv,level)

    switch level
        case 1
            nlevel = 128;
        case 2
            nlevel = 64;
        case 3
            nlevel = 32;
        case 4
            nlevel = 16;
        case 5
            nlevel = 8;
    end

    for i = 1:nlevel
        coeff(1,i) = conv(1,i*2);
    end
    
    
end
