%% reading in seizure EEG recordings and annotations
load('EEG_annotations.mat');
[r,~] = size(A);
for k = 1:69
    annot2(k,:)=str2double(B(k,2:3));    
end

%% loop through all seizure EEG recordings and annotations for signal pre-processing, segmentation and feature extraction

for y = 1:69
    if exist(char(B(y)),'file')
        [header,sig,sz_period] = newmyread_edf(char(B(y)),annot2(y,1),annot2(y,2));

        signal = sig(any(sig,2),:); 
        [numchannels,~] = size(signal);
        t = header.records;
        fs = 256;
     %% averaging, filtering, normalizing of original time signals
       
        total = zeros(1,length(signal(1,:)));
        for x = 1:numchannels
            total = signal(x,:)+ total;
        end
        avgsig = total./numchannels;
        
        %filter and normalize averaged signal
     
        norm_sig = normalised_diff(avgsig);
        segments = buffer(norm_sig,256).';
        [r,c] = size(segments);

     %% extracting ictal and interictal segments from averaged signals
%         %seizure segments extracted fully according to annotations

         
        szstart = annot2(y,1);
        szend = annot2(y,2);
        
        k=1;
        for n = szstart:szend
            szseg(k,:) = segments(n,:);
            k = k+1;
       
        end
       
        sz_seg{y,1} = szseg;
        clear szseg
        
        %extract interictal segments
       
        nseg = szend-szstart;
        n1 = szstart-1; pre_rand_idx = randperm(n1);
        n2 = r - szend; post_rand_idx = randperm(n2);
        
        if nseg>n1
            for n = 1:n1
                pre_seg(n,:) = segments(pre_rand_idx(n),:);
            end
        else
            for n = 1:nseg
                pre_seg(n,:) = segments(pre_rand_idx(n),:);
            end
        end
        
        if nseg>n2
            for n = 1:n2
                post_seg(n,:) = segments(post_rand_idx(n),:);
            end
        else
            for n = 1:nseg
                post_seg(n,:) = segments(post_rand_idx(n),:);
            end
        end
        
        int_seg{y,1} = vertcat(pre_seg,post_seg);
        
       clear pre_seg post_seg 
        
     end
    

end

% sz_seg{63} = []; sz_seg{70} = [];
% int_seg{63} = []; int_seg{70} = [];
 
%% get numeric array
clear seizure_seg interictal_seg
seizure_seg = cell2mat(sz_seg); 
interictal_seg = cell2mat(int_seg);

      
  