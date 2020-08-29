#pragma once
#include <vector>
#include <unordered_set>

namespace xcscpp
{

    class IEnvironment
    {
    public:
        IEnvironment() = default;

        virtual ~IEnvironment() = default;

        // Returns current situation
        virtual std::vector<int> situation() const = 0;

        // Executes action (and update situation) and returns reward
        virtual double executeAction(int action) = 0;

        // Returns true if the problem was solved by the previous action
        // (always true for a single-step problem after the first action execution)
        virtual bool isEndOfProblem() const = 0;

        // Returns available actions (e.g. { 0, 1 })
        virtual const std::unordered_set<int> & availableActions() const = 0;
    };

}
