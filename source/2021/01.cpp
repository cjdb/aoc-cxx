// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0
//
#include <fmt/format.h>
#include <range/v3/algorithm/foldl.hpp>
#include <range/v3/iterator.hpp>
#include <range/v3/range.hpp>
#include <range/v3/view.hpp>
#include <functional>
#include <iostream>
#include <vector>

int main()
{
	namespace rv = ranges::views;
	auto input = ranges::istream_view<int>(std::cin) | ranges::to<std::vector>;

	auto difference = [](auto&& r) { return *ranges::next(r.begin()) - *r.begin(); };
	auto is_positive = [](auto const x) { return x > 0; };
	auto inner_data = input | rv::sliding(3) | rv::transform([](auto&& r) { return ranges::foldl(r, 0, std::plus()); });
	auto outer_data = inner_data | rv::sliding(2) | rv::transform(difference) | rv::filter(is_positive);
	fmt::print("{}\n", ranges::distance(outer_data));
}
