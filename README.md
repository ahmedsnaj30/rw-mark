# Random-Writer
Analyze transitions between a fixed number of characters (k-grams) in a piece of text, and create a random writer that could randomly generate text that would come next using the Markov model. Utilized the discrete distribution of frequencies (character’s frequency / k-gram frequency) with the Mersenne Twister Engine to construct a randomly generated string of any length given by the user. 

Commands:\
``make``\
``./TextWriter <k-order> <length> < tomsawyer.txt``

Order of 6:\
![order6](https://user-images.githubusercontent.com/70961105/173454531-aa717347-249c-4d29-8e74-98a3a489d617.png)

Order of 11:\
![order11](https://user-images.githubusercontent.com/70961105/173454591-a20b23b5-4838-415b-a73d-ec15f984d4e8.png)
