//PROGRAM 1:

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main()
{
    //initiate calculation variables
    int n, nFactorialExpand, stirlingsApproxExpand, expandDiff;
    double nFactorial, stirlingsApprox, error;
    
    //tab for display
    const char TAB = '\t';
    
    //program parameters
    const int N_LOWER = 1, N_UPPER = 100;
    
    //introduction and header
    cout << "Family name: Yip\nStudent ID: 20267919\n";
    cout << "n\tn!\t\tStirling's Approx\tError\n---------------------------"
        << "--------------------------\n";
    
    //main loop
    for (n = N_LOWER; n <= N_UPPER; n++)
    {
        //For n!
        nFactorial = 1;
        nFactorialExpand = 0;
        for (int k = 1; k <= n; k++)
        {
            nFactorial *= k;
            while (nFactorial >= 10)
            {
                nFactorial /= 10;
                nFactorialExpand++;
            }
        }
        
        //For  (n/e)^n
        stirlingsApproxExpand = 0;
        stirlingsApprox = pow(n / exp(1), n) * sqrt(2 * M_PI * n);
        while (stirlingsApprox >= 10)
        {
            stirlingsApprox /= 10;
            stirlingsApproxExpand++;
        }
        if (stirlingsApprox < 1)
        {
            stirlingsApprox *= 10;
            stirlingsApproxExpand--;
        }
        
        //For error
        expandDiff = stirlingsApproxExpand - nFactorialExpand;
        error = 100 * (nFactorial - stirlingsApprox * pow(10, expandDiff)) / 
            nFactorial;
        
        //output
        cout << fixed << setprecision(4) << n << TAB << nFactorial << "E" 
            << nFactorialExpand << TAB << stirlingsApprox << "E" 
            << stirlingsApproxExpand << TAB << TAB;
        cout << fixed << setprecision(2) << error << "%" << endl;
        
    }

    return 0;
}

/* ------------------------------RUN 1-----------------------------------------

Family name: Yip
Student ID: 20267919
n       n!              Stirling's Approx       Error
-----------------------------------------------------
1       1.0000E0        9.2214E-1               7.79%
2       2.0000E0        1.9190E0                4.05%
3       6.0000E0        5.8362E0                2.73%
4       2.4000E1        2.3506E1                2.06%
5       1.2000E2        1.1802E2                1.65%
6       7.2000E2        7.1008E2                1.38%
7       5.0400E3        4.9804E3                1.18%
8       4.0320E4        3.9902E4                1.04%
9       3.6288E5        3.5954E5                0.92%
10      3.6288E6        3.5987E6                0.83%
11      3.9917E7        3.9616E7                0.75%
12      4.7900E8        4.7569E8                0.69%
13      6.2270E9        6.1872E9                0.64%
14      8.7178E10       8.6661E10               0.59%
15      1.3077E12       1.3004E12               0.55%
16      2.0923E13       2.0814E13               0.52%
17      3.5569E14       3.5395E14               0.49%
18      6.4024E15       6.3728E15               0.46%
19      1.2165E17       1.2111E17               0.44%
20      2.4329E18       2.4228E18               0.42%
21      5.1091E19       5.0889E19               0.40%
22      1.1240E21       1.1198E21               0.38%
23      2.5852E22       2.5759E22               0.36%
24      6.2045E23       6.1830E23               0.35%
25      1.5511E25       1.5460E25               0.33%
26      4.0329E26       4.0200E26               0.32%
27      1.0889E28       1.0855E28               0.31%
28      3.0489E29       3.0398E29               0.30%
29      8.8418E30       8.8164E30               0.29%
30      2.6525E32       2.6452E32               0.28%
31      8.2228E33       8.2008E33               0.27%
32      2.6313E35       2.6245E35               0.26%
33      8.6833E36       8.6614E36               0.25%
34      2.9523E38       2.9451E38               0.24%
35      1.0333E40       1.0309E40               0.24%
36      3.7199E41       3.7113E41               0.23%
37      1.3764E43       1.3733E43               0.22%
38      5.2302E44       5.2188E44               0.22%
39      2.0398E46       2.0354E46               0.21%
40      8.1592E47       8.1422E47               0.21%
41      3.3453E49       3.3385E49               0.20%
42      1.4050E51       1.4022E51               0.20%
43      6.0415E52       6.0298E52               0.19%
44      2.6583E54       2.6532E54               0.19%
45      1.1962E56       1.1940E56               0.19%
46      5.5026E57       5.4927E57               0.18%
47      2.5862E59       2.5817E59               0.18%
48      1.2414E61       1.2392E61               0.17%
49      6.0828E62       6.0725E62               0.17%
50      3.0414E64       3.0363E64               0.17%
51      1.5511E66       1.5486E66               0.16%
52      8.0658E67       8.0529E67               0.16%
53      4.2749E69       4.2682E69               0.16%
54      2.3084E71       2.3049E71               0.15%
55      1.2696E73       1.2677E73               0.15%
56      7.1100E74       7.0994E74               0.15%
57      4.0527E76       4.0468E76               0.15%
58      2.3506E78       2.3472E78               0.14%
59      1.3868E80       1.3849E80               0.14%
60      8.3210E81       8.3094E81               0.14%
61      5.0758E83       5.0689E83               0.14%
62      3.1470E85       3.1428E85               0.13%
63      1.9826E87       1.9800E87               0.13%
64      1.2689E89       1.2672E89               0.13%
65      8.2477E90       8.2371E90               0.13%
66      5.4434E92       5.4366E92               0.13%
67      3.6471E94       3.6426E94               0.12%
68      2.4800E96       2.4770E96               0.12%
69      1.7112E98       1.7092E98               0.12%
70      1.1979E100      1.1964E100              0.12%
71      8.5048E101      8.4948E101              0.12%
72      6.1234E103      6.1164E103              0.12%
73      4.4701E105      4.4650E105              0.11%
74      3.3079E107      3.3042E107              0.11%
75      2.4809E109      2.4782E109              0.11%
76      1.8855E111      1.8834E111              0.11%
77      1.4518E113      1.4503E113              0.11%
78      1.1324E115      1.1312E115              0.11%
79      8.9462E116      8.9368E116              0.11%
80      7.1569E118      7.1495E118              0.10%
81      5.7971E120      5.7912E120              0.10%
82      4.7536E122      4.7488E122              0.10%
83      3.9455E124      3.9416E124              0.10%
84      3.3142E126      3.3110E126              0.10%
85      2.8171E128      2.8143E128              0.10%
86      2.4227E130      2.4204E130              0.10%
87      2.1078E132      2.1057E132              0.10%
88      1.8548E134      1.8531E134              0.09%
89      1.6508E136      1.6493E136              0.09%
90      1.4857E138      1.4843E138              0.09%
91      1.3520E140      1.3508E140              0.09%
92      1.2438E142      1.2427E142              0.09%
93      1.1568E144      1.1557E144              0.09%
94      1.0874E146      1.0864E146              0.09%
95      1.0330E148      1.0321E148              0.09%
96      9.9168E149      9.9082E149              0.09%
97      9.6193E151      9.6110E151              0.09%
98      9.4269E153      9.4189E153              0.08%
99      9.3326E155      9.3248E155              0.08%
100     9.3326E157      9.3248E157              0.08%


Process exited with code: 0
---------------------------------------------------------------------------- */