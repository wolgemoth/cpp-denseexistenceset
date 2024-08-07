// Copyright (c) 2024 Loui Eriksson
// All rights reserved.

#ifndef LOUI_ERIKSSON_DENSE_EXISTENCE_SET_HPP
#define LOUI_ERIKSSON_DENSE_EXISTENCE_SET_HPP

#include <vector>

namespace LouiEriksson {
    
    struct LowestMemoryUsage  {}; /** @brief Each item is represented by 1 bit in memory. */
    struct LowMemoryUsage     {}; /** @brief Each item is represented by 8 bits in memory. */
    struct Balanced           {}; /** @brief Each item is represented by 32 bits in memory. */
    struct HighestPerformance {}; /** @brief Each item is represented by the system size of a DWORD in memory. */

    template<typename T>
    struct Alignment {};
    template<> struct Alignment<LowestMemoryUsage>  { using Type =      bool; };
    template<> struct Alignment<LowMemoryUsage>     { using Type =      char; };
    template<> struct Alignment<Balanced>           { using Type =  uint32_t; };
    template<> struct Alignment<HighestPerformance> { using Type = uintptr_t; };

    /**
     * @mainpage Version 1.0.0
     * @class DenseExistenceSet
     * @details A set allowing for efficient existence checks without needing to store the original data in memory.
     *
     * @tparam AlignmentType The alignment type used by the set.
     *
     * @see LowestMemoryUsage
     * @see LowMemoryUsage
     * @see Balanced
     * @see HighestPerformance
     */
    template <typename AlignmentType = LowestMemoryUsage>
    class DenseExistenceSet {

        static_assert(
            std::is_same_v<AlignmentType, LowestMemoryUsage>  ||
            std::is_same_v<AlignmentType, LowMemoryUsage>     ||
            std::is_same_v<AlignmentType, Balanced>           ||
            std::is_same_v<AlignmentType, HighestPerformance>,
            "AlignmentType must be one of the following: "
            "LowestMemoryUsage, LowMemoryUsage, Balanced, HighestPerformance"
        );

    private:

        using boolean_t = typename Alignment<AlignmentType>::Type;

        std::vector<boolean_t> m_Bits;

    public:

        /**
         * @brief Initialise set.
         * @param[in] _capacity Initial capacity of the set. Must be larger than 0.
         */
        constexpr explicit DenseExistenceSet(const size_t& _capacity = 1U) {
            m_Bits.resize(_capacity);
        }

        /**
         * @brief Initialise set using a collection of items.
         * @details Please note: Duplicate entries will be merged.
         *
         * @param[in] _items Items to construct the set using.
         * @param[in] _capacity Initial capacity of the set. If a value less than 1 is assigned, it will use the size of the provided collection.
         */
        constexpr DenseExistenceSet(const std::initializer_list<size_t>& _items, const size_t& _capacity = 0U) {

            size_t auto_capacity = _capacity;

            if (auto_capacity < 1U) {
                auto_capacity = std::max<size_t>(_items.size(), 1U);
            }

            m_Bits.reserve(auto_capacity);

            for (const auto& item : _items) {
                Add(item);
            }
        }

        /**
         * @brief Add a hash to the set.
         * @param[in] _hash The hash value to be added.
         */
        void Add(const size_t& _hash) {

            if (_hash >= m_Bits.size()) {
                m_Bits.resize(_hash + 1U);
            }

            m_Bits[_hash] = static_cast<boolean_t>(true);
        }

        /**
         * @brief Remove a hash from the set.
         * @param[in] _hash The hash value to be removed.
         * @note Please note that this function does not resize the set.
         *
         * @see set::Trim()
         * @see set::Clear()
         */
        void Remove(const size_t& _hash) {

            if (_hash < m_Bits.size()) {
                m_Bits[_hash] = static_cast<boolean_t>(false);
            }
        }

        /**
         * @brief Check if the given hash exists in the set.
         * @param[in] _hash The hash value to check.
         * @return True if the hash exists in the set, false otherwise.
         */
        [[nodiscard]] inline bool Contains(const size_t& _hash) const {
            return _hash < m_Bits.size() && static_cast<bool>(m_Bits[_hash]);
        }

        /**
         * @brief Trim the set by removing trailing false values.
         *
         * @see set::Clear()
         */
        void Trim() {

            const auto it = std::find_if(
                m_Bits.rbegin(),
                m_Bits.rend(),
                [](const auto& bit) constexpr {
                    return static_cast<bool>(bit);
                }
            );

            if (it != m_Bits.rend()) {
                m_Bits.resize(std::distance(it, m_Bits.rend()));
            }
            else {
                Clear();
            }
        }

        /**
         * @brief Clear the content of the set.
         * @details Remove all elements from the set.
         */
        void Clear() {
            m_Bits.clear();
        }

        /**
         * @brief Get the size of the set.
         * @details Returns the number of elements in the set.
         *
         * @return The size of the set.
         */
        constexpr auto Size() const {
            return m_Bits.size();
        }
    };

} // LouiEriksson

#endif //LOUI_ERIKSSON_DENSE_EXISTENCE_SET_HPP
