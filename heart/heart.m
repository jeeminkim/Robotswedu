x = zeros(13, 1);
y = zeros(24, 1);

x(1) = -1.139;
x(2) = -1.0;
x(3) = -0.8;
x(4) = -0.6;
x(5) = -0.4;
x(6) = -0.2;
x(7) = 0;
x(8) = 0.2;
x(9) = 0.4;
x(10) = 0.6;
x(11) = 0.8;
x(12) = 1.0;
x(13) = 1.139;

syms ys;
for i = 1:1:13
    equation = (x(i)^2 + ys^2 - 1)^3 - x(i)^2 * ys^3 == 0;
    answer = solve(equation, ys);
    if (size(answer, 1) == 2)
        if (answer(1) <= answer(2))
            sol = answer(1);
        else
            sol = answer(2);
        end
    else
        sol = answer(1);
    end
    y(i) = sol;
end

j = 14;
for i = 12:-1:2
    equation = (x(i)^2 + ys^2 - 1)^3 - x(i)^2 * ys^3 == 0;
    answer = solve(equation, ys);
    if (size(answer, 1) == 2)
        if (answer(1) >= answer(2))
            sol = answer(1);
        else
            sol = answer(2);
        end
    else
        sol = answer(1);
    end
    y(j) = sol;
    j = j + 1;
    answer
end
