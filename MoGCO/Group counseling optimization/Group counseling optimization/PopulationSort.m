function [x, Cost] = PopulationSort(x, Cost)
% Sort the population and costs from best to worst
[Cost, indices] = sort(Cost, 'ascend');
x = x(indices, :);
return