#include <iostream>
#include<vector>
#include<math.h>

using namespace std;

long fact (long number);
long combination (long number1, long number2);
bool equal_arrays(long array1[], long array2[]);

bool equal_arrays(long array1[], long array2[], long Size)
{
    for(long i = 0; i < Size; i++)
    {
        if(array1[i] != array2[i])
            return false;
    }
    return true;
}

long combination (long number1, long number2)
{
    return (fact(number1)/(fact(number2) * fact(number1 - number2)));
}

long fact (long number)
{
    long result = 1;
    for(long i = 1; i <= number; i++)
        result = result * i;
    return result;
}

int main(void)
{
    long number_of_cuts, input;

    vector<long> L;
    vector<long> values;

    cout<<"Enter L-set then press L :\n";
    long n;
    for(n = 1; 1; n++)
    {
        if(cin>>input)
            L.push_back(input);
        else break;
    }

    long maximum =  L[0];
    for(long i = 1; i < L.size(); i++)
    {
        if(L[i] > maximum)
            maximum = L[i];
    }
    cout<<"Maximum: "<<maximum<<endl;

    float a, b, c, x1, x2, determinant, realPart, imaginaryPart;
    a = 1;
    b = -1;
    c = -2*(n);
    determinant = b*b - 4*a*c;

    if (determinant > 0)
    {
        x1 = (-b + sqrt(determinant)) / (2*a);
        x2 = (-b - sqrt(determinant)) / (2*a);
        if(x1 >= 0)
        {
            number_of_cuts = x1;
        }
        else if(x2 >= 0)
        {
            number_of_cuts = x2;
        }
    }

    else if (determinant == 0)
    {
        x1 = (-b + sqrt(determinant)) / (2*a);
        number_of_cuts = x1;
    }

    else
    {
        realPart = -b/(2*a);
        imaginaryPart =sqrt(-determinant)/(2*a);
        number_of_cuts = realPart;
    }

    cout<<"Number of cuts = "<<number_of_cuts<<endl;

    long L_sorted[L.size()];
    for(long i = 0; i < L.size(); i++)
        L_sorted[i] = L.at(i);

    long temp;
    for(long j = 0; j < L.size(); j++)
    {
        for(long i = j+1; i < L.size(); i++)
        {
            if(L_sorted[j] > L_sorted[i])
            {
                temp = L_sorted[j];
                L_sorted[j] = L_sorted[i];
                L_sorted[i] = temp;
            }
        }
    }

    for(long i = 0; i <= maximum; i++)
        values.push_back(i);

    long temps[number_of_cuts];
    for(long i = 0; i < number_of_cuts-2; i++)
    {
        temps[i] = values[i+1];
    }

    long number_of_sets = combination(maximum-1, number_of_cuts-2);
    long X[number_of_sets][number_of_cuts];

    long j;
    for(long i = 0; i < number_of_sets; i++)
    {
        for(j = 0; j < number_of_cuts; j++)
        {
            if(j == 0) X[i][j] = 0;
            else
            {
                X[i][j] = temps[j-1];
            }
        }
    }

    for(long i = 0; i < number_of_sets; i++)
    {
        for(j = 1; j < number_of_cuts-1; j++)
        {
            X[i][j] = temps[j-1];
        }
        temps[j-2]++;
        for(long k = 0; k < number_of_cuts-3; k++)
        {
            if(temps[j-2-k] >= maximum-k)
            {
                temps[j-2-(k+1)]++;
                temps[j-2-k] = temps[j-2-(k+1)]+1;
                X[i][j] = temps[j-2-k];
            }

        }
        if(temps[j-2] >= maximum)
        {
            for(long k = 1; k < number_of_cuts-3; k++)
            {
                temps[k] = temps[k-1]+1;
            }
        }
        for(j = 1; j < number_of_cuts-1; j++)
        {
            if(X[i][j] >= maximum-1)
                X[i][j] = maximum - (number_of_cuts-j-1);
        }

    }

    for(long i = 0; i < number_of_sets; i++)
    {
        for(j = 0; j < number_of_cuts-1; j++);
        X[i][j] = maximum;
    }

    for(long i = 0; i < number_of_sets; i++)
    {
        cout<<"X["<<i<<"] {";
        for(long u = 0; u < number_of_cuts; u++)
        {
            if(u == number_of_cuts-1)
                cout<<X[i][u];
            else cout<<X[i][u]<<", ";
        }
        cout<<"}"<<endl;
    }

    long deltaX[((number_of_cuts * (number_of_cuts-1)/2))];
    long counter = 0;
    bool solution_found = false;
    for(long k = 0; k < number_of_sets; k++)
    {
        for(long i = 0; i < number_of_cuts-1; i++)
        {
            for(long j = i+1; j < number_of_cuts; j++)
            {
                deltaX[counter] = X[k][j] - X[k][i];
                counter++;
            }
        }

        long temp;
        for(long m = 0; m < L.size(); m++)
        {
            for(long n = m+1; n < L.size(); n++)
            {
                if(deltaX[m] > deltaX[n])
                {
                    temp = deltaX[m];
                    deltaX[m] = deltaX[n];
                    deltaX[n] = temp;
                }
            }
        }

        if(equal_arrays(deltaX, L_sorted, L.size()))
        {
            solution_found = true;
            cout<<"Correct X set: {";
            for(long w = 0; w < number_of_cuts; w++)
            {
                if(w == number_of_cuts-1)
                    cout<<X[k][w];
                else cout<<X[k][w]<<", ";
            }


            cout<<"}"<<endl;
            cout<<" solution found after "<<k+1<<" iterations"<<endl;
            break;
        }
        else counter = 0;
    }

    if(!solution_found)
        cout<<"No solution!"<<endl;



    return 0;

}
