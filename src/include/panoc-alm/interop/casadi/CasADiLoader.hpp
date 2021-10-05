#pragma once

#include <panoc-alm/util/problem.hpp>

namespace pa {

/// @addtogroup grp_ExternalProblemLoaders
/// @{

/// Load an objective function generated by CasADi.
std::function<pa::Problem::f_sig>
load_CasADi_objective(const char *so_name, const char *fun_name = "f");
/// Load the gradient of an objective function generated by CasADi.
std::function<pa::Problem::grad_f_sig>
load_CasADi_gradient_objective(const char *so_name,
                               const char *fun_name = "grad_f");
/// Load a constraint function generated by CasADi.
std::function<pa::Problem::g_sig>
load_CasADi_constraints(const char *so_name, const char *fun_name = "g");
/// Load the gradient-vector product of a constraint function generated by
/// CasADi.
std::function<pa::Problem::grad_g_prod_sig>
load_CasADi_gradient_constraints_prod(const char *so_name,
                                      const char *fun_name = "grad_g");
/// Load the Hessian of a Lagrangian function generated by CasADi.
std::function<pa::Problem::hess_L_sig>
load_CasADi_hessian_lagrangian(const char *so_name,
                               const char *fun_name = "hess_L");
/// Load the Hessian-vector product of a Lagrangian function generated by
/// CasADi.
std::function<pa::Problem::hess_L_prod_sig>
load_CasADi_hessian_lagrangian_prod(const char *so_name,
                                    const char *fun_name = "hess_L_prod");

/// Load a problem generated by CasADi (without parameters).
///
/// @param  filename
///         Filename of the shared library to load the functions from.
/// @param  n
///         Number of decision variables (@f$ x \in \mathbb{R}^n @f$).
/// @param  m
///         Number of general constraints (@f$ g(x) \in \mathbb{R}^m @f$).
/// @param  second_order
///         Load the additional functions required for second-order PANOC.
///
/// The file should contain functions with the names `f`, `grad_f`, `g` and
/// `grad_g`. These functions evaluate the objective function, its gradient,
/// the constraints, and the constraint gradient times a vector respecitvely.
/// If @p second_order is true, additional functions `hess_L` and
/// `hess_L_prod` should be provided to evaluate the Hessian of the Lagrangian
/// and Hessian-vector products.
pa::Problem load_CasADi_problem(const char *filename, unsigned n, unsigned m,
                                bool second_order = false);
/// Load a problem generated by CasADi (with parameters).
///
/// @copydetails load_CasADi_problem
ProblemWithParam load_CasADi_problem_with_param(const char *filename,
                                                unsigned n, unsigned m,
                                                bool second_order = false);

/// @}

} // namespace pa