# dog-shelter
Practice with hash tables, especially collision resolution with open addressing in hash tables



<h2>Overview</h2>

The application should create a hash table using open addressing with quadratic probing (where f(i) = i2) to keep track of these dogs where each element in a hash table represents a dog. The initial size of the hash table should be 11. If the load factor λ (The total number of dogs in a hash table / the size of the hash table) becomes larger than 0.5, then the size of the hash table should be doubled and rounded to the next prime number, and then re-hashing should be performed. The hash function should be as follows where the key represents the unique identifier of a dog.


<h2>Functional Requirements</h2>

1)Add a dog

The operation will ask for all the necessary information and then create a dog structure. It then places it in an appropriate position in a hash table. If the load factor of the hash table becomes more than 0.5, and then rehashing will be performed as mentioned above. An example is provided below where the input is shown in bold. If the id is not unique, then the application should print "Id should be unique!" and go back to the main menu.

2) Search for a dog

The operation will ask for an identifier for a dog and then try to find the dog in the hash table and then print its details if found. An example is provided below where the input is shown in bold. The dog is not found, then the application should print "No dog is found" and go back to the main menu.

3) Adopt a dog

The operation will ask for an identifier for a dog to be adopted and then the dog will be found in the hash table. The operation will then ask for a leave date to set the leave date of the dog. An example is provided below where the input is shown in bold. The dog is not found, then the application should print "No dog is found" and go back to the main menu. If the dog is already adopted, then the application should print "Dog is already adopted!" and go back to the main menu.
