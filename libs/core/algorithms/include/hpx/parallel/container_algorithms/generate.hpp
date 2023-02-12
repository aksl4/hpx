//  Copyright (c) 2014 Grant Mercer
//  Copyright (c) 2014-2023 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/// \file parallel/container_algorithms/generate.hpp

#pragma once

#if defined(DOXYGEN)
namespace hpx { namespace ranges {
    // clang-format off

    /// Assign each element in range [first, last) a value generated by the
    /// given function object f
    ///
    /// \note   Complexity: Exactly \a distance(first, last)
    ///                     invocations of \a f and assignments.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam Rng         The type of the source range used (deduced).
    ///                     The iterators extracted from this range type must
    ///                     meet the requirements of an forward iterator.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param rng          Refers to the sequence of elements the algorithm
    ///                     will be applied to.
    /// \param f            generator function that will be called. signature of
    ///                     function should be equivalent to the following:
    ///                     \code
    ///                     Ret fun();
    ///                     \endcode \n
    ///                     The type \a Ret must be such that an object of type
    ///                     \a FwdIter can be dereferenced and assigned a value
    ///                     of type \a Ret.
    ///
    /// The assignments in the parallel \a generate algorithm invoked with an
    /// execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The assignments in the parallel \a generate algorithm invoked with
    /// an execution policy object of type \a parallel_policy or
    /// \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a replace_if algorithm returns a \a hpx::future<FwdIter>
    ///           if the execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy
    ///           and returns \a FwdIter otherwise.
    ///           It returns \a last.
    ///
    template <typename ExPolicy, typename Rng, typename F>
    typename hpx::parallel::util::detail::algorithm_result<ExPolicy,
        typename hpx::traits::range_iterator<Rng>::type>::type
    generate(ExPolicy&& policy, Rng&& rng, F&& f);

    /// Assign each element in range [first, last) a value generated by the
    /// given function object f
    ///
    /// \note   Complexity: Exactly \a distance(first, last)
    ///                     invocations of \a f and assignments.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam Iter        The type of the source begin iterator used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam Sent        The type of the source end iterator used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param f            generator function that will be called. signature of
    ///                     function should be equivalent to the following:
    ///                     \code
    ///                     Ret fun();
    ///                     \endcode \n
    ///                     The type \a Ret must be such that an object of type
    ///                     \a FwdIter can be dereferenced and assigned a value
    ///                     of type \a Ret.
    ///
    /// The assignments in the parallel \a generate algorithm invoked with an
    /// execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The assignments in the parallel \a generate algorithm invoked with
    /// an execution policy object of type \a parallel_policy or
    /// \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a replace_if algorithm returns a \a hpx::future<FwdIter>
    ///           if the execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy
    ///           and returns \a FwdIter otherwise.
    ///           It returns \a last.
    ///
    template <typename ExPolicy, typename Iter, typename Sent, typename F>
    hpx::parallel::util::detail::algorithm_result_t<ExPolicy, Iter>
    generate(ExPolicy&& policy, Iter first, Sent last, F&& f);

    /// Assign each element in range [first, last) a value generated by the
    /// given function object f
    ///
    /// \note   Complexity: Exactly \a distance(first, last)
    ///                     invocations of \a f and assignments.
    ///
    /// \tparam Rng         The type of the source range used (deduced).
    ///                     The iterators extracted from this range type must
    ///                     meet the requirements of an forward iterator.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param rng          Refers to the sequence of elements the algorithm
    ///                     will be applied to.
    /// \param f            generator function that will be called. signature of
    ///                     function should be equivalent to the following:
    ///                     \code
    ///                     Ret fun();
    ///                     \endcode \n
    ///                     The type \a Ret must be such that an object of type
    ///                     \a FwdIter can be dereferenced and assigned a value
    ///                     of type \a Ret.
    ///
    /// \returns  The \a replace_if algorithm returns \a last.
    ///
    template <typename Rng, typename F>
    typename hpx::traits::range_iterator<Rng>::type
    generate(Rng&& rng, F&& f);

    /// Assign each element in range [first, last) a value generated by the
    /// given function object f
    ///
    /// \note   Complexity: Exactly \a distance(first, last)
    ///                     invocations of \a f and assignments.
    ///
    /// \tparam Iter        The type of the source begin iterator used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam Sent        The type of the source end iterator used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param last         Refers to the end of the sequence of elements the
    ///                     algorithm will be applied to.
    /// \param f            generator function that will be called. signature of
    ///                     function should be equivalent to the following:
    ///                     \code
    ///                     Ret fun();
    ///                     \endcode \n
    ///                     The type \a Ret must be such that an object of type
    ///                     \a FwdIter can be dereferenced and assigned a value
    ///                     of type \a Ret.
    ///
    /// \returns  The \a replace_if algorithm returns \a last.
    ///
    template <typename Iter, typename Sent, typename F>
    Iter generate(Iter first, Sent last, F&& f);

