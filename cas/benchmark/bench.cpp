//
// Created by Abd-El-Aziz Zayed on 2022-10-02.
//

#include <benchmark/benchmark.h>
#include <cas/plot/Function.h>

static void BM_FunctionCreation(benchmark::State& state) {
    std::string strFunction = "tan(x)*sin(x)*cos(x)"
                              "*cot(x)*csc(y)*sec(x)"
                              "*arctan(x)*arcsin(x)*arccos(y)"
                              "*arccot(y)*arccsc(x)*arcsec(y*x)"
                              "+(x+1)^(exp(x)+abs(y))+log(x)"
                              "+ln(y)+sqrt(x)+cbrt(x)"
                              "+mod(x,2)+floor(y*x)+ceil(x)"
                              "+round(x)+x/y+sign(x)"
                              "+min(x, y, x+y, x*y, x/y, x^y)"
                              "*max(x, y, x+y, x*y, x/y, x^y)";

    for (auto _: state) {
        cas::Function function = cas::Function(strFunction);
        for (double x = -1.0; x <= 1.0; x += 0.01) {
            for (double y = -1.0; y <= 1.0; y += 0.01) {
                benchmark::DoNotOptimize(function.evaluate({{'x', x}, {'y', y}}));
            }
        }
        for (double x = -100.0; x <= 100.0; x += 1.0) {
            for (double y = -100.0; y <= 100.0; y += 1.0) {
                benchmark::DoNotOptimize(function.evaluate({{'x', x}, {'y', y}}));
            }
        }
    }
}
BENCHMARK(BM_FunctionCreation)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();