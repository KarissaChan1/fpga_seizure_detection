function [a5features,d5features,d4features,d3features, d2features]=dwt_feature_extract(bands)
    
    for i = 1:6
        M(i,1) = max(bands{i,1});
        m(i,1) = min(bands{i,1});
        avg(i,1) = mean(bands{i,1});
        absavg(i,1) = mean(abs(bands{i,1}));
        r(i,1) = rms(bands{i,1});
        E(i,1) = sum(abs((bands{i,1})).^2);
        stdev(i,1) = std(bands{i,1});
        sk(i,1) = skewness(bands{i,1});
        kurt(i,1) = kurtosis(bands{i,1});
        variance(i,1) = var(bands{i,1});
        P(i,1) = sum(abs((bands{i,1})).^2)/(2*length(bands{i,1})+1);
        ent(i,1) = wentropy(bands{i,1}, 'shannon');
        
    end
    
    a5features.max = M(6,1);
   
a5features.min = m(6,1);
a5features.mean = avg(6,1);
a5features.absmean = absavg(6,1);
a5features.RMS = r(6,1);
a5features.energy = E(6,1);
a5features.STD = stdev(6,1);
a5features.skew = sk(6,1);
a5features.kurtosis = kurt(6,1);
a5features.variance = variance(6,1);
a5features.power = P(6,1);
a5features.entropy = ent(6,1);
    
d5features.max = M(5,1); 
d5features.min = m(5,1);
d5features.mean = avg(5,1);
d5features.absmean = absavg(5,1);
d5features.RMS = r(5,1);
d5features.energy = E(5,1);  
d5features.STD = stdev(5,1);
d5features.skew = sk(5,1);
d5features.kurtosis = kurt(5,1);
d5features.variance = variance(5,1);
d5features.power = P(5,1);
d5features.entropy = ent(5,1);


d4features.max = M(4,1);
d4features.min = m(4,1);
d4features.mean = avg(4,1);
d4features.absmean = absavg(4,1);
d4features.RMS = r(4,1);
d4features.energy = E(4,1);  
d4features.STD = stdev(4,1);
d4features.skew = sk(4,1);
d4features.kurtosis = kurt(4,1);
d4features.variance = variance(4,1);
d4features.power = P(4,1);
d4features.entropy = ent(4,1);



d3features.max = M(3,1);
d3features.min = m(3,1);
d3features.mean = avg(3,1);
d3features.absmean = absavg(3,1);
d3features.RMS = r(3,1);
d3features.energy = E(3,1);  
d3features.STD = stdev(3,1);
d3features.skew = sk(3,1);
d3features.kurtosis = kurt(3,1);
d3features.variance = variance(3,1);
d3features.power = P(3,1);
d3features.entropy = ent(3,1);

d2features.max = M(2,1);
d2features.min = m(2,1);
d2features.mean = avg(2,1);
d2features.absmean = absavg(2,1);
d2features.RMS = r(2,1);
d2features.energy = E(2,1);  
d2features.STD = stdev(2,1);
d2features.skew = sk(2,1);
d2features.kurtosis = kurt(2,1);
d2features.variance = variance(2,1);
d2features.power = P(2,1);
d2features.entropy = ent(2,1);
    

end
