//
// Created by Piotr Żelazko on 06.05.2018.
//

#define BOOST_TEST_DYN_LINK
#ifdef BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

class Base {
public:
    virtual int foo(){
        return 1;
    }
};

class Child : public Base {
public:
    int foo() override {
        return 2;
    }
};


BOOST_AUTO_TEST_SUITE(playground)

    BOOST_AUTO_TEST_CASE(playground){


        Base base;
        Child child;


        BOOST_CHECK_EQUAL(base.foo(),1);

        BOOST_CHECK_EQUAL(child.foo(),2);


        Base& baseRef = base;
        Base& childRef = child;


        BOOST_CHECK_EQUAL(baseRef.foo(),1);
        BOOST_CHECK_EQUAL(childRef.foo(),2);


        Base* ptr = &child;
        Base& ref = *ptr;

        BOOST_CHECK_EQUAL(ptr->foo(),2);
        BOOST_CHECK_EQUAL(ref.foo(),2);




    }




BOOST_AUTO_TEST_SUITE_END()
#endif // BOOST_TEST_DYN_LINK