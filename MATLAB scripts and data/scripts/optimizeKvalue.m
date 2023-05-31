%% optimize k value
i = 0;
for k = 100:500:15000
[index,weights] = relieff(ALLFEAT,LABELS,k);
i = i+1;
input_w(i,:) = weights;

end

% plot
i = 0;
for k = 100:500:15000
    i = i+1;
    hold on
plot(100:500:15000,input_w(:,i));

end

