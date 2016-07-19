L1 = 18;
L2 = 16;

name = 'heart';
inputFileName = strcat(name, '.txt');
outputFileName = strcat(name, '_result.txt');
fid = fopen(inputFileName);
buffer = fgetl(fid);
data = textscan(fid,'%f%f','delimiter', ' ');

x = data{1};
y = data{2};
len = length(x);
theta2 = zeros(len, 1);
theta1 = zeros(len, 1);

for i = 1:len
    theta2(i) = acos((x(i)^2 + y(i)^2 - L1^2 - L2^2)/(2*L1*L2));
    syms theta;
    equation = L1 * sin(theta) + L2 * sin(theta + theta2(i)) - x(i) == 0;
    answer = solve(equation, theta);
    y1 = round(L1 * cos(answer(1)) + L2 * cos(answer(1) + theta2(i)));
    if (size(answer, 1) == 2)
        y2 = round(L1 * cos(answer(2)) + L2 * cos(answer(2) + theta2(i)));
        if (abs(y1 - y(i)) < abs(y2 - y(i)))
            sol = answer(1);
        else
            sol = answer(2);
        end
    else 
        sol = answer(1);
    end
    theta1(i) = round(sol * 100) / 100;
end

signal2 = zeros(len, 1);
signal1 = zeros(len, 1);

for i = 1:len
    signal2(i) = 512 + theta2(i) * (180 / pi) * (512 / 150);
    signal1(i) = 512 + theta1(i) * (180 / pi) * (512 / 150);
end

FID = fopen(outputFileName, 'w');
fprintf(FID, 'short signal1[%d]; short signal2[%d];\r\n', len, len);
fprintf(FID, 'int len = %d;\r\n', len);
for i = 0:len - 1
    fprintf(FID, 'signal1[%d] = %d; signal2[%d] = %d;\r\n', i, round(signal1(i+1)), i, round(signal2(i+1)));
end
fclose(FID);