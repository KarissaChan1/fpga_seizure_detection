function decomp = newsegwt_decomp(segment)
%#codegen
%uses DWT for 5 level signal decomposition
%A5 = delta band (0-4Hz)
%D5 = theta band (4-8Hz)
%D4 = alpha band (8-16Hz - can filter)
%D3 = beta band (16-32Hz - can filter)
%D2 = gamma band (32-64Hz)
    dwtmode('per','nodisp');
    [C,L]=wavedec(segment,5,'db4'); %l = number of coefficients by level, c = wavelet decomp vector
    [cd1,cd2,cd3,cd4,cd5] = detcoef(C,L,[1 2 3 4 5]);
    ca5 = appcoef(C,L,'db4');
    
 
   
D1 = wrcoef('d',C,L,'db4',1);
D2 = wrcoef('d',C,L,'db4',2);
D3 = wrcoef('d',C,L,'db4',3);
D4 = wrcoef('d',C,L,'db4',4);
D5 = wrcoef('d',C,L,'db4',5);
A5 = wrcoef('a',C,L,'db4',5);
% 
% decomp.d1 = D1;
% decomp.d2 = D2;
% decomp.d3 = D3;
% decomp.d4 = D4;
% decomp.d5 = D5;
% decomp.a5 = A5;
% decomp;

decomp{1,1} = cd1;
decomp{2,1} = cd2;
decomp{3,1} = cd3;
decomp{4,1} = cd4;
decomp{5,1} = cd5;
decomp{6,1} = ca5;


% figure,
% subplot(6,1,1)
% plot(segment);
% title('Original');
% subplot(6,1,2)
% plot(A5);
% title('Delta');
% subplot(6,1,3)
% plot(D5);
% title('Theta');
% subplot(6,1,4)
% plot(D4);
% title('Alpha');
% subplot(6,1,5)
% plot(D3);
% title('Beta');
% subplot(6,1,6)
% plot(D2);
% title('Gamma');





end