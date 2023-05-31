function [timefreq_features] = tf_feature_extract(segment)
%segmatrix is a matrix of signal segments (150 segments x 6144 samples each)
j = 1;
%mean, coefficient of variation, rms, kurtosis, PSD


        avg = mean(segment);
        cov = mean(segment)/std(segment);
        r = rms(segment);
        kurt = kurtosis(segment);
        
        [pxx,f]=pwelch(segment);
        PSDestimate = mean(pxx);
        xIndex = find(pxx == max(pxx), 1, 'first');
        peakFreq(j,1) = f(xIndex);
        maxPSD(j,1)=max(pxx);

timefreq_features.mean = avg;
timefreq_features.COV = cov;
timefreq_features.RMS = r;
timefreq_features.kurtosis = kurt;
timefreq_features.PSD = PSDestimate;
timefreq_features.pkFreq = peakFreq;
timefreq_features.pkPSD = maxPSD;
timefreq_features



end