    /// Assigns each element in range [first, first+count) a value generated by
    /// the given function object g.
    ///
    /// \note   Complexity: Exactly \a count invocations of \a f and
    ///         assignments, for count > 0.
    ///
    /// \tparam ExPolicy    The type of the execution policy to use (deduced).
    ///                     It describes the manner in which the execution
    ///                     of the algorithm may be parallelized and the manner
    ///                     in which it executes the assignments.
    /// \tparam FwdIter     The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam Size        The type of the argument specifying the number of
    ///                     elements to apply \a f to.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param policy       The execution policy to use for the scheduling of
    ///                     the iterations.
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param count        Refers to the number of elements in the sequence the
    ///                     algorithm will be applied to.
    /// \param f            Refers to the generator function object that will be
    ///                     called. The signature of the function should be
    ///                     equivalent to
    ///                     \code
    ///                     Ret fun();
    ///                     \endcode \n
    ///                     The type \a Ret must be such that an object of type
    ///                     \a OutputIt can be dereferenced and assigned a value
    ///                     of type \a Ret.
    ///
    /// The assignments in the parallel \a generate_n algorithm invoked with an
    /// execution policy object of type \a sequenced_policy
    /// execute in sequential order in the calling thread.
    ///
    /// The assignments in the parallel \a generate_n algorithm invoked with
    /// an execution policy object of type \a parallel_policy or
    /// \a parallel_task_policy are permitted to execute in an unordered
    /// fashion in unspecified threads, and indeterminately sequenced
    /// within each thread.
    ///
    /// \returns  The \a replace_if algorithm returns a \a hpx::future<FwdIter>
    ///           if the execution policy is of type
    ///           \a sequenced_task_policy or
    ///           \a parallel_task_policy
    ///           and returns \a FwdIter otherwise.
    ///           It returns \a last.
    ///
    template <typename ExPolicy, typename FwdIter, typename Size, typename F>
    hpx::parallel::util::detail::algorithm_result_t<ExPolicy, FwdIter>
    generate_n(ExPolicy&& policy, FwdIter first, Size count, F&& f);

    /// Assigns each element in range [first, first+count) a value generated by
    /// the given function object g.
    ///
    /// \note   Complexity: Exactly \a count invocations of \a f and
    ///         assignments, for count > 0.
    ///
    /// \tparam FwdIter     The type of the source iterators used (deduced).
    ///                     This iterator type must meet the requirements of an
    ///                     forward iterator.
    /// \tparam Size        The type of the argument specifying the number of
    ///                     elements to apply \a f to.
    /// \tparam F           The type of the function/function object to use
    ///                     (deduced). Unlike its sequential form, the parallel
    ///                     overload of \a equal requires \a F to meet the
    ///                     requirements of \a CopyConstructible.
    ///
    /// \param first        Refers to the beginning of the sequence of elements
    ///                     the algorithm will be applied to.
    /// \param count        Refers to the number of elements in the sequence the
    ///                     algorithm will be applied to.
    /// \param f            Refers to the generator function object that will be
    ///                     called. The signature of the function should be
    ///                     equivalent to
    ///                     \code
    ///                     Ret fun();
    ///                     \endcode \n
    ///                     The type \a Ret must be such that an object of type
    ///                     \a OutputIt can be dereferenced and assigned a value
    ///                     of type \a Ret.
    ///
    /// \returns  The \a replace_if algorithm returns \a last.
    ///
    template <typename FwdIter, typename Size, typename F>
    FwdIter generate_n(FwdIter first, Size count, F&& f);

    // clang-format on
}}    // namespace hpx::ranges

#else    //DOXYGEN

