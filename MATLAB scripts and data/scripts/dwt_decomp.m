function [d,a] = dwt_decomp(segment)

    % level 1 dwt
    conv1 = conv_lo(segment,1);
    a1 = downsamp(conv1,1);
    a{1,1} = a1;
    
    conv1_hi = conv_hi(segment,1);
    d1 = downsamp(conv1_hi,1);
    d{1,1} = d1;
    
    %level 2 dwt
    conv2 = conv_lo(a1,2);
    a2 = downsamp(conv2,2);
    a{2,1} = a2;
    
    conv2_hi = conv_hi(a1,2);
    d2 = downsamp(conv2_hi,2);
    d{2,1} = d2;
    
    %level 3 dwt
    conv3_lo = conv_lo(a2,3);
    a3 = downsamp(conv3_lo,3);
    a{3,1} = a3;
    
    conv3_hi = conv_hi(a2,3);
    d3 = downsamp(conv3_hi,3);
    d{3,1} = d3;
    
    %level 4 dwt
    conv4_lo = conv_lo(a3,4);
    a4 = downsamp(conv4_lo,4);
    a{4,1} = a4;
    
    conv4_hi = conv_hi(a3,4);
    d4 = downsamp(conv4_hi,4);
    d{4,1} = d4;
    
    %level 5 dwt
    conv5_lo = conv_lo(a4,5);
    a5 = downsamp(conv5_lo,5);
    a{5,1} = a5;
    d{6,1} = a5;
    
    conv5_hi = conv_hi(a4,5);
    d5 = downsamp(conv5_hi,5);
    d{5,1} = d5;
    
    
   

end



