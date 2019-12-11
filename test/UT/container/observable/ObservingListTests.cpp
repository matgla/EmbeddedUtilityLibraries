// This file is part of EUL project. This project is set of libraries useful for embedded development.
// Copyright (C) 2019 Mateusz Stadnik
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <vector>

#include <catch.hpp>

#include "eul/container/observable/observing_list.hpp"
#include "eul/container/observable/observing_node.hpp"

struct TestingElement
{
    TestingElement(int x)
        : a(x)
    {
    }
    int a;
};

TEST_CASE("Observing list should", "[ObservingListTests]")
{
    SECTION("push_back elements")
    {
        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        eul::container::observing_node<TestingElement> a{10};
        eul::container::observing_node<TestingElement> b{20};
        eul::container::observing_node<TestingElement> c{30};

        sut.push_back(a);
        sut.push_back(b);
        sut.push_back(c);

        REQUIRE(sut.at(0)->a == 10);
        REQUIRE(sut.at(1)->a == 20);
        REQUIRE(sut.at(2)->a == 30);
    }

    SECTION("push_front elements")
    {
        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        eul::container::observing_node<TestingElement> a{10};
        eul::container::observing_node<TestingElement> b{20};
        eul::container::observing_node<TestingElement> c{30};

        sut.push_front(a);
        sut.push_front(b);
        sut.push_front(c);

        REQUIRE(sut.at(2)->a == 10);
        REQUIRE(sut.at(1)->a == 20);
        REQUIRE(sut.at(0)->a == 30);
    }

    SECTION("auto remove element out of scope")
    {
        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        eul::container::observing_node<TestingElement> a{10};

        {
            eul::container::observing_node<TestingElement> x{15};
            sut.push_back(x);
            REQUIRE(sut.at(0)->a == 15);
            REQUIRE(sut.size() == 1);
        }

        sut.push_back(a);
        {
            eul::container::observing_node<TestingElement> b{20};
            sut.push_back(b);

            REQUIRE(sut.at(1)->a == 20);
            REQUIRE(sut.size() == 2);
        }
        eul::container::observing_node<TestingElement> c{30};
        sut.push_back(c);

        REQUIRE(sut.at(0)->a == 10);
        REQUIRE(sut.at(1)->a == 30);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.at(2) == nullptr);
        {
            eul::container::observing_node<TestingElement> b{20};
            sut.push_back(b);

            REQUIRE(sut.at(0)->a == 10);
            REQUIRE(sut.at(1)->a == 30);
            REQUIRE(sut.at(2)->a == 20);
            REQUIRE(sut.size() == 3);
        }
        REQUIRE(sut.at(0)->a == 10);
        REQUIRE(sut.at(1) != nullptr);
        REQUIRE(sut.size() == 2);
        REQUIRE(sut.at(2) == nullptr);
    }

    SECTION("Not insert observed node")
    {
        eul::container::observing_node<TestingElement> b{15};

        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        {
            eul::container::observing_node<TestingElement> a{10};

            REQUIRE(sut.push_back(a));
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 10);
            REQUIRE(sut.at(1) == nullptr);

            REQUIRE(sut.push_back(a) == false);
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 10);
            REQUIRE(sut.at(1) == nullptr);

            sut.push_back(b);
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 10);
            REQUIRE(sut.at(1));
            REQUIRE(sut.at(1)->a == 15);
            REQUIRE(sut.at(2) == nullptr);

            REQUIRE(sut.push_back(a) == false);
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 10);
            REQUIRE(sut.at(1));
            REQUIRE(sut.at(1)->a == 15);
            REQUIRE(sut.at(2) == nullptr);
        }
        REQUIRE(sut.at(0));
        REQUIRE(sut.at(0)->a == 15);

        REQUIRE(sut.at(1) == nullptr);
    }

    SECTION("Move node to other list")
    {
        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut2;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};

            REQUIRE(sut.push_back(a));
            REQUIRE(sut.push_back(b));
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 10);
            REQUIRE(sut.at(1));
            REQUIRE(sut.at(1)->a == 15);

            sut2.push_back(a);
            REQUIRE(sut2.at(0));
            REQUIRE(sut2.at(0)->a == 10);
            REQUIRE(sut2.at(1) == nullptr);

            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 15);
            REQUIRE(sut.at(1) == nullptr);
        }
        REQUIRE(sut.at(0) == nullptr);
        REQUIRE(sut2.at(0) == nullptr);
    }

    SECTION("Not insert after if node not exists")
    {
        eul::container::observing_node<TestingElement> c{20};

        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};

            REQUIRE(sut.push_back(b));
            REQUIRE(sut.insert_after(a, c) == false);
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 15);
            REQUIRE(sut.at(1) == nullptr);
        }
        REQUIRE(sut.at(0) == nullptr);
    }

    SECTION("Insert after node")
    {
        eul::container::observing_node<TestingElement> c{20};

        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};
            eul::container::observing_node<TestingElement> d{30};

            REQUIRE(sut.push_back(a));
            REQUIRE(sut.push_back(b));
            REQUIRE(sut.insert_after(a, c));
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 10);
            REQUIRE(sut.at(1));
            REQUIRE(sut.at(1)->a == 20);
            REQUIRE(sut.at(2));
            REQUIRE(sut.at(2)->a == 15);

            REQUIRE(sut.insert_after(b, d));
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 10);
            REQUIRE(sut.at(1));
            REQUIRE(sut.at(1)->a == 20);
            REQUIRE(sut.at(2));
            REQUIRE(sut.at(2)->a == 15);
            REQUIRE(sut.at(3));
            REQUIRE(sut.at(3)->a == 30);
        }
        REQUIRE(sut.at(0));
        REQUIRE(sut.at(0)->a == 20);
        REQUIRE(sut.at(1) == nullptr);
    }

    SECTION("Not insert before if node not exists")
    {
        eul::container::observing_node<TestingElement> c{20};

        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};

            REQUIRE(sut.push_back(b));
            REQUIRE(sut.insert_before(a, c) == false);
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 15);
            REQUIRE(sut.at(1) == nullptr);
        }
        REQUIRE(sut.at(0) == nullptr);
    }


    SECTION("Insert before node")
    {
        eul::container::observing_node<TestingElement> c{20};

        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
        {
            eul::container::observing_node<TestingElement> a{10};
            eul::container::observing_node<TestingElement> b{15};
            eul::container::observing_node<TestingElement> d{30};

            REQUIRE(sut.push_back(a));
            REQUIRE(sut.push_back(b));
            REQUIRE(sut.insert_before(a, c));
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 20);
            REQUIRE(sut.at(1));
            REQUIRE(sut.at(1)->a == 10);
            REQUIRE(sut.at(2));
            REQUIRE(sut.at(2)->a == 15);

            REQUIRE(sut.insert_before(b, d));
            REQUIRE(sut.at(0));
            REQUIRE(sut.at(0)->a == 20);
            REQUIRE(sut.at(1));
            REQUIRE(sut.at(1)->a == 10);
            REQUIRE(sut.at(2));
            REQUIRE(sut.at(2)->a == 30);
            REQUIRE(sut.at(3));
            REQUIRE(sut.at(3)->a == 15);
            REQUIRE(sut.size() == 4);
        }
        REQUIRE(sut.at(0));
        REQUIRE(sut.at(0)->a == 20);
        REQUIRE(sut.at(1) == nullptr);

        eul::container::observing_node<TestingElement> b{15};
        REQUIRE(sut.push_back(b));
        REQUIRE(sut.at(0));
        REQUIRE(sut.at(0)->a == 20);
        REQUIRE(sut.at(1));
        REQUIRE(sut.at(1)->a == 15);
        REQUIRE(sut.at(2) == nullptr);
        REQUIRE(sut.size() == 2);
    }

    SECTION("Support for each")
    {
        eul::container::observing_list<eul::container::observing_node<TestingElement>> sut;
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
