#pragma once
#include <vector>
#include <unordered_set>
#include <memory> // std::shared_ptr

#include "classifier.hpp"
#include "constants.hpp"

namespace xcscpp
{

    class ClassifierPtrSet
    {
    public:
        using ClassifierPtr = std::shared_ptr<StoredClassifier>;

    protected:
        Constants *m_pConstants;
        const std::unordered_set<int> m_availableActions;
        std::unordered_set<ClassifierPtr> m_set;

    private:
        static std::unordered_set<ClassifierPtr> makeSetFromClassifiers(const std::vector<Classifier> & classifiers, Constants *pConstants)
        {
            std::unordered_set<ClassifierPtr> set;
            for (const auto & cl : classifiers)
            {
                set.emplace(std::make_shared<StoredClassifier>(cl, pConstants));
            }
            return set;
        }

    public:
        // Constructor
        ClassifierPtrSet(Constants *pConstants, const std::unordered_set<int> & availableActions)
            : m_pConstants(pConstants)
            , m_availableActions(availableActions)
        {
        }

        ClassifierPtrSet(const std::unordered_set<ClassifierPtr> & set, Constants *pConstants, const std::unordered_set<int> & availableActions)
            : m_set(set)
            , m_pConstants(pConstants)
            , m_availableActions(availableActions)
        {
        }

        ClassifierPtrSet(const std::vector<Classifier> & initialClassifiers, Constants *pConstants, const std::unordered_set<int> & availableActions)
            : m_set(makeSetFromClassifiers(initialClassifiers, pConstants))
            , m_pConstants(pConstants)
            , m_availableActions(availableActions)
        {
        }

        // Destructor
        virtual ~ClassifierPtrSet() = default;

        auto empty() const noexcept
        {
            return m_set.empty();
        }

        auto size() const noexcept
        {
            return m_set.size();
        }

        auto begin() const noexcept
        {
            return m_set.begin();
        }

        auto end() const noexcept
        {
            return m_set.end();
        }

        auto cbegin() const noexcept
        {
            return m_set.cbegin();
        }

        auto cend() const noexcept
        {
            return m_set.cend();
        }

        template <class... Args>
        auto insert(Args && ... args)
        {
            return m_set.insert(std::forward<Args>(args)...);
        }

        template <class... Args>
        auto emplace(Args && ... args)
        {
            return m_set.emplace(std::forward<Args>(args)...);
        }

        template <class... Args>
        auto erase(Args && ... args)
        {
            return m_set.erase(std::forward<Args>(args)...);
        }

        void clear() noexcept
        {
            m_set.clear();
        }

        template <class... Args>
        void swap(Args && ... args)
        {
            m_set.swap(std::forward<Args>(args)...);
        }

        template <class... Args>
        auto find(Args && ... args) const
        {
            return m_set.find(std::forward<Args>(args)...);
        }

        template <class... Args>
        auto count(Args && ... args) const
        {
            return m_set.count(std::forward<Args>(args)...);
        }
    };

}
