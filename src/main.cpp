#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <memory>

#define MAP_WIDTH 5
#define MAP_HEIGHT 5
#define ITERATIONS 100

template <typename t>
void schoen_print(t text)
{
    std::cout << text << std::endl;
}

template <typename t>
void schoen_error(t text)
{
    std::cout << "\x1b[38;5;9m" << text << std::endl;
}

template <typename t>
void schoen_warn(t text)
{
    std::cout << "\x1b[38;5;228m" << text << std::endl;
}

template <typename Derived>
void zero_matrix(Eigen::MatrixBase<Derived> &matrix)
{
    auto cols = matrix.cols();
    auto rows = matrix.rows();

    for (auto c = 0; c < cols; c++)
    {
        for (auto r = 0; r < rows; r++)
        {
            matrix(r, c) = 0;
        }
    }
}

// template <typename A>
// struct convolution_result
// {
//     EIGEN_MAKE_ALIGNED_OPERATOR_NEW
//     bool valid;
//     Eigen::MatrixBase<A> matrix_ptr;

//     friend std::ostream& operator<<(std::ostream& output, const convolution_result<A> &st)
//     {
//         if (st.valid)
//             output << "st.matrix_ptr";
//         else
//             output << "Invalid Result";

//         return output;
//     }
// };

template <typename A, typename B, typename C>
bool simple_convolution(Eigen::MatrixBase<A> &matrix, Eigen::MatrixBase<B> &kernel, Eigen::MatrixBase<C> &ret_matrix)
{
    auto kc = kernel.cols();
    auto kr = kernel.rows();

    // This only accepts square kernels with an uneven size (with center)
    if (kc != kr || kc % 2 != 1)
    {
        schoen_warn("NOT A VALID KERNEL!!");
        return false;
    }
    auto kernel_size = (kc - 1) / 2;

    auto mc = matrix.cols();
    auto mr = matrix.rows();
    zero_matrix(ret_matrix);

    if (mc != ret_matrix.cols() || mr != ret_matrix.rows())
    {
        schoen_warn("NOT A VALID RETURN MATRIX!!");
        return false;
    }

    // Create matrix with padding
    Eigen::MatrixX<double> padded_matrix;
    padded_matrix.resize(mr + 2 * kernel_size, mc + 2 * kernel_size);
    zero_matrix(padded_matrix);
    padded_matrix.block(1, 1, mr, mc) = matrix;

    // schoen_print(padded_matrix);

    for (auto c = 0; c < mc; c++)
    {
        for (auto r = 0; r < mr; r++)
        {
            // Convolution unit
            double result = 0;
            for (auto i = -kernel_size; i <= kernel_size; i++)
            {
                for (auto j = -kernel_size; j <= kernel_size; j++)
                {
                    // std::cout << "Index: " << r+kernel_size+j << " , " << c+kernel_size+i << "\t";
                    // std::cout << "Kernel: " << kernel_size+j << " , " << kc-1-(kernel_size+j) << std::endl;
                    result += padded_matrix(r + kernel_size + j, c + kernel_size + i) * kernel((kernel_size + j), kc - 1 - (kernel_size + i));
                }
            }
            ret_matrix(r, c) = result;
        }
    }

    return true;
}

bool game_rules(int value, bool isAlive)
{
    switch (value)
    {
    case 2:
        return isAlive;
    case 3:
        return true;
    default:
        return false;
    }
}

template <typename A, typename B, typename C>
bool get_new_state(Eigen::MatrixBase<A> &conv_res, Eigen::MatrixBase<B> &old_state, Eigen::MatrixBase<C> &new_state)
{
    if (conv_res.cols() != new_state.cols() || conv_res.cols() != old_state.cols() ||
        conv_res.rows() != new_state.rows() || conv_res.rows() != old_state.rows())
    {
        schoen_warn("NOT VALID MATRICESS");
        return false;
    }

    zero_matrix(new_state);

    auto rows = conv_res.rows();
    auto cols = conv_res.cols();

    for (auto c = 0; c < cols; c++)
    {
        for (auto r = 0; r < rows; r++)
        {
            new_state(r, c) = game_rules(conv_res(r, c), old_state(r, c));
        }
    }
}

template <typename A>
bool do_step(Eigen::MatrixBase<A> &old_state, Eigen::MatrixBase<A> &new_state)
{
    Eigen::Matrix3f kernel;
    kernel << 1, 1, 1,
        1, 0, 1,
        1, 1, 1;

    Eigen::MatrixX<double> res;
    res.resize(old_state.cols(), old_state.rows());

    if (!simple_convolution(old_state, kernel, res))
        return false;

    if (!get_new_state(res, old_state, new_state))
        return false;

    return true;
}

int main()
{
    Eigen::Matrix<double, MAP_WIDTH, MAP_HEIGHT> matrix;

    zero_matrix(matrix);
    matrix.block(0, 2, 4, 1) << 1, 1, 1, 1;

    std::cout << "Matrix initialized: \n"
              << matrix << std::endl;

    Eigen::Matrix3f kernel;
    kernel << 1, 1, 1,
        1, 0, 1,
        1, 1, 1;
    std::cout << "Kernel: \n"
              << kernel << std::endl;

    Eigen::Matrix<double, MAP_WIDTH, MAP_HEIGHT> new_state = matrix.replicate(1, 1);

    for (int i = 0; i < ITERATIONS; i++)
    {
        do_step(matrix, new_state);
        std::cout << "Iter [" << i+1 << "]:\n"
                  << new_state
                  << std::endl;
        matrix = new_state;
    }

    std::cout << std::endl;
    return 1;
}