# ipow
My variant of integer pow.

Performance comparison (unsafe) ipow vs std::pow

    size 1	unsafe_ipow avg: 25.9899 ns	 pow avg: 35.9951 ns	-27.796%
    size 2	unsafe_ipow avg: 21.2945 ns	 pow avg: 30.0231 ns	-29.0729%
    size 4	unsafe_ipow avg: 21.511 ns	 pow avg: 32.4803 ns	-33.7721%
    size 1	unsafe_ipow avg: 21.27 ns	 pow avg: 29.5151 ns	-27.9351%
    size 2	unsafe_ipow avg: 21.1839 ns	 pow avg: 29.9409 ns	-29.2478%
    size 4	unsafe_ipow avg: 21.8938 ns	 pow avg: 32.6738 ns	-32.9928%
