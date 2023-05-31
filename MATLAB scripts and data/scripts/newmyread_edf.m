function [header,sig,annot]= newmyread_edf(record,s1,s2)
%function call: myread_edf('recording.edf',seizure start,seizure end)
%returns: header = recording information, channel = struct containing name
%of channel and channel recording

%read EEG
[header,sig]= edfread(record);

%read seizure annotations (if they exist)
annot = zeros(1,2);
annot(1,1) = s1;
annot(1,2) = s2;
