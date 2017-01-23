# movie-review-and-rate
This is a project that use basic machine learning methods to predict movie's rate based on reviews.
It takes known movie reviews and splits the reviews into single words.
Assign each word with average rate value. (Each review has a rate, and the words in the review are assigned with this rate value. If the word shows up in different reviews, then this word is assigned with the average value of rates of those reviews containing this word.)
Then, for each new movie, take its review and split the review into single words.
Find the average value of the rates of words in this review, and assign it as the predicted rate for this movie. 
