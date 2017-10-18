#############################################################
##  In this tutorial, we are going to learn to assess the 
## goodnes of fits of models and to compare models.
## We are going to do this both with classical statistics (Anova) and
## with modern cross-validation approaches.

# We are now going to practice doing the statistics for linear models using the F-statistic.
library(car)

# Remember the job prestige data has a mixture of numeric predictors (income, education, women) and factors (group)

# Always take a peak at the data and look at the sample size
head(Prestige)
nrow(Prestige)

# Always visualize your data
scatterplotMatrix(~ prestige + log2(income) + education + women | type, data=Prestige, by.group=TRUE, id.n=0,
                  smooth=FALSE, col=gray(c(0,0.5,0.7)))

# Our favorite model is an ANOCOVA where type as a factor and education and log(income) as covariates  
prestige.mod <- lm(prestige ~ education*type + log2(income)*type,
                      data=Prestige)
summary(prestige.mod)


################################
# Exercise 1
# Statistics on models and Parameters.
# From Tutorial 4 Exercise 3:
# For the prestige.mod  you calculated SSerror, SStotal and from those R2 and R2 adjusted.
# First copy and paste that code over here.
# Second, add the calculation for F.
# Finally, you should also estimate the probability by using the pf() command.  To calculate p you will need the degrees of freedom.




#######################################
# Type I and II ANOVA
#######################################

# The anova command (fom the stats library) shows sequential F values. This hypothesis
# testing is sometimes called a Type I anova. In a Type I ANOVA, also called a sequential
# ANOVA, a series of models are fit, and the *difference* in sum-of-square error between
# each model is reported in the summary. Examine the table that's printed out after
# running a sequential ANOVA:

anova(prestige.mod)

# The "Sum Sq" column in the table above is *difference* in model sum-of-squares (SSerr) for several
# different models. The first row is a model that just predicts prestige from education,
# which can be written (prestige ~ education). The "Sum Sq" column for this row shows
# the sum-of-squares error of a model that just uses the overall mean, also called SStotal,
# minus the sum-of-squares error of the model prestige ~ education.
# Likewise, the second row shows the difference in the sum-of-squares error between
# a the model prestige ~ education and the model prestige ~ education + type.
# Check out section 4.4.3 of the blue Fox book for more information.

# Sequential F values are "out-of-favor" ... It is better to look at type II anovas.  The function
# Anova() - with a capital A (from the car library) performs these tests.  In these tests, a model
# that includes all regressors is compared to a model that includes all other regressors but one. (It
# is a bit more complicated when interactions are involved)
#
# For more information on Type I/II/III ANOVA, check out sec 4.4.4 of blue Fox or this explanation:
#    https://mcfromnz.wordpress.com/2011/03/02/anova-type-iiiiii-ss-explained/
Anova(prestige.mod)

# An ANOVA procedure can be used to test the significance of any two models (two alternative hypotheses)
# Here we'll compare the model prestige ~ education + log2(income) + type to a model with only
# an intercept term
prestige.mod.1 <- lm(prestige ~ education + log2(income) + type, data=na.omit(Prestige)) # full model
prestige.mod.0 <- update(prestige.mod.1, . ~ 1) # intercept only
anova(prestige.mod.0, prestige.mod.1) # compare models

#########################################
# EXERCISE 2
#
# What does the F value in the anova output corresond to? Check to see if it is the same. Hint: the F value
# output of ANOVA is for comparison of the model prestige ~ education + log2(income) + type to a
# model with only an intercept. What do you know about the output of summary(prestige.mod.1)?
#########################################


### End of Exercise 2.

# One can also test the effect of one additional parameter
prestige.mod.0inc <- update(prestige.mod.1, . ~ . - log2(income))
anova(prestige.mod.0inc, prestige.mod.1) # compare models


#########################################
# EXERCISE 3
#
# What does this F value correspond to?  Give two other ways of
# obtaining it. One way is to explore the output of a Type II ANOVA using
# on prestige.mod.1. Which model comparison does the matching F value
# correspond to?
#########################################


### End of exercise 3

# More generally you can use the anova command to compare two nested models
prestige.mod.1 <- lm(prestige ~ education + log2(income) + type,
    data=na.omit(Prestige)) # full model
prestige.mod.ed  <- lm(prestige ~ education, data=na.omit(Prestige))
(prestige.mod.ed.sum <- summary(prestige.mod.ed))

anova(prestige.mod.ed, prestige.mod.1)

######################  Done with Classical Model Validation #########

# We are now going to perform a 10-fold cross validation on the prestige
# data frame to get our own value of R2.

# First we randomly shuffle the data and omit na rows.
n.folds <- 10
my.Prestige <-na.omit(Prestige[sample(nrow(Prestige)),])

# Next, we create 10 equally size folds
folds <- cut(seq(1,nrow(my.Prestige)),breaks=n.folds,labels=FALSE)

########################################################
#   Exercise 4.  Complete the following loop to get n.folds value
# of cross validated R2 (one for each fold) for the full model and the model without Education compared to
# the zeroth order model.  Compare the mean of those cv-R2 to R2adj and use the SE of
# those estimates to asses whether the full model performs better.  


#  END of Exercise 4.

###################################
# Cross-validation with resampling to test a particular hypothesis.
###################################
# Our second example is the resampling example from the book.
# In this case we are interrested in determining whether a model for salary prediction fitted on men works for women as well.
library(car)
set.seed(12345) # to reproduce results in the text

# Let's look at the data format
some(Salaries)
nrow(Salaries)

