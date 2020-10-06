#include "xcspp/environment/dataset_environment.hpp"
#include <stdexcept>

namespace xcspp
{

    namespace
    {
        std::unordered_set<int> GetAvailableActionsInDataset(const Dataset & dataset)
        {
            std::unordered_set<int> availableActions;
            for (const auto & action : dataset.actions)
            {
                availableActions.insert(action); // already inserted items are ignored here
            }
            return availableActions;
        }
    }

    std::size_t DatasetEnvironment::loadNext()
    {
        if (m_chooseRandom)
        {
            const auto idx = m_random.nextInt<std::size_t>(0UL, m_dataset.situations.size() - 1UL);
            m_situation = m_dataset.situations[idx];
            m_answer = m_dataset.actions[idx];
            return idx;
        }
        else
        {
            m_situation = m_dataset.situations[m_nextIdx];
            m_answer = m_dataset.actions[m_nextIdx];
            const auto idx = m_nextIdx;
            if (++m_nextIdx >= m_dataset.situations.size())
            {
                m_nextIdx = 0;
            }
            return idx;
        }
    }

    DatasetEnvironment::DatasetEnvironment(const Dataset & dataset, bool chooseRandom)
        : m_dataset(dataset)
        , m_availableActions(GetAvailableActionsInDataset(dataset))
        , m_nextIdx(0)
        , m_chooseRandom(chooseRandom)
        , m_isEndOfProblem(false)
    {
        if (m_dataset.situations.size() != m_dataset.actions.size())
        {
            throw std::domain_error("The dataset size is invalid in DatasetEnvironment constructor (situations/actions size does not match).");
        }

        if (m_dataset.situations.empty() || m_dataset.actions.empty())
        {
            throw std::runtime_error("DatasetEnvironment constructor received an empty dataset.");
        }

        loadNext();
    }

    std::vector<int> DatasetEnvironment::situation() const
    {
        return m_situation;
    }

    double DatasetEnvironment::executeAction(int action)
    {
        const double reward = (action == m_answer) ? 1000.0 : 0.0;

        // Single-step problem
        m_isEndOfProblem = true;

        loadNext();

        return reward;
    }

    bool DatasetEnvironment::isEndOfProblem() const
    {
        return m_isEndOfProblem;
    }

    std::unordered_set<int> DatasetEnvironment::availableActions() const
    {
        return m_availableActions;
    }

    int DatasetEnvironment::getAnswer() const
    {
        return m_answer;
    }
}