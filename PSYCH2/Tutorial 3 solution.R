# In this third tutorial, we are going to continue to learn about the lm() command in R. 
# This tutorial is adapted from the Fox Chapter 4.

# We are getting read of stars on our reports
options(show.signif.stars=FALSE)

# Load the car library
library(car)

# The linear model can be use for bi-variate regression
# Examine the Davis data file
head(Davis) # first 6 rows
nrow(Davis)

# Show a scatter plot of the data
scatterplot(weight ~ repwt, data=Davis, smooth=FALSE, id.n=1)

# Perform the bi-variate regression
davis.mod <- lm(weight ~ repwt, data=Davis)
davis.mod
summary(davis.mod)

###########################################
# The lm() can be used for multiple regression
# We are now going to look at a example of multiple regression
head(Prestige)
nrow(Prestige)

# We used the scatter plot command to look at the data and decided to use log2(income):
scatterplotMatrix(~prestige + log2(income) + education + women, span=0.7, data=Prestige)

# Now we are ready for the model
prestige.mod <- lm(prestige ~ education + log2(income) + women,
    data=Prestige)
    
summary(prestige.mod)

# How do we visualize the fit?
# We can look at the predictions versus the actual

plot(fitted(prestige.mod),Prestige$prestige)

# Exercise 1. Add a y=x line to your plot using the abline command
abline(a=0, b=1)

# Try some fancier plots (See chapter 1)
avPlots(prestige.mod)

residualPlots(prestige.mod)

# The plot command also works
plot(prestige.mod)

###########################################
# The lm() can also be used predictor variables that are factors (also known as categorical or nominal variables).  If we only have one variable we are doing a one-way ANOVA. If the variable has two-levels it is a t-test. 

# The categorical variables are transformed into numeric variables called "contrasts".  You need k-1 contrast variables to code k levels. But remember that the linear model as j+1 parameters where j is the number of variables.  

Prestige$type # This shows all the data for type
class(Prestige$type)  # This tells us that R considers type to be a factor
levels(Prestige$type) # And this shows the levels of the factor

# This shows the contrasts for type
contrasts(Prestige$type)

# The mean values for each factor in type
with(Prestige, tapply(prestige, type, mean))

# We can now do a one-way ANOVA
prestige.mod.type = lm(prestige ~ type, data=Prestige)
summary(prestige.mod.type)

# This is another example from the text for the one-way anova

set.seed(1234) # to reproduce results in the text

some(Baumann) # sample 10 observations
nrow(Baumann)
xtabs(~ group, data=Baumann)
with(Baumann, tapply(post.test.3, group, mean))
with(Baumann, tapply(post.test.3, group, sd))
# The next command makes a nice plot
plot(post.test.3 ~ group, data=Baumann, xlab="Group",
     ylab="Reading Score")
baum.mod.1 <- lm(post.test.3 ~ group, data=Baumann)
summary(baum.mod.1)

# You can also change your reference
summary(update(baum.mod.1, . ~ . - group +
    relevel(group, ref="DRTA")))

## lm() can deal with a mixture of factors and numerical predictors.
# This is also called ANACOVA: analysis of covariance.  In this first example we are not modeling any interactions    

# First let's take a look at the data

scatterplotMatrix(~ prestige + log2(income) + education + women | type, data=Prestige, by.group=TRUE, id.n=0,
smooth=FALSE, col=gray(c(0,0.5,0.7)))

# Now we are doing the model that includes type and excludes the percent of women
prestige.mod.1 <- update(prestige.mod, ~ . - women + type)
summary(prestige.mod.1)

# You can estimate the adjusted means: the means when the mean of the covariates are taken into account.
library(effects)
effect("type", prestige.mod.1)

# You can use the objects() to look at all the things that are stored in the model structure
objects(prestige.mod.1)

# We can now plot the fitted values vs actual values.  We are getting them from the model structure because of missing arguments...

scatterplot(prestige.mod.1$model$prestige, prestige.mod.1$fitted.values, groups=prestige.mod.1$model$type)
abline(a=0,b=1)

