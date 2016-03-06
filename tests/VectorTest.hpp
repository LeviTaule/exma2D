#include "MosquitoNet.h"
#include "exma2D/vector2D.hpp"
#include "exma2D/impl/utils.cpp"

#include "exma2D/vendor/degrad/degrad.h"

#include <cmath>
#include <limits>

using namespace Enhedron::Test;
using namespace exma::vector;
using namespace exma::utils;

struct VectorF
{
    float x, y;
};

auto len_t = [](const VectorF vec) -> float
{
    return sqrt(vec.x*vec.x + vec.y*vec.y);
};

void checkVectorComponents(Check& check, VectorF a, VectorF b) {
    check.when("The respective values of the components should be equal", [&] {
        check(VAR(compare(a.x, b.x)) && VAR(compare(a.y, b.y)) &&
            // Just so we can see the values
            (true || (VAR(a.x) && VAR(a.y) &&  VAR(b.x) && VAR(b.y)))
        );
    });
}

static Suite s("vectors",
    context("constexpr",
        given("constexpr functions", [](auto & check)
        {
            constexpr VectorF vec_a {1, 1};
            constexpr VectorF vec_b {5, -3};
            constexpr float scalar_a = .5f;

            constexpr auto additon = vec_a + vec_b;
            constexpr auto subtraction = vec_a - vec_b;
            constexpr auto multiplication_vec_scalar = vec_a * scalar_a;
            constexpr auto multiplication_scalar_vec = scalar_a * vec_a;
            constexpr auto division = vec_a / scalar_a;
            constexpr auto equality = vec_a == vec_b;
            constexpr auto inequality = vec_a != vec_b;
            constexpr auto reverse = -vec_a;
            constexpr auto perpendicular = perpendicule(vec_a);
            constexpr auto dot_product = dot(vec_a, vec_b);
            constexpr auto cross_product = cross(vec_a, vec_b);
            constexpr auto len_squared = len2(vec_a);
            constexpr auto projection = project(vec_b, vec_a);
            constexpr auto projection_n = projectN(vec_b, vec_a);
            constexpr auto reflection = reflect(vec_b, vec_a);
            constexpr auto reflection_n = reflectN(vec_b, vec_a);
        })
    ),
    context("addition",
        given("a zero and a 'positive' vector",
            checkVectorComponents,
            VectorF{0, 0} + VectorF{1, 2},
            VectorF {1, 2}),
        given("two 'positive' vectors, one non-integer (FP)",
            checkVectorComponents,
            VectorF{1, 2} + VectorF{5, 6.5},
            VectorF{6, 8.5}),
        given("a 'positive' and a 'negative' vector",
            checkVectorComponents,
            VectorF{1, 2} + VectorF{-2, -4.5},
            VectorF{-1, -2.5}),
        given("a zero and a 'negative' vector",
            checkVectorComponents,
            VectorF{0, 0} + VectorF{-2, -4.5},
            VectorF{-2, -4.5})
    ),
    context("subtraction",
        given("a zero and a 'positive' vector",
            checkVectorComponents,
            VectorF{0, 0} - VectorF{1, 2},
            VectorF {-1, -2}),
        given("two 'positive' vectors, one non-integer (FP)",
            checkVectorComponents,
            VectorF{1, 2} - VectorF{5, 6.5},
            VectorF{-4, -4.5}),
        given("a 'positive' and a 'negative' vector",
            checkVectorComponents,
            VectorF{1, 2} - VectorF{-2, -4.5},
            VectorF{3, 6.5}),
        given("a zero and a 'negative' vector",
            checkVectorComponents,
            VectorF{0, 0} - VectorF{-2, -4.5},
            VectorF{2, 4.5})
    ),
    context("scaling",
        given("a 'positive' vector and multiplicating by a scalar zero",
            checkVectorComponents,
            VectorF{1, 2} * 0 ,
            VectorF {0, 0}),
        given("a zero scalar",[](auto & check)
        {
            check.when("dividing by zero", [&]()
            {
                constexpr VectorF vec_a{4, 2};

                auto result_a = vec_a / 0;

                check("NaN is reuturned",
                    VAR(std::isnan(result_a.x)) &&
                    VAR(std::isnan(result_a.y)));
            });
        }),
        given("a scalar zero and a 'positive' vector",
            checkVectorComponents,
            0 * VectorF{1, 2},
            VectorF {0, 0}),
        given("a 'mixed' vector and multiplicating by a scalar > 1",
            checkVectorComponents,
            VectorF{-1, 2} * 300,
            VectorF{-300, 600}),
        given("a 'mixed' vector and dividing by a scalar > 1",
            checkVectorComponents,
            VectorF{-600, 300} / 300,
            VectorF{-2, 1}),
        given("a scalar > 1 and a 'positive' vector",
            checkVectorComponents,
            3 * VectorF{1, 2},
            VectorF{3, 6}),
        given("an FP scalar < 1 and > 0 and a 'negative' vector",
            checkVectorComponents,
            0.25f * VectorF{-2.f, -5.f},
            VectorF{-0.5f, -1.25f}),
        given("a 'mixed' vector and an FP scalar < 0",
            checkVectorComponents,
            VectorF{2, -5.f} * -2.5f,
            VectorF{-5, 12.5f})
    ),
    context("equality",
        given("two vectors", [](auto & check)
        {
            constexpr VectorF vec_a{1.f, 50.f};
            constexpr VectorF vec_b{1, 50.f};
            constexpr VectorF vec_c{20.f, 50};
            constexpr VectorF vec_d{1, -50.f};

            check.when("they are same", [&]()
            {
                auto result_a = vec_a == vec_a;
                auto result_b = vec_a == vec_b;
                auto result_c = vec_a != vec_b;
                auto result_d = vec_a != vec_b;

                check("true is returned",
                    VAR(result_a) && VAR(result_b));
                check("false is returned",
                    !(VAR(result_c) && VAR(result_d)));
            });

            check.when("at least one component is different", [&]()
            {
                auto result_a = vec_a == vec_c;
                auto result_b = vec_a == vec_d;
                auto result_c = vec_a != vec_c;
                auto result_d = vec_a != vec_d;

                check("false is returned",
                    !VAR(result_a) && !VAR(result_b));;
                check("true is returned",
                    VAR(result_c) && VAR(result_d));
            });
        }),
        given("a scalar zero and a 'positive' vector",
            checkVectorComponents,
            0 * VectorF{1, 2},
            VectorF {0, 0}),
        given("a 'mixed' vector and multiplicating by a scalar > 1",
            checkVectorComponents,
            VectorF{-1, 2} * 300,
            VectorF{-300, 600}),
        given("a 'mixed' vector and dividing by a scalar > 1",
            checkVectorComponents,
            VectorF{-600, 300} / 300,
            VectorF{-2, 1}),
        given("a scalar > 1 and a 'positive' vector",
            checkVectorComponents,
            3 * VectorF{1, 2},
            VectorF{3, 6}),
        given("an FP scalar < 1 and > 0 and a 'negative' vector",
            checkVectorComponents,
            0.25f * VectorF{-2.f, -5.f},
            VectorF{-0.5f, -1.25f}),
        given("a 'mixed' vector and an FP scalar < 0",
            checkVectorComponents,
            VectorF{2, -5.f} * -2.5f,
            VectorF{-5, 12.5f})
    ),
    context("cross product",
        given("two vectors",[](auto & check)
        {
            constexpr VectorF zero{0.f, 0.f};
            constexpr VectorF positive{1.f, 30.f};
            constexpr VectorF negative{-1.f, -30.f};
            constexpr VectorF mixed{-1.f, 30.f};
            check.when("at least of them one is a zero vector", [&]()
            {
                constexpr auto result_a = cross(zero, positive);
                constexpr float result_b = cross(negative, zero);
                constexpr float result_c = cross(mixed, zero);
                constexpr float result_d = cross(zero, zero);
                check("cross product is zero",
                    VAR(result_a) == 0 && VAR(result_b == 0) && 
                    VAR(result_c == 0) && VAR(result_d == 0));
            });
            check.when("other things happen", [&]()
            {
                constexpr float result_a = cross(positive, positive);
                constexpr float result_b = cross(positive, negative);
                constexpr float result_c = cross(positive, mixed);
                constexpr float result_d = cross(negative,  negative);
                constexpr float result_e = cross(negative, mixed);
                constexpr float result_f = cross(mixed, mixed);

                check("it yields the correct result",
                      VAR(result_a) == VAR(result_d) &&
                      VAR(result_c) == VAR(-result_e) &&
                      VAR(result_b) == VAR(-result_a)
                );
            });
        })
    ),
    context("dot product",
        given("two vectors",[](auto & check)
        {
            constexpr VectorF zero{0.f, 0.f};
            constexpr VectorF positive{1.f, 30.f};
            constexpr VectorF negative{-1.f, -30.f};
            constexpr VectorF mixed{-1.f, 30.f};
            check.when("at least of them one is a zero vector", [&]()
            {
                constexpr auto result_a = dot(zero, positive);
                constexpr float result_b = dot(negative, zero);
                constexpr float result_c = dot(mixed, zero);
                constexpr float result_d = dot(zero, zero);
                check("dot product is zero",
                    VAR(result_a) == 0 && VAR(result_b == 0) && 
                    VAR(result_c == 0) && VAR(result_d == 0));
            });
            check.when("other things happen", [&]()
            {
                constexpr float result_a = dot(positive, positive);
                constexpr float result_b = dot(positive, negative);
                constexpr float result_c = dot(positive, mixed);
                constexpr float result_d = dot(negative,  negative);
                constexpr float result_e = dot(negative, mixed);
                constexpr float result_f = dot(mixed, mixed);

                check("it yields the correct result",
                      VAR(result_a) == VAR(result_d) &&
                      VAR(result_c) == VAR(-result_e) &&
                      VAR(result_b) == VAR(-result_a)
                );
            });
        })
    ),
    context("length and length^2",
        given("'triangles'", [](auto & check)
        {
            check.when("all the sides are non-zero", [&]()
            {
                constexpr VectorF triangle_sides_a{3, 4};
                constexpr VectorF triangle_sides_b{6, 8};
                constexpr VectorF triangle_sides_c{-3, -4};
                constexpr VectorF triangle_sides_d{-3, 4};

                auto result_a = len(triangle_sides_a);
                constexpr auto result_a2 = len2(triangle_sides_a);
                auto result_b = len(triangle_sides_b);
                constexpr auto result_b2 = len2(triangle_sides_b);
                constexpr auto result_c2 = len2(triangle_sides_c);
                constexpr auto result_d2 = len2(triangle_sides_d);

                check("the hypothenuse is correct",
                    VAR(result_a*result_a) == VAR(result_a2) &&
                    VAR(result_b*result_b) == VAR(result_b2) &&
                    VAR(result_a) == 5 &&
                    VAR(result_a2) == VAR(result_c2) &&
                    VAR(result_a2) == VAR(result_d2));
            });
            check.when("0-1 sides are 0", [&]()
            {
                constexpr VectorF triangle_sides_a{0, 4};
                constexpr VectorF triangle_sides_b{4, 0};
                constexpr VectorF triangle_sides_c{0, 0};

                auto result_a = len(triangle_sides_a);
                constexpr auto result_a2 = len2(triangle_sides_a);
                auto result_b = len(triangle_sides_b);
                constexpr auto result_b2 = len2(triangle_sides_b);
                auto result_c = len(triangle_sides_c);
                constexpr auto result_c2 = len2(triangle_sides_c);

                check("the length is correct",
                    VAR(result_a) == VAR(result_b) &&
                    VAR(result_c) == 0 &&
                    VAR(result_a) == 4);
            });
        })
    ),
    context("normalizing",
        given("a vector", [](auto & check)
        {
            check.when("the vector is non-unit non-zero", [&]()
            {
                constexpr VectorF vector_a{4, 4};
                constexpr VectorF vector_b{4, 8};
                constexpr VectorF vector_c{2, 5};
                constexpr VectorF vector_d{-2, -5};
                constexpr VectorF vector_e{2, -5};

                auto result_a = len_t(normalize(vector_a));
                auto result_b = len_t(normalize(vector_b));
                auto result_c = len_t(normalize(vector_c));
                auto result_d = len_t(normalize(vector_d));
                auto result_e = len_t(normalize(vector_e));

                check("the units are unit length",
                    VAR(compare(result_a, result_b)) &&
                    VAR(compare(result_a, result_c)) &&
                    VAR(compare(result_a, result_d)) &&
                    VAR(compare(result_a, result_e)) &&
                    VAR(compare(result_a, 1.f)));
            });
            check.when("the vector has 0-1 zero components", [&]()
            {
                constexpr VectorF vec_a{0, 4};
                constexpr VectorF vec_b{4, 0};
                constexpr VectorF vec_c{0, 0};

                auto result_a = normalize(vec_a);
                auto result_b = normalize(vec_b);
                auto result_c = normalize(vec_c);

                check("NaN is reuturned",
                    VAR(!std::isnan(result_a.x)) &&
                    VAR(!std::isnan(result_b.x)) &&
                    VAR(std::isnan(result_c.x))
                );
            });
        })
    ),
    context("projecting",
        given("a non-unit vector and a unit axis vector",
            checkVectorComponents,
            projectN(VectorF{10, 10},  VectorF{1, 0}),
            VectorF {10, 0}),
        given("a unit vector and a non-unit axis vector",
            checkVectorComponents,
            project(VectorF{1, 1}, VectorF{10, 10}),
            VectorF {1, 1}),
        given("a vector with non-equal components",
            checkVectorComponents,
            project(VectorF{10, 5}, VectorF{10, 10}),
            VectorF {7.5, 7.5}),
        given("a vector with a negative component and a unit vector",
            checkVectorComponents,
            projectN(VectorF{10, -5}, VectorF{0, 1}),
            VectorF {0, -5}),
        given("a vector with negative components",
            checkVectorComponents,
            project(VectorF{10, -5}, VectorF{-3, 4}),
            VectorF {6, -8}),
        given("a zero vector/axis", [](auto & check)
        {
            check.when("the axis is zero", [&]()
            {
                auto result = project(VectorF{10, -5}, VectorF{0, 0});
                 check("NaN is reuturned",
                    VAR(std::isnan(result.x)) &&
                    VAR(std::isnan(result.y))
                );
            });
            check.when("the vector is zero", [&]()
            {
                auto result = project(VectorF{0, 0}, VectorF{10, -5});
                 check("<0, 0> is returned",
                    VAR(result.x) == 0.f &&
                    VAR(result.y) == 0.f
                );
            });
        })
    ),
    context("reflecting",
        given("a non-unit vector and a unit axis vector",
            checkVectorComponents,
            reflectN(VectorF{10, 10},  VectorF{1, 0}),
            VectorF {-10, 10}),
        given("two non-units vectors",
            checkVectorComponents,
            reflect(VectorF{10, 10},  VectorF{5, 15}),
            VectorF {2, -14}),
        given("vectors with mixed sign components",
            checkVectorComponents,
            reflect(VectorF{-10, 10},  VectorF{5, -15}),
            VectorF {-2, -14})
    ),
    context("rotating",
        given("axis-aligned rotating",
            checkVectorComponents,
            rotate(VectorF{10, 0},  VectorF{0, 0}, 90_deg),
            VectorF {0, 10}),
        given("non-axis-aligned rotating",
            checkVectorComponents,
            rotate(VectorF{10, 10},  VectorF{0, 0}, 180_deg),
            VectorF {-10, -10}),
        given("moved origin",
            checkVectorComponents,
            rotate(VectorF{10, 10},  VectorF{-1, -1}, 180_deg),
            VectorF {-12, -12})
    ),
    given("a vector", [](auto & check)
    {
        constexpr float x = 2.f, y = 3.f;
        constexpr VectorF vec{x, y};

        check.when("we reverse vector", [&]()
        {
            constexpr VectorF reversed = -vec;
            check("vector has the value of both the components negated",
                VAR(reversed.x) == VAR(-vec.x) &&
                VAR(reversed.y) == VAR(-vec.y)
            );
        });

        check.when("we make the vector perpendicular", [&]()
        {
            constexpr VectorF perpendicular = perpendicule(vec);
            check("vector has the value of one of the components negated",
                VAR(perpendicular.x) == y && VAR(perpendicular.y) == -x ||
                VAR(perpendicular.x) == -y && VAR(perpendicular.y) == x);
        });
    })
);
