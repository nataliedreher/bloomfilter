# CSPB 2270 – Data Structures - Term Project

#### Data Structure Implemented: Bloom Filter.

From [Wikipedia](https://en.wikipedia.org/wiki/Bloom_filter): "A Bloom filter is a space-efficient probabilistic data structure, conceived by Burton Howard Bloom in 1970, that is used to test whether an element is a member of a set." [[1]](https://en.wikipedia.org/wiki/Bloom_filter)

A Bloom Filter starts with a bit array. A bit array is an array where all values are either 0 or 1. Initially all values of the bit array are set to 0. To add an item to the bit array you first need to hash it. This requires some **k** number of independent hash functions. You take your item then run it through all **k** hash functions and each function will give you an index of the bit array to set to 1. You can repeat this process as many times as you want, however there are some downsides.

Since a Bloom Filter is a "probabilistic data structure" false positive matches are a possibility. It's not all bad as false negatives aren't possible. This means where searching the bit array to see if an item is included in the set you will find out the item might be in the set or that the item is definitely not included in the set. Another downside is that once an item is added to the set it can't be removed from the set. One more downside is that as you add more items to the set the probability of false positives increases. An explanation on how to calculate false positives can be found [here](https://en.wikipedia.org/wiki/Bloom_filter#Probability_of_false_positives).

The major upside to a Bloom Filter is that if you don't mind a small chance of receiving a false positive you can store a large number of items in a set with a very small amount of space. And when well implemented Bloom Filters run very quickly and don't require a lot of resources. 

An example of a real-world implementation of a Bloom Filter comes from the online publishing platform Medium. They use Bloom Filters to greatly lower the chances of recommending articles a user has aleady read.

#### How to compile and run.

1. Clone the repository.
2. CD into the folder that contains this project. Next CD into the build folder.
3. Type `cmake ..` into the terminal then wait until cmake completes.
4. Type `make` into the terminal then wait until make completes.
5. To run the unit tests type `./run_tests` into the terminal. To run the CLI app type `./run_app_1` into the terminal.