# let's relevel the factor rank
Salaries$rank <- relevel(Salaries$rank, ref="AsstProf")

# Making a table to see how many subjects in each category
# xtabs make a table and ftable "flattens" the table
ftable(x1 <- xtabs(~ discipline + rank + sex, data=Salaries))
round(100*ftable(prop.table(x1, margin=c(1, 2))), 1) # % m and f

# We are plotting the data
library(lattice)
xyplot(salary ~ yrs.since.phd | discipline:rank, group=sex,
  data=Salaries, type=c("g", "p", "r"), auto.key=TRUE)

bwplot(salary ~ discipline:sex | rank, data=Salaries,
    scales=list(rot=90), layout=c(3, 1))

# Generate a model for Males only
fselector <- Salaries$sex == "Female" # TRUE for females
salmod <- lm(salary ~ rank*discipline + yrs.since.phd, data=Salaries,
    subset=!fselector) # regression for males
    
# predictions for females:
femalePreds <- predict(salmod, newdata=Salaries[fselector, ])
(meanDiff <- mean(Salaries$salary[fselector] - femalePreds))

# Let's do a bootstrap to see how often we could get this result
set.seed(8141976) # for reproducibility
fnumber <- sum(fselector) # number of females
n <- length(fselector) # number of observations
B <- 999 # number of replications
simDiff <- numeric(B) # initialize vector with B entries
for (j in 1:B){
    sel <- sample(1:n, fnumber) # random sample of nominated 'females'
    m2 <- update(salmod, subset=-sel) # refit regression model
    simDiff[j] <- mean(Salaries$salary[sel]
        - predict(m2, newdata=Salaries[sel, ])) # compute mean diff.
    }
    
# Calculate the p-value    
(frac <- round(sum(meanDiff > simDiff)/(1 + B), 3))

# Plot the histogram
hist(simDiff,
   main=paste("Histogram of Simulated Mean Differences\np-value =",
       frac),
   xlab="Dollars")
abline(v=meanDiff, lty="dashed")



#######################################
# Our last example examines overfitting.
#######################################

# We are now going to do an example with data from the Theunissen lab.
# In the data, we quantify the "timbre" of a musical instrument with the timbre
# column, and various acoustic features of the sound in the columns labeled
# sound.1, sound.2, etc. 

# First, change this path to the path where the file mds1PCA40.txt lives:
setwd('/Users/frederictheunissen/Documents/Classes/Psych 102/Fall 15')

# Then read the file and print out the number of rows
Timbre <- read.table('mds1PCA40.txt')
(n.inst <- nrow(Timbre))

# Check out a summary of the data. It's all numerical! 
summary(Timbre)

######################################
# EXERCISE 5
# Use Scatter plot matrix to visualize the data.  Use only the first 3 sound features, specifically
# sound.1, sound.2, and sound.3.
######################################

### End of 5


# We are now going to predict timbre and keep track of R-square values as a function of the number of parameters.

Rvals <- numeric(40)
Rvals.adj  <- numeric(40)
timbre.mod <- lm(timbre ~ sound.1, data=Timbre)
(timbre.sum <- summary(timbre.mod))
Rvals[1] <- timbre.sum$r.squared
sserror <- sum(timbre.mod$residual^2)
mean.timbre <- mean(timbre.mod$model$timbre)
sstotal <- sum((timbre.mod$model$timbre - mean.timbre)^2)
dferror <- timbre.mod$df.residual  # n - k -1
dftotal  <- length(timbre.mod$fitted.values)-1 # n - 1
Rvals.adj[1]  <- 1- ((sserror/dferror)/(sstotal/dftotal))

i <- 2
timbre.mod <- update(timbre.mod, sprintf(". ~ . + sound.%d", i))
timbre.sum <- summary(timbre.mod)
Rvals[i] <- timbre.sum$r.squared
sserror <- sum(timbre.mod$residual^2)
dferror <- timbre.mod$df.residual  # n - k -1
Rvals.adj[i]  <- 1- ((sserror/dferror)/(sstotal/dftotal))


################################################
# EXERCISE 6
# Compute and plot the R2 (obtained from the model) and the adjusted R square (as a red line) as a function of the number of sound parameters
# used to model timbre perception.  To do this, you can use the code above inside of a
# for loop, which iterates 40 times because there are 40 sound predictors.
################################################


################################################
# EXERCISE 7
# Calculate by "hand" the R-square obtained for a model with 3
# sound parameters. Hint: You have done this on your previous tutorial. Use
# the $residuals of the model timbre ~ sound.1 + sound.2 + sound.3.
###############################################


###############################################
# EXERCISE 8
# Using the resampling (bootstrapping) example above and a model with 3 sound parameters:
#  1) Randomly divide the sound instruments into a "fitting" and "validation" data set
#  2) Fit a linear model on the "fitting" data set.
#  3) Predict the prestige of the data points in the "validation" data set using the linear
#     model you fit on the "fitting" data set, report the R2. Hint: use the predict(..) function
#     with data = the fitting data set.
#  4) Repeat 1-3 for models that include an increasing number of sound features. The exercise
#     started with a model trained on 3 features, but combine the code you wrote to do 1-3 with
#     code from exercise 4 to loop through models that increase in the number of sounds they
#     utilize as predictors. The goal is to determine the "generalization" performance of each
#     model. Generalization performance is defined here as the R2 of model predictions on the "validation"
#     data set, when that model has been trained on the "fitting" data set.
#
# Suggestion: use 10 data ponts for a validation data set but note that you will then have n-10 rows
# in your data set for fitting model parameters.
###############################################



