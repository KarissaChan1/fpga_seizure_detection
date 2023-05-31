%% GET FEATURES
% load('eeg63_segments.mat');
clear a5features d5features d4features d3features d2features tffeatures t_a5 t_d5 t_d4 t_d3 t_d2 t_tf arr_a5 arr_d5 arr_d4 arr_d3 arr_d2 arr_tf ALLFEAT
[r,c] = size(segments);
for i = 1:r
%  [d{i,1},~] = dwt_decomp(segments(i,:));
   d{i,1} = newsegwt_decomp(segments(i,:));
    [a5features(i,1),d5features(i,1),d4features(i,1),d3features(i,1),d2features(i,1)]=dwt_feature_extract(d{i,1});
    tffeatures(i,:) = tf_feature_extract(segments(i,:));
    
end

t_a5 = struct2table(a5features);    arr_a5 = table2array(t_a5);
t_d5 = struct2table(d5features);    arr_d5 = table2array(t_d5);
t_d4 = struct2table(d4features);    arr_d4 = table2array(t_d4);
t_d3 = struct2table(d3features);    arr_d3 = table2array(t_d3);
t_d2 = struct2table(d2features);    arr_d2 = table2array(t_d2);
t_tf = struct2table(tffeatures);    arr_tf = table2array(t_tf);

ALLFEAT = [arr_tf arr_d2 arr_d3 arr_d4 arr_d5 arr_a5];

%% feature selection
 load('relieff_index_new.mat'); 
clear relieffeat
        for k = 1:10
            relieffeat(:,k) = ALLFEAT(:,index(k));
        end
        
 %% write svm model
 
load('mdl_new.mat');
weights = Mdl_opt.Beta;

D = 0;
for k = 1:r
    for i = 1:10
        D = D + weights(i)*relieffeat(k,i);
    end
    F(k) = D + Mdl_opt.Bias;
    label(k) = sign(F(k));
    if label(k) == -1
        label(k) = 1;
    else
        label(k) = 0;
    end
    
    
    D = 0;
end
% label = medfilt1(label,13);

%% use matlab model
load('mdl_new.mat');
ypred = predict(Mdl_opt,relieffeat);

for i = 1:r
    ypred_c(i,1) = convertCharsToStrings(ypred(i));
    if strcmp(ypred_c(i),'Ictal') == 1
        label(i) = 1;
    else
        label(i) = 0;
    end
end
FP = 0;
TN = 0;
for i = 1:sz_period(1)-1
    if label(i) == 1
        FP = FP + 1;
    end
    if label(i) == 0
        TN = TN + 1;
    end
end

for i = sz_period(2)+1:r
    if label(i) == 1
        FP = FP + 1;
    end
    if label(i) == 0
        TN = TN + 1;
    end
end
TP = 0;
FN = 0;
for i = sz_period(1):sz_period(2)
    if label(i) == 1
        TP = TP + 1;
    end
    if label(i) == 0
        FN = FN +1;
    end
end


sensitivity = TP/(TP+FN);
specificity = TN/(TN+FP);
FPR = FP/(FP+TN);
TPR = TP/(TP+FN);
TNR = TN/(TN+FP);


%% get accuracies
FP = 0;
TN = 0;
for i = 1:sz_period(1)-1
    if label(i) == 1
        FP = FP + 1;
    end
    if label(i) == 0
        TN = TN + 1;
    end
end


for i = sz_period(2):2497
    if label(i) == 1
        FP = FP + 1;
    end
    if label(i) == 0
        TN = TN + 1;
    end
end
for i = sz_period(2):2497
    if label(i) == 1
        FP = FP + 1;
    end
    if label(i) == 0
        TN = TN + 1;
    end
end
for i = 2540:r
    if label(i) == 1
        FP = FP + 1;
    end
    if label(i) == 0
        TN = TN + 1;
    end
end
TP = 0;
FN = 0;
for i = sz_period(1):sz_period(2)
    if label(i) == 1
        TP = TP + 1;
    end
    if label(i) == 0
        FN = FN +1;
    end
end
for i = 2498:2539
    if label(i) == 1
        TP = TP + 1;
    end
    if label(i) == 0
        FN = FN +1;
    end
end


sensitivity = TP/(TP+FN);
specificity = TN/(TN+FP);
FPR = FP/(FP+TN);
TPR = TP/(TP+FN);
TNR = TN/(TN+FP);

%% plot subplots
figure;
subplot(3,1,1); plot(norm_sig); xlim([0 r*256]);
% y = medfilt1(label,13);
% subplot(3,1,3); plot(y);ylim([-0.5 2]); xlim([0 r]);xline(sz_period(1)); xline(sz_period(2));xline(2498);xline(2539);
subplot(3,1,2); plot(label); ylim([-0.5 2]); xlim([0 r]);
xline(sz_period(1)); xline(sz_period(2));
% subplot(3,1,2); plot(tf); ylim([-0.5 2]); xlim([0 r]);
% xline(sz_period(1)); xline(sz_period(2));
