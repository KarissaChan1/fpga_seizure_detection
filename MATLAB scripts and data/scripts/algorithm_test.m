%% GET FEATURES
% load('interictal_seg.mat'); %already normalized
% load('seizure_seg.mat');
all_seg = vertcat(seizure_seg,interictal_seg);
[r,c]=size(all_seg);
clear a5features d5features d4features d3features d2features tffeatures t_a5 t_d5 t_d4 t_d3 t_d2 t_tf arr_a5 arr_d5 arr_d4 arr_d3 arr_d2 arr_tf ALLFEAT d
for i = 1:r
%  [d{i,1},~] = dwt_decomp(all_seg(i,:));
   d{i,1} = newsegwt_decomp(all_seg(i,:));
    [a5features(i,1),d5features(i,1),d4features(i,1),d3features(i,1),d2features(i,1)]=dwt_feature_extract(d{i,1});
    tffeatures(i,:) = tf_feature_extract(all_seg(i,:));
    
end

t_a5 = struct2table(a5features);    arr_a5 = table2array(t_a5);
t_d5 = struct2table(d5features);    arr_d5 = table2array(t_d5);
t_d4 = struct2table(d4features);    arr_d4 = table2array(t_d4);
t_d3 = struct2table(d3features);    arr_d3 = table2array(t_d3);
t_d2 = struct2table(d2features);    arr_d2 = table2array(t_d2);
t_tf = struct2table(tffeatures);    arr_tf = table2array(t_tf);

ALLFEAT = [arr_tf arr_d2 arr_d3 arr_d4 arr_d5 arr_a5];
% save(fullfile('C:\Users\Karissa\Desktop\USRA University of Toronto 2020\Epilepsy_CLS Project\algorithm scripts\data','ALLFEAT.mat'),'ALLFEAT','-v7.3')

%% get labels
clear LABELS
for i = 1:5041
    
   LABELS(i,1) = "Ictal";
end

for i = 5042:r
    
    LABELS(i,1) = "Interictal";
end

% save(fullfile('C:\Users\Karissa\Desktop\USRA University of Toronto 2020\Epilepsy_CLS Project\algorithm scripts\data','ALLlabels.mat'),'LABELS','-v7.3')

%% feature selection

% [r,c] = size(ALLFEAT);
%         [index,~] = relieff(ALLFEAT,LABELS,10500);
%         relieffeat = zeros(r,10);
               clear relieffeat
%                load('relieff_index_new.mat');
        for k = 1:10
            relieffeat(:,k) = ALLFEAT(:,index(k));
        end
        
%  save(fullfile('C:\Users\Karissa\Desktop\USRA University of Toronto 2020\Epilepsy_CLS Project\algorithm scripts\data','SELECTED_FEAT.mat'),'relieffeat','-v7.3')

%% partition data set
clear trainset testset trainclasses testclasses
rand_idx = randperm(r);

for k = 1:floor(r*0.75)
    trainset(k,:) = relieffeat(rand_idx(k),:);
    trainclasses(k,1) = LABELS(rand_idx(k));
end

x = 1;
for k = floor(r*0.75)+1:r
    testset(x,:) = relieffeat(rand_idx(k),:);
    testclasses(x,1) =LABELS(rand_idx(k));
    x = x+1;
end
% save(fullfile('C:\Users\Karissa\Desktop\USRA University of Toronto 2020\Epilepsy_CLS Project\algorithm scripts\data','TRAIN.mat'),'trainset','-v7.3')
% save(fullfile('C:\Users\Karissa\Desktop\USRA University of Toronto 2020\Epilepsy_CLS Project\algorithm scripts\data','TRAINlabels.mat'),'trainclasses','-v7.3')
% save(fullfile('C:\Users\Karissa\Desktop\USRA University of Toronto 2020\Epilepsy_CLS Project\algorithm scripts\data','TEST.mat'),'testset','-v7.3')
% save(fullfile('C:\Users\Karissa\Desktop\USRA University of Toronto 2020\Epilepsy_CLS Project\algorithm scripts\data','TESTlabels.mat'),'testclasses','-v7.3')


%% train and optimize model

rng default
% mdl = fitclinear(trainset,trainclasses);
Mdl_opt = fitclinear(trainset,trainclasses);
% ,'OptimizeHyperparameters','auto',...
%     'HyperparameterOptimizationOptions',struct('AcquisitionFunctionName',...
%     'expected-improvement-plus'));

%% test
% load('trainedSVM_5000.mat');
%  ypred = predict(trainedModel2.ClassificationSVM,testset);
ypred = predict(Mdl_opt,testset);

for i = 1:floor(r*0.25)
    ypred_c(i,1) = convertCharsToStrings(ypred(i));
    tf(i) = strcmp(ypred_c(i),testclasses(i));
end

% accuracy = sum(tf,'all')/floor(r*0.25);

%% calculate sensitivity

% TP/TP+TN

TP = 0;
TN = 0;
numP = 0;
numN = 0;
for i = 1:floor(r*0.25)
    if strcmp(testclasses(i),'Ictal')== 1
        numP = numP+1;
    end
    if strcmp(testclasses(i),'Interictal')== 1
        numN = numN+1;
    end
    
    if tf(i)== 1 && strcmp(testclasses(i),'Ictal')== 1
        TP = TP + 1;
    end
    
    if tf(i)== 1 && strcmp(testclasses(i),'Interictal') == 1
        TN = TN + 1;
    end
       
end

FP = 0;
FN = 0;
for i = 1:floor(r*0.25)
    if tf(i) == 0 && strcmp(testclasses(i),'Interictal') == 1
        FP = FP + 1;
    end
    if tf(i) == 0 && strcmp(testclasses(i),'Ictal') == 1
        FN = FN + 1;
    end
    
end


sensitivity = TP/(TP+FN);
specificity = TN/(TN+FP);
FPR = FP/(FP+TN);
TPR = TP/(TP+FN);
TNR = TN/(TN+FP);
acc = (TP+TN)/(numP+numN);