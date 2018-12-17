#include <vector>

#include <catch.hpp>

#include "eul/container/observable/observing_list.hpp"
#include "eul/container/observable/observing_node.hpp"

struct TestingElement
{
    TestingElement(int x) : a(x)
    {
    }
    int a;
};

TEST_CASE("Observing list should", "[ObservingListTests]")
{
    SECTION("push_back elements")
    {
        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        eul::container::observing_node<TestingElement> a{10};
        eul::container::observing_node<TestingElement> b{20};
        eul::container::observing_node<TestingElement> c{30};

        sut.push_back(a);
        sut.push_back(b);
        sut.push_back(c);

        REQUIRE((*sut.at(0))->a == 10);
        REQUIRE((*sut.at(1))->a == 20);
        REQUIRE((*sut.at(2))->a == 30);
    }

    SECTION("auto remove element out of scope")
    {
        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        eul::container::observing_node<TestingElement> a{10};

        {
            eul::container::observing_node<TestingElement> x{15};
            sut.push_back(x);
            REQUIRE((*sut.at(0))->a == 15);
            REQUIRE(sut.size() == 1);
        }

        sut.push_back(a);
        {
            eul::container::observing_node<TestingElement> b{20};
            sut.push_back(b);

            REQUIRE((*sut.at(1))->a == 20);
            REQUIRE(sut.size() == 2);
        }
        eul::container::observing_node<TestingElement> c{30};
        sut.push_back(c);

        REQUIRE((*sut.at(0))->a == 10);
        REQUIRE((*sut.at(1))->a == 30);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.at(2).has_value() == false);
        {
            eul::container::observing_node<TestingElement> b{20};
            sut.push_back(b);

            REQUIRE((*sut.at(0))->a == 10);
            REQUIRE((*sut.at(1))->a == 30);
            REQUIRE((*sut.at(2))->a == 20);
            REQUIRE(sut.size() == 3);
        }
        REQUIRE((*sut.at(0))->a == 10);
        REQUIRE(sut.at(1).has_value() == true);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.at(2).has_value() == false);
    }

    SECTION("Not insert observed node")
    {
        eul::container::observing_node<TestingElement> b{15};

        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        {
            eul::container::observing_node<TestingElement> a{10};

            REQUIRE(sut.push_back(a));
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 10);
            REQUIRE(sut.at(1).has_value() == false);

            REQUIRE(sut.push_back(a) == false);
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 10);
            REQUIRE(sut.at(1).has_value() == false);

            sut.push_back(b);
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 10);
            REQUIRE(sut.at(1).has_value());
            REQUIRE((*sut.at(1))->a == 15);
            REQUIRE(sut.at(2).has_value() == false);

            REQUIRE(sut.push_back(a) == false);
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 10);
            REQUIRE(sut.at(1).has_value());
            REQUIRE((*sut.at(1))->a == 15);
            REQUIRE(sut.at(2).has_value() == false);
        }
        REQUIRE(sut.at(0).has_value() == true);
        REQUIRE((*sut.at(0))->a == 15);

        REQUIRE(sut.at(1).has_value() == false);
    }

    SECTION("Move node to other list")
    {
        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut2;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};

            REQUIRE(sut.push_back(a));
            REQUIRE(sut.push_back(b));
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 10);
            REQUIRE(sut.at(1).has_value());
            REQUIRE((*sut.at(1))->a == 15);

            sut2.push_back(a);
            REQUIRE(sut2.at(0).has_value());
            REQUIRE((*sut2.at(0))->a == 10);
            REQUIRE(sut2.at(1).has_value() == false);

            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 15);
            REQUIRE(sut.at(1).has_value() == false);
        }
        REQUIRE(sut.at(0).has_value() == false);
        REQUIRE(sut2.at(0).has_value() == false);
    }

    SECTION("Not insert after if node not exists")
    {
        eul::container::observing_node<TestingElement> c{20};

        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};

            REQUIRE(sut.push_back(b));
            REQUIRE(sut.insert_after(a, c) == false);
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 15);
            REQUIRE(sut.at(1).has_value() == false);
        }
        REQUIRE(sut.at(0).has_value() == false);
    }

    SECTION("Insert after node")
    {
        eul::container::observing_node<TestingElement> c{20};

        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};
            eul::container::observing_node<TestingElement> d{30};

            REQUIRE(sut.push_back(a));
            REQUIRE(sut.push_back(b));
            REQUIRE(sut.insert_after(a, c));
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 10);
            REQUIRE(sut.at(1).has_value());
            REQUIRE((*sut.at(1))->a == 20);
            REQUIRE(sut.at(2).has_value());
            REQUIRE((*sut.at(2))->a == 15);

            REQUIRE(sut.insert_after(b, d));
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 10);
            REQUIRE(sut.at(1).has_value());
            REQUIRE((*sut.at(1))->a == 20);
            REQUIRE(sut.at(2).has_value());
            REQUIRE((*sut.at(2))->a == 15);
            REQUIRE(sut.at(3).has_value());
            REQUIRE((*sut.at(3))->a == 30);
        }
        REQUIRE(sut.at(0).has_value());
        REQUIRE((*sut.at(0))->a == 20);
        REQUIRE(sut.at(1).has_value() == false);
    }

    SECTION("Not insert before if node not exists")
    {
        eul::container::observing_node<TestingElement> c{20};

        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};

            REQUIRE(sut.push_back(b));
            REQUIRE(sut.insert_before(a, c) == false);
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 15);
            REQUIRE(sut.at(1).has_value() == false);
        }
        REQUIRE(sut.at(0).has_value() == false);
    }


    SECTION("Insert before node")
    {
        eul::container::observing_node<TestingElement> c{20};

        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};
            eul::container::observing_node<TestingElement> d{30};

            REQUIRE(sut.push_back(a));
            REQUIRE(sut.push_back(b));
            REQUIRE(sut.insert_before(a, c));
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 20);
            REQUIRE(sut.at(1).has_value());
            REQUIRE((*sut.at(1))->a == 10);
            REQUIRE(sut.at(2).has_value());
            REQUIRE((*sut.at(2))->a == 15);

            REQUIRE(sut.insert_before(b, d));
            REQUIRE(sut.at(0).has_value());
            REQUIRE((*sut.at(0))->a == 20);
            REQUIRE(sut.at(1).has_value());
            REQUIRE((*sut.at(1))->a == 10);
            REQUIRE(sut.at(2).has_value());
            REQUIRE((*sut.at(2))->a == 30);
            REQUIRE(sut.at(3).has_value());
            REQUIRE((*sut.at(3))->a == 15);
            REQUIRE(sut.size() == 4);
        }
        REQUIRE(sut.at(0).has_value());
        REQUIRE((*sut.at(0))->a == 20);
        REQUIRE(sut.at(1).has_value() == false);

        eul::container::observing_node<TestingElement> b{15};
        REQUIRE(sut.push_back(b));
        REQUIRE(sut.at(0).has_value());
        REQUIRE((*sut.at(0))->a == 20);
        REQUIRE(sut.at(1).has_value());
        REQUIRE((*sut.at(1))->a == 15);
        REQUIRE(sut.at(2).has_value() == false);
        REQUIRE(sut.size() == 2);
    }

    SECTION("Support for each")
    {
        eul::container::observing_list<
            eul::container::observing_node<TestingElement>>
            sut;
        {
            eul::container::observing_node<TestingElement> a{3};
            eul::container::observing_node<TestingElement> b{2};
            eul::container::observing_node<TestingElement> c{1};
            eul::container::observing_node<TestingElement> d{4};

            {
                const std::vector<int> expectedData;
                std::vector<int> data;

                for (auto& e : sut)
                {
                    data.push_back(e.data().a);
                }

                REQUIRE(expectedData == data);
            }
            {
                const std::vector<int> expectedData{3};
                std::vector<int> data;

                sut.push_back(a);
                for (auto& e : sut)
                {
                    data.push_back(e.data().a);
                }

                REQUIRE(expectedData == data);

                const std::vector<int> expectedData2{3, 1, 2, 4};
                sut.push_back(c);
                sut.push_back(b);
                sut.push_back(d);

                data.clear();
                for (auto& e : sut)
                {
                    data.push_back(e.data().a);
                }

                REQUIRE(expectedData2 == data);

                const std::vector<int> expectedData3{3, 1, 2};
                d.reset();

                data.clear();
                for (auto& e : sut)
                {
                    data.push_back(e.data().a);
                }

                REQUIRE(expectedData3 == data);

                const std::vector<int> expectedData4{1, 2};
                a.reset();

                data.clear();
                for (auto& e : sut)
                {
                    data.push_back(e.data().a);
                }

                REQUIRE(expectedData4 == data);

                const std::vector<int> expectedData5{2};
                c.reset();

                data.clear();
                for (auto& e : sut)
                {
                    data.push_back(e.data().a);
                }

                REQUIRE(expectedData5 == data);
            }
        }

        REQUIRE(sut.size() == 0);
        const std::vector<int> expectedData{};

        std::vector<int> data;
        for (auto& e : sut)
        {
            data.push_back(e.data().a);
        }

        REQUIRE(expectedData == data);
    }
}
