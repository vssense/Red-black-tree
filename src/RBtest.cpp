#define POISON 0
#include "RBtree.h"
#include <set>
#include <time.h>

const size_t STANDARD_TEST_SIZE = 1000000;
const int MIN_VALUE = -16383;

enum Commands
{
    INSERT,
    DELETE,
    FIND,
    NUM_COMMANDS,
    UPPER_BOUND,
    LOWER_BOUND,
};

struct Command
{
    Commands cmd;
    int question;
    int answer;
};

Command* GetTest(size_t size)
{
    Command* test = (Command*)calloc(size, sizeof(Command));
    assert(test);

    for (size_t i = 0; i < size; ++i)
    {
        test[i].cmd = Commands(rand() % NUM_COMMANDS);
        test[i].question = MIN_VALUE + rand();
    }

    return test;
}

void GetAnswers(Command* test, size_t size)
{
    std::set<int> correct_tree;

    clock_t start = clock();

    for (size_t i = 0; i < size; ++i)
    {
        switch (test[i].cmd)
        {
            case INSERT :
            {
                correct_tree.insert(test[i].question);
                test[i].answer = 0;
                break;
            }
            case DELETE :
            {
                correct_tree.erase(test[i].question);
                test[i].answer = 0;
                break;
            }
            case FIND :
            {
                test[i].answer = correct_tree.find(test[i].question) != correct_tree.end();
                break;
            }
            default :
            {
                printf("Error : unknown command\n");
                break;
            }
        }
    }

    clock_t end = clock();

    printf("std::set finished work\ntime = %lg ms\n", (end - start + 0.0) * 1000 / CLOCKS_PER_SEC);
}

void TestRBtree(Command* test, size_t size)
{
    assert(test);
    assert(size);

    RBtree tree = {};
    Construct(&tree);

    bool test_passed = true;

    clock_t start = clock();

    for (size_t i = 0; i < size; ++i)
    {
        switch (test[i].cmd)
        {
            case INSERT :
            {
                Insert(&tree, test[i].question);
                break;
            }
            case DELETE :
            {
                Delete(&tree, test[i].question);
                break;
            }
            case FIND :
            {
                bool is_found = Find(&tree, test[i].question);
                if (test[i].answer != is_found)
                {
                    test_passed = false;
                    if (is_found)
                    {
                        printf("Error : found %d\n", test[i].question);
                    }
                    else
                    {
                        printf("Error : not found %d\n", test[i].question);
                    }
                }
                break;
            }
            default :
            {
                printf("Error : unknown command\n");
                break;
            }
        }
    }

    clock_t end = clock();
    if (!test_passed)
    {
        printf("Test failed!\n");    
    }

    printf("RBtree finished work\ntime = %lg ms\n", (end - start + 0.0) * 1000 / CLOCKS_PER_SEC);    
}

void TestFind(size_t size)
{
    Command* test = GetTest(size);

    GetAnswers(test, size);

    TestRBtree(test, size);

}

int main(const int argc, const char* argv[])//!!! atoi
{
    if (argc - 1 > 0)
    {
        TestFind(atoi(argv[1]));
    }
    else
    {
        TestFind(STANDARD_TEST_SIZE);
    }

    
    return 0;
}