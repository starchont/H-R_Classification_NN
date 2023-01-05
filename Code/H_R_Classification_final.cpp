#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <numeric>

using namespace std;

vector<string> read()
{
    ifstream fin;
    string line;
    vector<string> v;

    fin.open("HR6class.csv");
    while (true)
    {
        fin >> line;
        if (fin.eof())
            break;
        v.push_back(line);
    }
    return v;
}

vector<double> normalization(vector<double> &A)
{
    double max_val = 0, min_val = 0;
    vector<double> B(A.size());
    max_val = *max_element(A.begin(), A.end());
    min_val = *min_element(A.begin(), A.end());

    /*Normalization according to (X-x_min)/(x_max-x_min)*/
    for (int i = 0; i < A.size(); i++)
    {
        B[i] = (A[i] - min_val) / (max_val - min_val);
    }
    return B;
}

vector<double> normalization(vector<int> &A)
{
    double max_val, min_val;
    vector<double> B(A.size());
    max_val = *max_element(A.begin(), A.end());
    min_val = *min_element(A.begin(), A.end());

    /*Normalization according to (X-x_min)/(x_max-x_min)*/
    for (int i = 0; i < A.size(); i++)
    {
        B[i] = (A[i] - min_val) / (max_val - min_val);
    }
    return B;
}

vector<vector<double>> random_num_generator(int N, int col)
{
    vector<double> M(col, 0);
    vector<vector<double>> vec(N, M);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < col; j++)
        {
            double num = (double)rand() / RAND_MAX;
            vec[i][j] = num;
        }
    }
    return vec;
}

double activation_func(double value_u)
{
    double beta = 0.01;
    return (max(value_u, beta * value_u)); //  ReLU Function
}

vector<double> softmax(vector<double> &input, size_t size)
{
    assert(0 <= size <= sizeof(input) / sizeof(double));
    double m, sum, constant;
    m = -INFINITY;
    for (int i = 0; i < size; ++i)
    {
        if (m < input[i])
        {
            m = input[i];
        }
    }

    sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum += exp(input[i] - m);
    }

    constant = m + log(sum);
    for (int i = 0; i < size; ++i)
    {
        input[i] = exp(input[i] - constant);
    }
    return input;
}

vector<double> cross_entropy_loss(vector<double> &input, vector<int> &g_truth)
{
    vector<double> sum_val;
    for (int i = 0; i < input.size(); i++)
    {
        sum_val.push_back(-(g_truth[i] * log2(input[i])));
        // cout<<g_truth[i]<<"\t"<<input[i] <<"\t"<< sum_val<<endl;
    }
    // cout<<endl;
    return sum_val;
}

