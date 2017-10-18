# In this second tutorial, we are going to learn about the lm() command in R.  Much of the tutorial is from the Fox Chapter 4.

# We are getting read of stars on our reports
options(show.signif.stars=FALSE)

# Load the car library
# install.packages("car")
library(car)

# Examine the Davis data file
head(Davis) # first 6 rows
nrow(Davis)

# Show a scatter plot of the data
scatterplot(weight ~ repwt, data=Davis, smooth=FALSE, id.n=1)

# Perform the bi-variate regression
davis.mod <- lm(weight ~ repwt, data=Davis)
davis.mod
summary(davis.mod)

# Exercise 1. Calculate the Coefficients of this model using the equations for bi-variate linear regression.  
# Hint you can get rid of NAs by using the index of good entries using the following two lines.
attach(Davis)
idxgood <- (!is.na(weight)) & (!is.na(repwt))


mw <- mean(weight[idxgood])  # The mean weight
mrw <- mean(repwt[idxgood])  # The mean reported weight
b <- sum((repwt[idxgood]-mrw)*(weight[idxgood]-mw))/sum((repwt[idxgood]-mrw)^2)
a <- mw - b*mrw

detach(Davis)

# Get confidence intervals for the parameters
confint(davis.mod)


# We are now going to update the model to delete the outlier
davis.mod.2 <- update(davis.mod, subset=-12)
summary(davis.mod.2)
# This is a good way to compare the coeffiencts of the two models
cbind(Original=coef(davis.mod), NoCase12=coef(davis.mod.2))

# We are now going to look at a example of multiple regression
head(Prestige)
nrow(Prestige)

# Always look at the data first... The scatterplot is very nice
scatterplotMatrix(~prestige + income + education + women, span=0.7, data=Prestige)

# The relationshipt to income is not very linear. Let's try:
scatterplotMatrix(~prestige + log2(income) + education + women, span=0.5, data=Prestige)

# Now we are ready for the model
prestige.mod <- lm(prestige ~ education + log2(income) + women,
    data=Prestige)
    
summary(prestige.mod)

# Exercise 2.  Calculate the bivariate regression coefficients (use lm()).  
# Compare them to the multivariate coefficients by making a table using cbind. 
# Ignore the intercept.

prestige.mod.edu <- lm(prestige ~ education, data=Prestige)
prestige.mod.inc <- lm(prestige ~ log2(income), data=Prestige)
prestige.mod.wom <- lm(prestige ~ women, data=Prestige)
coeff.mod <- coef(prestige.mod)
coeff.edu <- coef(prestige.mod.edu)
coeff.inc <- coef(prestige.mod.inc)
coeff.wom <- coef(prestige.mod.wom)
cbind(Multivariate=coeff.mod[2:4],Bivariate=c(coeff.edu[2],coeff.inc[2],coeff.wom[2]))

# We are now going to learn about factors in R.
Prestige$type # This shows all the data for type
class(Prestige$type)  # This tells us that R considers type to be a factor
levels(Prestige$type) # And this shows the levels of the factor

# You can specify the levels into different orders
Prestige$type <- with(Prestige, factor(type,
    levels=c("bc", "wc", "prof")))
select <- c(1, 2, 35, 36, 61, 62) # a few rows
Prestige$type[select]  # a few values

# This is just to show that factors could be transformed into numbers or characters 
# (but warning the number transformation is not what you get from contrasts)
type.number <- as.numeric(Prestige$type)
type.number[select]
class(type.number)
type.character <- as.character(Prestige$type)
type.character[select]
class(type.character)
type.factor <- factor(type.character, levels=c("bc", "wc", "prof"))
type.factor[select]

# This shows you how contrasts work
(z <- factor(rep(c("a", "b", "c", "d"), c(3, 2, 4, 1))))
model.matrix(~ z)
contrasts(z)

#Exercise 4. What are the contrast for Prestige$type? First try to guess then and then use the contrasts command.

contrasts(Prestige$type)

# The following command gives you the mean of the prestige for each profession type

with(Prestige, tapply(prestige, type, mean))

#Exercise 5. Perform the linear regression with type as a factor.  What values do you expect for the coefficients?
# Verify your answer.

prestige.mod.type = lm(prestige ~ type, data=Prestige)
summary(prestige.mod.type)


