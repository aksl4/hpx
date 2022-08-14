//  Copyright (c) 2016-2022 Hartmut Kaiser
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/local/algorithm.hpp>
#include <hpx/local/init.hpp>
#include <hpx/modules/testing.hpp>

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "test_utils.hpp"

///////////////////////////////////////////////////////////////////////////////
unsigned int seed = std::random_device{}();
std::mt19937 gen(seed);

template <typename Policy, typename ExPolicy, typename IteratorTag>
void test_for_loop_sender_direct(Policy l, ExPolicy&& policy, IteratorTag)
{
    static_assert(hpx::is_execution_policy<ExPolicy>::value,
        "hpx::is_execution_policy<ExPolicy>::value");

    typedef std::vector<std::size_t>::iterator base_iterator;
    typedef test::test_iterator<base_iterator, IteratorTag> iterator;

    std::vector<std::size_t> c(10007);
    std::iota(std::begin(c), std::end(c), gen());

    namespace ex = hpx::execution::experimental;
    namespace tt = hpx::this_thread::experimental;

    using scheduler_t = ex::thread_pool_policy_scheduler<Policy>;

    auto exec = ex::explicit_scheduler_executor(scheduler_t(l));
    hpx::experimental::for_loop(policy.on(exec), iterator(std::begin(c)),
        iterator(std::end(c)), [](iterator it) { *it = 42; }) |
        tt::sync_wait();

    // verify values
    std::size_t count = 0;
    std::for_each(std::begin(c), std::end(c), [&count](std::size_t v) -> void {
        HPX_TEST_EQ(v, std::size_t(42));
        ++count;
    });
    HPX_TEST_EQ(count, c.size());
}

template <typename IteratorTag>
void test_for_loop()
{
    using namespace hpx::execution;

    test_for_loop_sender_direct(hpx::launch::sync, seq, IteratorTag());
    test_for_loop_sender_direct(hpx::launch::sync, unseq, IteratorTag());
    test_for_loop_sender_direct(hpx::launch::async, par, IteratorTag());
    test_for_loop_sender_direct(hpx::launch::async, par_unseq, IteratorTag());

    test_for_loop_sender_direct(hpx::launch::sync, seq(task), IteratorTag());
    test_for_loop_sender_direct(hpx::launch::sync, unseq(task), IteratorTag());
    test_for_loop_sender_direct(hpx::launch::async, par(task), IteratorTag());
    test_for_loop_sender_direct(
        hpx::launch::async, par_unseq(task), IteratorTag());
}

void for_loop_test()
{
    test_for_loop<std::random_access_iterator_tag>();
    test_for_loop<std::forward_iterator_tag>();
}

///////////////////////////////////////////////////////////////////////////////
//template <typename ExPolicy>
//void test_for_loop_idx(ExPolicy&& policy)
//{
//    static_assert(hpx::is_execution_policy<ExPolicy>::value,
//        "hpx::is_execution_policy<ExPolicy>::value");
//
//    std::vector<std::size_t> c(10007);
//    std::iota(std::begin(c), std::end(c), gen());
//
//    hpx::experimental::for_loop(std::forward<ExPolicy>(policy), 0, c.size(),
//        [&c](std::size_t i) { c[i] = 42; });
//
//    // verify values
//    std::size_t count = 0;
//    std::for_each(std::begin(c), std::end(c), [&count](std::size_t v) -> void {
//        HPX_TEST_EQ(v, std::size_t(42));
//        ++count;
//    });
//    HPX_TEST_EQ(count, c.size());
//}

//void for_loop_test_idx()
//{
//    using namespace hpx::execution;
//
//    test_for_loop_idx(seq);
//    test_for_loop_idx(par);
//    test_for_loop_idx(par_unseq);
//}

///////////////////////////////////////////////////////////////////////////////
int hpx_main(hpx::program_options::variables_map& vm)
{
    if (vm.count("seed"))
        seed = vm["seed"].as<unsigned int>();

    std::cout << "using seed: " << seed << std::endl;
    gen.seed(seed);

    for_loop_test();
    //for_loop_test_idx();

    return hpx::local::finalize();
}

int main(int argc, char* argv[])
{
    // add command line option which controls the random number generator seed
    using namespace hpx::program_options;
    options_description desc_commandline(
        "Usage: " HPX_APPLICATION_STRING " [options]");

    desc_commandline.add_options()("seed,s", value<unsigned int>(),
        "the random number generator seed to use for this run");

    // By default this test should run on all available cores
    std::vector<std::string> const cfg = {"hpx.os_threads=all"};

    // Initialize and run HPX
    hpx::local::init_params init_args;
    init_args.desc_cmdline = desc_commandline;
    init_args.cfg = cfg;

    HPX_TEST_EQ_MSG(hpx::local::init(hpx_main, argc, argv, init_args), 0,
        "HPX main exited with non-zero status");

    return hpx::util::report_errors();
}
