clear
clc
load gradient.txt; load hessian.txt; load initial.txt
c=-(hessian\gradient);
a=initial+c;

filename = 'solution.off';
fid = fopen(filename, 'w');

fprintf(fid,'OFF \n');
fprintf(fid,'16 18 0 \n');
for row=1:48
    fprintf(fid,'%d \t', a(row,1));
    if mod(row,3)==0
        fprintf(fid,'\n');
    end
end
fprintf(fid,'3 5 1 0 \n');
fprintf(fid,'3 0 4 5 \n');
fprintf(fid,'3 6 2 1 \n');
fprintf(fid,'3 1 5 6 \n');
fprintf(fid,'3 7 3 2 \n');
fprintf(fid,'3 2 6 7 \n');
fprintf(fid,'3 9 5 4 \n');
fprintf(fid,'3 4 8 9 \n');
fprintf(fid,'3 10 6 5 \n');
fprintf(fid,'3 5 9 10 \n');
fprintf(fid,'3 11 7 6 \n');
fprintf(fid,'3 6 10 11 \n');
fprintf(fid,'3 13 9 8 \n');
fprintf(fid,'3 8 12 13 \n');
fprintf(fid,'3 14 10 9 \n');
fprintf(fid,'3 9 13 14 \n');
fprintf(fid,'3 15 11 10 \n');
fprintf(fid,'3 10 14 15 \n');

fclose(fid);

filename = 'iterate.txt';
fid1 = fopen(filename, 'w');

for row=49:53
    fprintf(fid1,'%d \t', a(row,1));
end

fclose(fid1);