#include <hpx/config.hpp>
#include <hpx/concepts/concepts.hpp>
#include <hpx/iterator_support/range.hpp>
#include <hpx/iterator_support/traits/is_range.hpp>
#include <hpx/parallel/algorithms/generate.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace hpx::ranges {

    ///////////////////////////////////////////////////////////////////////////
    // CPO for hpx::ranges::generate
    inline constexpr struct generate_t final
      : hpx::detail::tag_parallel_algorithm<generate_t>
    {
    private:
        // clang-format off
        template <typename ExPolicy, typename Rng, typename F,
            HPX_CONCEPT_REQUIRES_(
                hpx::is_execution_policy_v<ExPolicy> &&
                hpx::traits::is_range<Rng>::value
            )>
        // clang-format on
        friend typename hpx::parallel::util::detail::algorithm_result<ExPolicy,
            typename hpx::traits::range_iterator<Rng>::type>::type
        tag_fallback_invoke(generate_t, ExPolicy&& policy, Rng&& rng, F&& f)
        {
            using iterator_type =
                typename hpx::traits::range_iterator<Rng>::type;

            static_assert(hpx::traits::is_forward_iterator_v<iterator_type>,
                "Required at least forward iterator.");

            return hpx::parallel::detail::generate<iterator_type>().call(
                HPX_FORWARD(ExPolicy, policy), hpx::util::begin(rng),
                hpx::util::end(rng), HPX_FORWARD(F, f));
        }

        // clang-format off
        template <typename ExPolicy, typename Iter, typename Sent, typename F,
            HPX_CONCEPT_REQUIRES_(
                hpx::is_execution_policy_v<ExPolicy> &&
                hpx::traits::is_sentinel_for<Sent, Iter>::value
            )>
        // clang-format on
        friend typename hpx::parallel::util::detail::algorithm_result<ExPolicy,
            Iter>::type
        tag_fallback_invoke(
            generate_t, ExPolicy&& policy, Iter first, Sent last, F&& f)
        {
            static_assert(hpx::traits::is_forward_iterator_v<Iter>,
                "Required at least forward iterator.");

            return hpx::parallel::detail::generate<Iter>().call(
                HPX_FORWARD(ExPolicy, policy), first, last, HPX_FORWARD(F, f));
        }

        // clang-format off
        template <typename Rng, typename F,
            HPX_CONCEPT_REQUIRES_(
                hpx::traits::is_range<Rng>::value
            )>
        // clang-format on
        friend typename hpx::traits::range_iterator<Rng>::type
        tag_fallback_invoke(generate_t, Rng&& rng, F&& f)
        {
            using iterator_type =
                typename hpx::traits::range_iterator<Rng>::type;

            static_assert(hpx::traits::is_forward_iterator_v<iterator_type>,
                "Required at least forward iterator.");

            return hpx::parallel::detail::generate<iterator_type>().call(
                hpx::execution::seq, hpx::util::begin(rng), hpx::util::end(rng),
                HPX_FORWARD(F, f));
        }

        // clang-format off
        template <typename Iter, typename Sent, typename F,
            HPX_CONCEPT_REQUIRES_(
                hpx::traits::is_sentinel_for<Sent, Iter>::value
            )>
        // clang-format on
        friend Iter tag_fallback_invoke(
            generate_t, Iter first, Sent last, F&& f)
        {
            static_assert(hpx::traits::is_forward_iterator_v<Iter>,
                "Required at least forward iterator.");

            return hpx::parallel::detail::generate<Iter>().call(
                hpx::execution::seq, first, last, HPX_FORWARD(F, f));
        }
    } generate{};

    ///////////////////////////////////////////////////////////////////////////
    // CPO for hpx::ranges::generate_n
    inline constexpr struct generate_n_t final
      : hpx::detail::tag_parallel_algorithm<generate_n_t>
    {
    private:
        // clang-format off
        template <typename ExPolicy, typename FwdIter, typename Size, typename F,
            HPX_CONCEPT_REQUIRES_(
                hpx::is_execution_policy_v<ExPolicy> &&
                hpx::traits::is_iterator_v<FwdIter>
            )>
        // clang-format on
        friend typename hpx::parallel::util::detail::algorithm_result<ExPolicy,
            FwdIter>::type
        tag_fallback_invoke(
            generate_n_t, ExPolicy&& policy, FwdIter first, Size count, F&& f)
        {
            static_assert(hpx::traits::is_forward_iterator_v<FwdIter>,
                "Required at least forward iterator.");

            if (hpx::parallel::detail::is_negative(count))
            {
                return hpx::parallel::util::detail::algorithm_result<ExPolicy,
                    FwdIter>::get(HPX_MOVE(first));
            }

            return hpx::parallel::detail::generate_n<FwdIter>().call(
                HPX_FORWARD(ExPolicy, policy), first,
                static_cast<std::size_t>(count), HPX_FORWARD(F, f));
        }

        // clang-format off
        template <typename FwdIter, typename Size, typename F,
            HPX_CONCEPT_REQUIRES_(
                hpx::traits::is_iterator_v<FwdIter>
            )>
        // clang-format on
        friend FwdIter tag_fallback_invoke(
            generate_n_t, FwdIter first, Size count, F&& f)
        {
            static_assert(hpx::traits::is_forward_iterator_v<FwdIter>,
                "Required at least forward iterator.");

            if (hpx::parallel::detail::is_negative(count))
            {
                return first;
            }

            return hpx::parallel::detail::generate_n<FwdIter>().call(
                hpx::execution::seq, first, static_cast<std::size_t>(count),
                HPX_FORWARD(F, f));
        }
    } generate_n{};
}    // namespace hpx::ranges

#endif    // DOXYGEN
