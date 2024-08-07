// Copyright (c) 2024 Loui Eriksson
// All rights reserved.

#ifndef LOUI_ERIKSSON_DENSE_EXISTENCE_SET_HPP
#define LOUI_ERIKSSON_DENSE_EXISTENCE_SET_HPP

#include <vector>

namespace LouiEriksson {

    struct LowestMemoryUsage  {};
    struct LowMemoryUsage     {};
    struct Balanced           {};
    struct HighestPerformance {};

    template<typename T>
    struct Alignment {};

    template<>
    struct Alignment<LowestMemoryUsage> {
        using Type = bool;
    };

    template<>
    struct Alignment<LowMemoryUsage> {
        using Type = char;
    };

    template<>
    struct Alignment<Balanced> {
        using Type = int32_t;
    };

    template<>
    struct Alignment<HighestPerformance> {
        using Type = intptr_t;
    };

    template <typename AlignmentType = LowestMemoryUsage>
    class DenseExistenceSet {

    private:

        std::vector<typename Alignment<AlignmentType>::Type> m_Bits;

    public:

        void Add(const size_t& _hash) {

            if (_hash >= m_Bits.size()) {
                m_Bits.resize(_hash + 1U);
            }

            m_Bits[_hash] = static_cast<typename Alignment<AlignmentType>::Type>(true);
        }

        void Remove(const size_t& _hash) {

            if (_hash < m_Bits.size()) {
                m_Bits[_hash] = static_cast<typename Alignment<AlignmentType>::Type>(false);
            }
        }

        [[nodiscard]] bool Contains(const size_t& _hash) const {
            return _hash >= m_Bits.size() ? false : static_cast<bool>(m_Bits[_hash]);
        }

        void Clear() {
            m_Bits.clear();
        }
    };

} // LouiEriksson

#endif //LOUI_ERIKSSON_DENSE_EXISTENCE_SET_HPP