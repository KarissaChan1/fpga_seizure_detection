
function norm_value = normalised_diff( data )
% Normalise values of an array to be between -1 and 1
% original sign of the array values is maintained.
%   if abs(min(data)) > max(data)
% 
%       max_range_value = abs(min(data));
%       min_range_value = min(data);
%   else
%       max_range_value = max(data);
%       min_range_value = -max(data);
%   end
% 
% norm_value = 2 .* data ./ (max_range_value - min_range_value);
[r,c] = size(data);
	
	
	scalemin = -1;
	scalemax = 1;

   
	M = max(data);
	m = min(data);
    range = M-m;
    for i = 1:c
        x_std(1,i) = (data(1,i) - m) / range;
        norm_value(1,i) = x_std(1,i)*(scalemax-scalemin) + scalemin;
    end

	

end