# Exercise 2: On a separate figure plot the predictions that one would have obtained for each group without taking the proffession type into account. 
# In other words in the current model each group has its own intercept - replace that intercept by the average of the three intercepts
# What do you see?
# Hint: I used a "for" to loop through all the data and a "if" to determine which type but you can also do this using vector programming.

fitted.values.notype <- prestige.mod.1$fitted.values  # the copy of fitted values that I will change
cf <- prestige.mod.1$coefficients  # The coefficients of the model
intercept.average <- mean(c(cf[1], cf[1]+cf[4], cf[1]+cf[5])) # Average intercept

nvals = length(fitted.values.notype)

for (i in 1:nvals) {
	if (prestige.mod.1$model$type[i] == 'prof') 
		fitted.values.notype[i] <- fitted.values.notype[i] - (cf[1]+cf[4]) + intercept.average
		else if (prestige.mod.1$model$type[i] == 'wc')
		fitted.values.notype[i] <- fitted.values.notype[i] - (cf[1]+cf[5]) + intercept.average
		else	fitted.values.notype[i] <- fitted.values.notype[i] - cf[1] + intercept.average
		}

scatterplot(prestige.mod.1$model$prestige, fitted.values.notype, groups=prestige.mod.1$model$type)
abline(a=0,b=1)

# When I remove the different intercepts, I see on my plot that I am now underestimating the prestige of the Prof jobs (more below the y=x line).

# ############################################
# lm() can also be used for modeling interactions.  THis is a form of "linearization" of non-linear effects.  
# Always visualize your data
# Always visualize your data
scatterplotMatrix(~ prestige + log2(income) + education + women | type, data=Prestige, by.group=TRUE, id.n=0,
                  smooth=FALSE, col=gray(c(0,0.5,0.7)))

# Before looking at interactions, we are understanding how linear regression can be used to fit non-linear terms. This is done by adding "regressors".  K "predictors"  can be manipulated to generate many more (>K) "regressors".

# We can compare the model that predicts prestige with income and education as additive predictor variables with a model that also includes a multiplicative term.

prestige.mod.1 <- lm(prestige ~ education + income, data=Prestige)
prestige.mod.2 <- lm(prestige ~ income*education, data=Prestige)
summary(prestige.mod.1)
summary(prestige.mod.2)

library(effects)
plot(effect("income:education", prestige.mod.2))

# More generally one can fit a non-linear function with splines.
# Splines are piece-wise polynomial fits to function
library(splines)
prestige.mod.3 <- lm(prestige ~ ns(income, df=4), data=Prestige)
summary(prestige.mod.3)

# Let's display the effect.

plot(effect("ns(income, df=4)", prestige.mod.3))

# We are now going to do a ANACOVA demonstration with interaction
select <- c(1, 2, 35, 36, 61, 62) # a few rows

# The interaction term adds new variables in the models.  Interaction terms with factors are shown with :. R is smart and creates all the necessary additional terms.  Let's look at these:

model.matrix(~ type + education + education:type,
             data=Prestige)[select, ]

# There is more than one way to specify the equation the * is used for both the linear and the multiplicative term (interaction)  
prestige.mod.4a <- lm(prestige ~ education*type + log2(income)*type,
                      data=Prestige)
summary(prestige.mod.4a)

prestige.mod.4b <- lm(prestige ~ type*(education + log2(income)),
                      data=Prestige)
summary(prestige.mod.4b)

# Exercise 3.  Plot the result of this ANACOVA with interaction using the plot command and the effect command for education*type in model 4a.  Try also the leveragePlots() and residualsPlot(). Explain what you see.

plot(effect("education*type", prestige.mod.4a))

# Leverage plots are generalizations of Added value plots.
# In added value plots, the residuals of the pretictor variables 
# given all other variables are used to predict the residual of the predicted variable.

avPlots(prestige.mod.4a)
leveragePlots( prestige.mod.4a)

# Your basic residual plot
residualPlots( prestige.mod.4a)

