# noisyDataSets

0. TAsk tracker:<br>
https://docs.google.com/spreadsheets/d/1W_MhftameBd9GcWW4ijHH4FxmyGZbB80luRRTA8CBEw/edit?usp=sharing <br>
Flow for 'Status': NEW -> IN PROGRESS -> TESTING(assign item to someone else at this stage) -> [Code review -> MERGE] -> COMPLETED

1. ML algorithms used to study noise:
    - Linear regression
    - Logistic regression
    - SVM
    - Clustering

2. Data-set and description:<br>
   #ds101<br>
   derived from: #ds100<br>
   Used in algorithm: <Liner Regression, etc> <br>
   <description of noise introduced><br>
   	ResultS:<br>

________________________________________________________________________________________________________________________________
99. Create noisy data-sets from the original data-set. Each data-set will vary in terms of noise type and noise amount<br>
    We have identified the following ways to create noisy data-sets:<br>
     -> Attribute noise<br>
       ->> Alter the top 10% rows of sorted data-set by 0-10% <br>
       ->> Alter the last 10% rows of sorted data-set by 0-10% <br>
       ->> Alter the top 10% rows of sorted data-set by 10-25% <br>
       ->> Alter the last 10% rows of sorted data-set by 10-25% <br>
       ->> Alter the top 25% rows of sorted data-set by 10-25%<br>
       ->> Alter randomly selected x% of data <br>
       ->> Alter each data point in the data-set by ~10% <br>
       ->> Alter each data point in the data-set by ~20%  <br>
       ->> Add noise to data points in high concentrated regions of data <br>
       ->> Add noise to data points in low concentrated regions of data <br>
       ..etc<br>
     -> Class noise<br>
       ->> Change the output for top/bottom x% of the data-set<br>
       ->> Change the output for randomly selected x% data in the data-set<br>
       ..etc<br>
     -> Add a small amount(%) of outliers to the data-set<br>
     -> Add irrelevant feature<br>
     -> Add Multicollinearity to features in data-set<br>