int main()
{
    srand((unsigned)time(NULL));
    vector<string> data;
    string str_1;
    vector<string> vec;
    vector<int> temp;
    vector<double> temp_1;
    vector<double> lum;
    vector<double> rad;
    vector<double> mag;
    vector<int> type_st;

    vector<int> temp_test;
    vector<double> temp_1_test;
    vector<double> lum_test;
    vector<double> rad_test;
    vector<double> mag_test;
    vector<int> type_st_test;

    data = read();
    // cout<<data.size()<<endl;

    // erase the first row of the data
    data.erase(data.begin());
    // cout<<data.size()<<endl;

    // for debugging
    /*for ( int i = 0 ;i<data.size(); i++){
        cout<<data[i]<<endl;
    }

    /*Shuffle data for training*/
    random_shuffle(data.begin(), data.end());

    /*Taking half of the data for training*/
    vector<string> test_data = {data.begin() + data.size() / 2, data.end()};
    data.resize(data.size() - data.size() / 2);

    // cout<<data.size()<<endl;
    // cout<<test_data.size()<<endl;

    //  for debugging
    /*for ( int i = 0 ;i<data.size(); i++){
        cout<<data[i]<<endl;
    }*/

    /*For training data*/
    for (int k = 0; k < data.size(); k++)
    {
        stringstream sstr(data[k]);
        while (sstr.good())
        {
            getline(sstr, str_1, ',');
            vec.push_back(str_1);
        }
        for (size_t j = 0; j < vec.size(); j++)
        {
            if (j == 0)
            {
                temp.push_back(stoi(vec[j]));
            }
            else if (j == 1)
            {
                lum.push_back(stold(vec[j]));
            }
            else if (j == 2)
            {
                rad.push_back(stod(vec[j]));
            }
            else if (j == 3)
            {
                mag.push_back(stod(vec[j]));
            }
            else if (j == 4)
            {
                type_st.push_back(stoi(vec[j]));
            }
            else
                break;
        }
        vec.clear();
    }

    /*For test data*/
    vec.clear();

    for (int k = 0; k < test_data.size(); k++)
    {
        stringstream sstr(test_data[k]);
        while (sstr.good())
        {
            getline(sstr, str_1, ',');
            vec.push_back(str_1);
        }
        for (size_t j = 0; j < vec.size(); j++)
        {
            if (j == 0)
            {
                temp_test.push_back(stoi(vec[j]));
            }
            else if (j == 1)
            {
                lum_test.push_back(stold(vec[j]));
            }
            else if (j == 2)
            {
                rad_test.push_back(stod(vec[j]));
            }
            else if (j == 3)
            {
                mag_test.push_back(stod(vec[j]));
            }
            else if (j == 4)
            {
                type_st_test.push_back(stoi(vec[j]));
            }
            else
                break;
        }
        vec.clear();
    }

    /* for(int m=0;m<type_st_test.size();m++){
         cout<<type_st_test[m] << endl;
     }*/

    /*Normalization of training data*/
    temp_1 = normalization(temp);
    lum = normalization(lum);
    rad = normalization(rad);
    mag = normalization(mag);

    /*Normalization of test data*/
    temp_1_test = normalization(temp_test);
    lum_test = normalization(lum_test);
    rad_test = normalization(rad_test);
    mag_test = normalization(mag_test);

    /*Printing the normalized input data*/
    /* for (int m = 0; m < temp.size(); m++)
     {
         cout << temp_1[m] <<" "<<lum[m]<<" " <<rad[m]<<" "<<mag[m]<<endl;
     }
    */

    /*One hot encoding for training data*/
    vector<int> one_hot(6, 0);
    vector<int> one_hot_test(6, 0);
    vector<vector<int>> one_hot_final(type_st.size(), one_hot);
    for (int i = 0; i < type_st.size(); i++)
    {
        for (int j = 0; j < one_hot.size(); j++)
        {
            one_hot[type_st[i]] = 1;
            one_hot_final[i][j] = one_hot[j];
        }
        one_hot[type_st[i]] = 0;
    }

    /*One hot encoding for test data*/
    fill(one_hot.begin(), one_hot.end(), 0);
    vector<vector<int>> one_hot_final_test(type_st_test.size(), one_hot);
    for (int i = 0; i < type_st_test.size(); i++)
    {
        for (int j = 0; j < one_hot.size(); j++)
        {
            one_hot[type_st_test[i]] = 1;
            one_hot_final_test[i][j] = one_hot[j];
        }
        one_hot[type_st_test[i]] = 0;
    }

    /*print the output of one-hot encoding*/
    /*for(int i =0;i<type_st_test.size();i++){
        for(int j =0;j<6;j++){
            cout<<one_hot_final_test[i][j];
        }
        cout<<endl;
    }*/

    /*Starting training*/
    double n = 0.1;
    int epochs = 1000;
    vector<vector<double>> random_initial_w(5, vector<double>(6, 0));
    vector<vector<double>> input_data(temp_1.size(), vector<double>(5, 0));
    vector<vector<double>> input_data_test(temp_1_test.size(), vector<double>(5, 0));
    ofstream myfile;
    ofstream myfile_1;
    myfile.open("mean_val_of_error");
    myfile_1.open("mean_value_of__error_test_data");

    /*Preparation of training input data*/
    for (int i = 0; i < temp_1.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 0)
            {
                input_data[i][j] = 1.0;
            }
            else if (j == 1)
            {
                input_data[i][j] = temp_1[i];
            }
            else if (j == 2)
            {
                input_data[i][j] = lum[i];
            }
            else if (j == 3)
            {
                input_data[i][j] = rad[i];
            }
            else
            {
                input_data[i][j] = mag[i];
            }
        }
    }

    /*Preparation of test data input*/
    for (int i = 0; i < temp_1_test.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j == 0)
            {
                input_data_test[i][j] = 1.0;
            }
            else if (j == 1)
            {
                input_data_test[i][j] = temp_1_test[i];
            }
            else if (j == 2)
            {
                input_data_test[i][j] = lum_test[i];
            }
            else if (j == 3)
            {
                input_data_test[i][j] = rad_test[i];
            }
            else
            {
                input_data_test[i][j] = mag_test[i];
            }
        }
    }

    // Printing the training data matrix
    /*for (int i = 0; i < temp_1.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << input_data[i][j];
            cout << "\t";
        }
        cout << endl;
    }*/

    /*Generating random weights*/
    random_initial_w = random_num_generator(6, 5);
    for (int k = 0; k < 6; k++)
    {
        for (int m = 0; m < 5; m++)
        {
            // cout<<random_initial_w[k][m]<<"\t";
        }
        // cout<<endl;
    }

    vector<double> u_val;
    vector<double> input_new(5, 0);
    vector<double> input_new_test(5, 0);
    double output_0 = 0, error_mean_val = 0, success = 0, num_0 = 0, error_mean_val_test = 0;
    vector<double> final_output;
    vector<double> final_output_test;
    vector<double> error_vec;
    vector<double> error_vec_test;
    vector<double> error(5, 0);
    double sum = 0, value = 0;
    double rand_num_w;

    vector<int> class_0_GT(6, 0);
    class_0_GT[0] = 1;
    vector<int> class_1_GT(6, 0);
    class_1_GT[1] = 1;
    vector<int> class_2_GT(6, 0);
    class_2_GT[2] = 1;
    vector<int> class_3_GT(6, 0);
    class_3_GT[3] = 1;
    vector<int> class_4_GT(6, 0);
    class_4_GT[4] = 1;
    vector<int> class_5_GT(6, 0);
    class_5_GT[5] = 1;
    int num_00 = 0, num_01 = 0, num_02 = 0, num_03 = 0, num_04 = 0, num_05 = 0;
    int num_10 = 0, num_11 = 0, num_12 = 0, num_13 = 0, num_14 = 0, num_15 = 0;
    int num_20 = 0, num_21 = 0, num_22 = 0, num_23 = 0, num_24 = 0, num_25 = 0;
    int num_30 = 0, num_31 = 0, num_32 = 0, num_33 = 0, num_34 = 0, num_35 = 0;
    int num_40 = 0, num_41 = 0, num_42 = 0, num_43 = 0, num_44 = 0, num_45 = 0;
    int num_50 = 0, num_51 = 0, num_52 = 0, num_53 = 0, num_54 = 0, num_55 = 0;
    vector<int> intfinal_output(6, 0);
    vector<int> intone_hot(6, 0);

    for (int i = 0; i < epochs; i++)
    {
        for (int row = 0; row < temp_1.size(); row++)
        {
            for (int col = 0; col < 5; col++)
            {
                input_new[col] = (input_data[row][col]);
                // cout<<input_new[col]<<"\t";
            }
            // cout<<endl;

            for (int counter_1 = 0; counter_1 < 6; counter_1++)
            {
                for (int counter_2 = 0; counter_2 < 5; counter_2++)
                {
                    sum += random_initial_w[counter_1][counter_2] * input_new[counter_2];
                }
                u_val.push_back(sum);
                // cout<<sum<<endl;
                sum = 0;
            }

            /*activation function and final output*/
            for (int counter = 0; counter < 6; counter++)
            {
                output_0 = activation_func(u_val[counter]);
                final_output.push_back(output_0);
                // cout<<output_0<<endl;
            }

            final_output = softmax(final_output, 6);

            // print softmax
            /* for(int counter=0;counter<6;counter++){
                 cout<<final_output[counter]<<endl;
             }
            */

            // Calculation of cross-entropy-loss
            for (int counter = 0; counter < 6; counter++)
            {
                one_hot[counter] = one_hot_final[row][counter];
            }
            error = cross_entropy_loss(final_output, one_hot);
            // cout << error << endl;
            for (int counter = 0; counter < 6; counter++)
            {
                value += error[counter];
            }
            error_vec.push_back(value);

            u_val.clear();
            value = 0;
            error.clear();
            sum = 0;

            /*test data*/
            for (int col = 0; col < 5; col++)
            {
                input_new_test[col] = (input_data_test[row][col]);
                // cout<<input_new_test[col]<<"\t";
            }
            // cout<<endl;

            for (int counter_1 = 0; counter_1 < 6; counter_1++)
            {
                for (int counter_2 = 0; counter_2 < 5; counter_2++)
                {
                    sum += random_initial_w[counter_1][counter_2] * input_new_test[counter_2];
                }
                u_val.push_back(sum);
                // cout<<sum<<endl;
                sum = 0;
            }
            /*activation function and final output*/
            for (int counter = 0; counter < 6; counter++)
            {
                output_0 = activation_func(u_val[counter]);
                final_output_test.push_back(output_0);
                // cout<<output_0<<endl;
            }

            final_output_test = softmax(final_output_test, 6);

            // Calculation of cross-entropy-loss
            for (int counter = 0; counter < 6; counter++)
            {
                one_hot_test[counter] = one_hot_final_test[row][counter];
            }
            error = cross_entropy_loss(final_output_test, one_hot_test);
            // cout << error << endl;
            for (int counter = 0; counter < 6; counter++)
            {
                value += error[counter];
            }
            error_vec_test.push_back(value);
            /*update weights*/
            for (int counter_1 = 0; counter_1 < 6; counter_1++)
            {
                for (int counter_2 = 0; counter_2 < 5; counter_2++)
                {
                    random_initial_w[counter_1][counter_2] = random_initial_w[counter_1][counter_2] - n * (final_output[counter_1] - one_hot[counter_1]) * input_new[counter_2];
                    // cout<<random_initial_w[counter_1][counter_2]<<"\t";
                }
                // cout<<endl;
            }

            if (i == epochs - 1)
            {
                int maxElementIndex = std::max_element(final_output.begin(), final_output.end()) - final_output.begin();
                for (int counter = 0; counter < 6; counter++)
                {
                    if (counter == maxElementIndex)
                    {
                        final_output[counter] = 1;
                    }
                    else
                    {
                        final_output[counter] = 0;
                    }
                }
                for (int counter = 0; counter < 6; counter++)
                {
                    intfinal_output[counter] = final_output[counter];
                }

                for (int counter = 0; counter < 6; counter++)
                {
                    intone_hot[counter] = one_hot[counter];
                }

                if (intone_hot == intfinal_output)
                {
                    success += 1;
                }
                if ((intone_hot == class_0_GT) && (intfinal_output == class_0_GT))
                {
                    num_00 += 1;
                }
                else if ((intone_hot == class_0_GT) && (intfinal_output == class_1_GT))
                {
                    num_01 += 1;
                }
                else if ((intone_hot == class_0_GT) && (intfinal_output == class_2_GT))
                {
                    num_02 += 1;
                }
                else if ((intone_hot == class_0_GT) && (intfinal_output == class_3_GT))
                {
                    num_03 += 1;
                }
                else if ((intone_hot == class_0_GT) && (intfinal_output == class_4_GT))
                {
                    num_04 += 1;
                }
                else if ((intone_hot == class_0_GT) && (intfinal_output == class_5_GT))
                {
                    num_05 += 1;
                }
                else if ((intone_hot == class_1_GT) && (intfinal_output == class_0_GT))
                {
                    num_10 += 1;
                }
                else if ((intone_hot == class_1_GT) && (intfinal_output == class_1_GT))
                {
                    num_11 += 1;
                }
                else if ((intone_hot == class_1_GT) && (intfinal_output == class_2_GT))
                {
                    num_12 += 1;
                }
                else if (((intone_hot == class_1_GT)) && ((intfinal_output == class_3_GT)))
                {
                    num_13 += 1;
                }
                else if ((intone_hot == class_1_GT) && (intfinal_output == class_4_GT))
                {
                    num_14 += 1;
                }
                else if ((intone_hot == class_1_GT) && (intfinal_output == class_5_GT))
                {
                    num_15 += 1;
                }
                else if ((intone_hot == class_2_GT) && (intfinal_output == class_0_GT))
                {
                    num_20 += 1;
                }
                else if ((intone_hot == class_2_GT) && (intfinal_output == class_1_GT))
                {
                    num_21 += 1;
                }
                else if ((intone_hot == class_2_GT) && (intfinal_output == class_2_GT))
                {
                    num_22 += 1;
                }
                else if ((intone_hot == class_2_GT) && (intfinal_output == class_3_GT))
                {
                    num_23 += 1;
                }
                else if ((intone_hot == class_2_GT) && (intfinal_output == class_4_GT))
                {
                    num_24 += 1;
                }
                else if ((intone_hot == class_2_GT) && (intfinal_output == class_5_GT))
                {
                    num_25 += 1;
                }
                else if ((intone_hot == class_3_GT) && (intfinal_output == class_0_GT))
                {
                    num_30 += 1;
                }
                else if ((intone_hot == class_3_GT) && (intfinal_output == class_1_GT))
                {
                    num_31 += 1;
                }
                else if ((intone_hot == class_3_GT) && (intfinal_output == class_2_GT))
                {
                    num_32 += 1;
                }
                else if ((intone_hot == class_3_GT) && (intfinal_output == class_3_GT))
                {
                    num_33 += 1;
                }
                else if ((intone_hot == class_3_GT) && (intfinal_output == class_4_GT))
                {
                    num_34 += 1;
                }
                else if ((intone_hot == class_3_GT) && (intfinal_output == class_5_GT))
                {
                    num_35 += 1;
                }
                else if ((intone_hot == class_4_GT) && (intfinal_output == class_0_GT))
                {
                    num_40 += 1;
                }
                else if ((intone_hot == class_4_GT) && (intfinal_output == class_1_GT))
                {
                    num_41 += 1;
                }
                else if ((intone_hot == class_4_GT) && (intfinal_output == class_2_GT))
                {
                    num_42 += 1;
                }
                else if ((intone_hot == class_4_GT) && (intfinal_output == class_3_GT))
                {
                    num_43 += 1;
                }
                else if ((intone_hot == class_4_GT) && (intfinal_output == class_4_GT))
                {
                    num_44 += 1;
                }
                else if ((intone_hot == class_4_GT) && (intfinal_output == class_5_GT))
                {
                    num_45 += 1;
                }
                else if ((intone_hot == class_5_GT) && (intfinal_output == class_0_GT))
                {
                    num_50 += 1;
                }
                else if ((intone_hot == class_5_GT) && (intfinal_output == class_1_GT))
                {
                    num_51 += 1;
                }
                else if ((intone_hot == class_5_GT) && (intfinal_output == class_2_GT))
                {
                    num_52 += 1;
                }
                else if ((intone_hot == class_5_GT) && (intfinal_output == class_3_GT))
                {
                    num_53 += 1;
                }
                else if ((intone_hot == class_5_GT) && (intfinal_output == class_4_GT))
                {
                    num_54 += 1;
                }
                else if ((intone_hot == class_5_GT) && (intfinal_output == class_5_GT))
                {
                    num_55 += 1;
                }
                //}
            }

            // cout << endl;
            one_hot.clear();
            one_hot_test.clear();
            input_new_test.clear();
            input_new.clear();
            u_val.clear();
            final_output.clear();
            value = 0;
            error.clear();
            final_output_test.clear();
        }
        error_mean_val = accumulate(error_vec.begin(), error_vec.end(), 0.0);
        error_mean_val = error_mean_val / type_st.size();
        // cout << error_mean_val << endl;
        myfile << error_mean_val << endl;

        error_mean_val_test = accumulate(error_vec_test.begin(), error_vec_test.end(), 0.0);
        error_mean_val_test = error_mean_val_test / type_st_test.size();
        // cout << error_mean_val << endl;
        myfile_1 << error_mean_val_test << endl;
        error_vec_test.clear();
        error_vec.clear();
        error_mean_val = 0;
        error_mean_val_test = 0;
    }
    cout << "Success at training data :" << success << "/120" << endl;
    cout << "Confusion Matrix" << endl;
    cout << num_00 << "\t" << num_01 << "\t" << num_02 << "\t" << num_03 << "\t" << num_04 << "\t" << num_05 << endl;
    cout << num_10 << "\t" << num_11 << "\t" << num_12 << "\t" << num_13 << "\t" << num_14 << "\t" << num_15 << endl;
    cout << num_20 << "\t" << num_21 << "\t" << num_22 << "\t" << num_23 << "\t" << num_24 << "\t" << num_25 << endl;
    cout << num_30 << "\t" << num_31 << "\t" << num_32 << "\t" << num_33 << "\t" << num_34 << "\t" << num_35 << endl;
    cout << num_40 << "\t" << num_41 << "\t" << num_42 << "\t" << num_43 << "\t" << num_44 << "\t" << num_45 << endl;
    cout << num_50 << "\t" << num_51 << "\t" << num_52 << "\t" << num_53 << "\t" << num_54 << "\t" << num_55 << endl;

    /*Test data*/
    fill(one_hot.begin(), one_hot.end(), 0.0);
    fill(u_val.begin(), u_val.end(), 0.0);
    fill(final_output.begin(), final_output.end(), 0.0);
    double sum_1 = 0, output_1 = 0;
    int num_1 = 0;
    int success_test = 0;
    fill(input_new.begin(), input_new.end(), 0.0);
    num_00 = 0, num_01 = 0, num_02 = 0, num_03 = 0, num_04 = 0, num_05 = 0;
    num_10 = 0, num_11 = 0, num_12 = 0, num_13 = 0, num_14 = 0, num_15 = 0;
    num_20 = 0, num_21 = 0, num_22 = 0, num_23 = 0, num_24 = 0, num_25 = 0;
    num_30 = 0, num_31 = 0, num_32 = 0, num_33 = 0, num_34 = 0, num_35 = 0;
    num_40 = 0, num_41 = 0, num_42 = 0, num_43 = 0, num_44 = 0, num_45 = 0;
    num_50 = 0, num_51 = 0, num_52 = 0, num_53 = 0, num_54 = 0, num_55 = 0;

    for (int i = 0; i < temp_1_test.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            input_new[j] = (input_data_test[i][j]);
        }

        for (int counter_1 = 0; counter_1 < 6; counter_1++)
        {
            for (int counter_2 = 0; counter_2 < 5; counter_2++)
            {
                sum_1 += random_initial_w[counter_1][counter_2] * input_new[counter_2];
            }
            u_val.push_back(sum_1);
            sum_1 = 0;
        }
        /*activation function and final output*/
        for (int counter = 0; counter < 6; counter++)
        {
            output_1 = activation_func(u_val[counter]);
            final_output.push_back(output_1);
            // cout<<output_0<<endl;
        }
        final_output = softmax(final_output, 6);

        int maxElementIndex_test = std::max_element(final_output.begin(), final_output.end()) - final_output.begin();

        for (int counter = 0; counter < 6; counter++)
        {
            one_hot[counter] = one_hot_final_test[i][counter];
            if (counter == maxElementIndex_test)
            {
                final_output[counter] = 1;
            }
            else
            {
                final_output[counter] = 0;
            }
        }

        for (int counter = 0; counter < 6; counter++)
        {
            intfinal_output[counter] = final_output[counter];
        }

        for (int counter = 0; counter < 6; counter++)
        {
            intone_hot[counter] = one_hot[counter];
        }
        if (intfinal_output == intone_hot)
        {
            success_test += 1;
        }

        if ((intone_hot == class_0_GT) && (intfinal_output == class_0_GT))
        {
            num_00 += 1;
        }
        else if ((intone_hot == class_0_GT) && (intfinal_output == class_1_GT))
        {
            num_01 += 1;
        }
        else if ((intone_hot == class_0_GT) && (intfinal_output == class_2_GT))
        {
            num_02 += 1;
        }
        else if ((intone_hot == class_0_GT) && (intfinal_output == class_3_GT))
        {
            num_03 += 1;
        }
        else if ((intone_hot == class_0_GT) && (intfinal_output == class_4_GT))
        {
            num_04 += 1;
        }
        else if ((intone_hot == class_0_GT) && (intfinal_output == class_5_GT))
        {
            num_05 += 1;
        }
        else if ((intone_hot == class_1_GT) && (intfinal_output == class_0_GT))
        {
            num_10 += 1;
        }
        else if ((intone_hot == class_1_GT) && (intfinal_output == class_1_GT))
        {
            num_11 += 1;
        }
        else if ((intone_hot == class_1_GT) && (intfinal_output == class_2_GT))
        {
            num_12 += 1;
        }
        else if (((intone_hot == class_1_GT)) && ((intfinal_output == class_3_GT)))
        {
            num_13 += 1;
        }
        else if ((intone_hot == class_1_GT) && (intfinal_output == class_4_GT))
        {
            num_14 += 1;
        }
        else if ((intone_hot == class_1_GT) && (intfinal_output == class_5_GT))
        {
            num_15 += 1;
        }
        else if ((intone_hot == class_2_GT) && (intfinal_output == class_0_GT))
        {
            num_20 += 1;
        }
        else if ((intone_hot == class_2_GT) && (intfinal_output == class_1_GT))
        {
            num_21 += 1;
        }
        else if ((intone_hot == class_2_GT) && (intfinal_output == class_2_GT))
        {
            num_22 += 1;
        }
        else if ((intone_hot == class_2_GT) && (intfinal_output == class_3_GT))
        {
            num_23 += 1;
        }
        else if ((intone_hot == class_2_GT) && (intfinal_output == class_4_GT))
        {
            num_24 += 1;
        }
        else if ((intone_hot == class_2_GT) && (intfinal_output == class_5_GT))
        {
            num_25 += 1;
        }
        else if ((intone_hot == class_3_GT) && (intfinal_output == class_0_GT))
        {
            num_30 += 1;
        }
        else if ((intone_hot == class_3_GT) && (intfinal_output == class_1_GT))
        {
            num_31 += 1;
        }
        else if ((intone_hot == class_3_GT) && (intfinal_output == class_2_GT))
        {
            num_32 += 1;
        }
        else if ((intone_hot == class_3_GT) && (intfinal_output == class_3_GT))
        {
            num_33 += 1;
        }
        else if ((intone_hot == class_3_GT) && (intfinal_output == class_4_GT))
        {
            num_34 += 1;
        }
        else if ((intone_hot == class_3_GT) && (intfinal_output == class_5_GT))
        {
            num_35 += 1;
        }
        else if ((intone_hot == class_4_GT) && (intfinal_output == class_0_GT))
        {
            num_40 += 1;
        }
        else if ((intone_hot == class_4_GT) && (intfinal_output == class_1_GT))
        {
            num_41 += 1;
        }
        else if ((intone_hot == class_4_GT) && (intfinal_output == class_2_GT))
        {
            num_42 += 1;
        }
        else if ((intone_hot == class_4_GT) && (intfinal_output == class_3_GT))
        {
            num_43 += 1;
        }
        else if ((intone_hot == class_4_GT) && (intfinal_output == class_4_GT))
        {
            num_44 += 1;
        }
        else if ((intone_hot == class_4_GT) && (intfinal_output == class_5_GT))
        {
            num_45 += 1;
        }
        else if ((intone_hot == class_5_GT) && (intfinal_output == class_0_GT))
        {
            num_50 += 1;
        }
        else if ((intone_hot == class_5_GT) && (intfinal_output == class_1_GT))
        {
            num_51 += 1;
        }
        else if ((intone_hot == class_5_GT) && (intfinal_output == class_2_GT))
        {
            num_52 += 1;
        }
        else if ((intone_hot == class_5_GT) && (intfinal_output == class_3_GT))
        {
            num_53 += 1;
        }
        else if ((intone_hot == class_5_GT) && (intfinal_output == class_4_GT))
        {
            num_54 += 1;
        }
        else if ((intone_hot == class_5_GT) && (intfinal_output == class_5_GT))
        {
            num_55 += 1;
        }

        one_hot.clear();
        input_new.clear();
        u_val.clear();
        final_output.clear();
    }
    cout<<endl;
    cout << "Success at test data :" << success_test << "/120" << endl;
    cout<<"Confusion matrix"<<endl;
    cout << num_00 << "\t" << num_01 << "\t" << num_02 << "\t" << num_03 << "\t" << num_04 << "\t" << num_05 << endl;
    cout << num_10 << "\t" << num_11 << "\t" << num_12 << "\t" << num_13 << "\t" << num_14 << "\t" << num_15 << endl;
    cout << num_20 << "\t" << num_21 << "\t" << num_22 << "\t" << num_23 << "\t" << num_24 << "\t" << num_25 << endl;
    cout << num_30 << "\t" << num_31 << "\t" << num_32 << "\t" << num_33 << "\t" << num_34 << "\t" << num_35 << endl;
    cout << num_40 << "\t" << num_41 << "\t" << num_42 << "\t" << num_43 << "\t" << num_44 << "\t" << num_45 << endl;
    cout << num_50 << "\t" << num_51 << "\t" << num_52 << "\t" << num_53 << "\t" << num_54 << "\t" << num_55 << endl;
    myfile.close();
    myfile_1.close();

    return 0;
}
