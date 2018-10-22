# noisyDataSets


0. TAsk tracker:
https://docs.google.com/spreadsheets/d/1W_MhftameBd9GcWW4ijHH4FxmyGZbB80luRRTA8CBEw/edit?usp=sharing
Flow for 'Status': NEW -> IN PROGRESS -> TESTING(assign item to someone else at this stage) -> [Code review -> MERGE] -> COMPLETED

1. ML algorithms used to study noise:
    - Linear regression
    - Logistic regression
    - SVM
    - Clustering

2. Data-set and description:
   #ds101
   derived from: #ds100
   Used in algorithm: <Liner Regression?>
   <description of noise introduced>
   	ResultS:


_____________________________________________________________________________________________________________________________________________
99. Create noisy data-sets from the original data-set. Each data-set will vary in terms of noise type and noise amount
    We have identified the following ways to create noisy data-sets:
     -> Attribute noise
       ->> Alter the top 10% rows of sorted data-set by 0-10% 
       ->> Alter the last 10% rows of sorted data-set by 0-10% 
       ->> Alter the top 10% rows of sorted data-set by 10-25% 
       ->> Alter the last 10% rows of sorted data-set by 10-25% 
       ->> Alter the top 25% rows of sorted data-set by 10-25%
       ->> Alter randomly selected x% of data 
       ->> Alter each data point in the data-set by ~10% 
       ->> Alter each data point in the data-set by ~20%  
       ->> Add noise to data points in high concentrated regions of data 
       ->> Add noise to data points in low concentrated regions of data 
       ..etc
     -> Class noise
       ->> Change the output for top/bottom x% of the data-set
       ->> Change the output for randomly selected x% data in the data-set
       ..etc
     -> Add a small amount(%) of outliers to the data-set
     -> Add irrelevant feature
     -> Add Multicollinearity to features in data-set