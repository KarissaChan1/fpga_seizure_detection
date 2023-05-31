function c = conv_hi(segment,level)
 
 HiD = [ -0.0106,-0.0329,0.0308,0.1870,-0.0280,-0.6309,0.7148,-0.2304 ]; 
 
    switch level
        case 1
            nsig = 256;
        case 2
            nsig = 128;
        case 3
            nsig = 64;
        case 4
            nsig = 32;
        case 5
            nsig = 16;
    end
    
    c = zeros(1,nsig);
    for t = 1:nsig
        for k = 1:8
            if t-k <=0
                break;
            end
            c(1,t) = c(1,t) + segment(1,t-k)*HiD(1,k);
        end
    end

end