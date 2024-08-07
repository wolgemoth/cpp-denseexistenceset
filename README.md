# C++ DenseExistenceSet (1.0.0)

## Table of Contents

- [About](#About)
- [Instructions](#Instructions)
- [Dependencies](#Dependencies)
- [References](#References)

### About

This is a dense existence set written in C++.

This data structure is designed to allow developers to perform efficient key existence checks without needing to store the original keys in memory.
It provides a variety of options for how the set should align its buckets in memory.

Since the set does not need to store the original keys in memory, it is much more efficient than a traditional set in situations requiring key existence checks.

Please note that this data structure does not provide a mechanism to resolve hash collisions. It is the developer's responsibility to use an appropriate hash function.

If you find a bug or have a feature-request, please raise an issue.

### Instructions

The implementation is header-only and written in templated C++17. You should not need to make any adjustments to your project settings or compiler flags. 

Simply include it in your project and you are ready to start!

### Dependencies

The DenseExistenceSet was written in C++17 and utilises the following standard headers:

#### &lt;vector&gt;
