clear all
close all
clc


d = 0.85;
Edges = [1 4; 1 6; 2 3; 2 4; 2 5; 3 5; 3 6; 3 7; 4 5; 4 6; 5 4; 5 6; 6 4; 6 7; 7 6;];
page_nr = length(unique(Edges)); % Take the unique valuse from edges matrix
links_nr = size(Edges,1); % Take the number of links from first size part (from 15x2)
b = ((1-d)/page_nr) * (ones(page_nr, 1));
I = speye(page_nr); % identity matrix

B = sparse(Edges(:,2), Edges(:,1), 1);


% sum of each column in B gives as amount of points to this site
% sum(B,1) - gives sum of each column
% sum(B, 2) - gives sum of each row
L = sum(B, 1);
% diag(L) gives us an L vector thrown onto main diagonal on matrix
A = sparse(diag(1./L)); % take 1/L vector and throw onto main diagonal

M = I - d*B*A;
% DO NOT USE inv(M) - unstable numerical algorithm - it makes some numerical error
r = M\b; % IT IS NOT SIMPLE DIVISION
% backslash is an operator that chooses the best algorithm to solve the equation

bar(r);