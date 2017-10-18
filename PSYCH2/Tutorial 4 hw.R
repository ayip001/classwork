# In the fourth tutorial we are going to practice a 2-way ANOVA with interaction
# and calculate some values of Goodness of Fit using R2.

# We are getting read of stars on our reports
options(show.signif.stars=FALSE)

# Load the car library
library(car)
# Load the effects library
library(effects)


###################################
# Multi-way ANOVA: lm() can also be used with multiple factors and interactions
# Background reading: “Models with Many Factors: Multiway ANOVA” , page 166, blue Fox book
###################################

# Let's now look at a new data set and do a 3x2 two-way ANOVA with interaction
set.seed(123456) # to reproduce the results in the text
some(Moore)  # sample 10 rows

# In the Moore data set a score of conformity measures the number of times (out of 40)
# that a subject will change their mind and agree with the partner.  The fscore and
# fcategory measures the subject’s authoritarianism, in number (fscore) and factor
# (fcategory) form. 

# This is the data size
nrow(Moore)

# Reorder the fcategory and partner.status so that “low” gets included as the 
# intercept in the linear models we will fit:
Moore$fcategory <- factor(Moore$fcategory, levels=c("low", "medium", "high"))
Moore$partner.status <- relevel(Moore$partner.status, ref="low")

# Now we’re going to look at the joint relationship between two factors. A “contingency
# table” shows how many data points are in each pair of levels, and can be created
# using the xtabs command:
xtabs(~ fcategory + partner.status, data=Moore)

# In this table, the upper right number is the number of samples that have
# fcategory=low, partner.status=low, and the lower right shows how many data
# points have fcategory=high, partner.status=high

# In the same way we can compute the number of data points for each pair of levels,
# we can compute the mean and standard deviation of conformity for each pair of levels
# This is just like a contingency table, with the number samples replaced by the
# mean (or sd) of the samples in that group.

# The mean conformity table (remember this for exercise 1.3)
with(Moore, tapply(conformity,
                   list(Authoritarianism=fcategory,
                        "Partner's Status"=partner.status),
                   mean))
# The standard deviation table
with(Moore, tapply(conformity,
                   list(Authoritarianism=fcategory,
                        "Partner's Status"=partner.status),
                   sd))

# Make a nice plot that shows the ranges of values that conformity takes
# on given each (fcategory, partner.status) combination
boxplot(conformity ~ fcategory:partner.status, data=Moore,
        xlab="Condition", ylab="conformity")
abline(v=3.5, lty="dashed")



###############################
# EXERCISES
###############################

# Do the ANOVA on the Moore dataset - first with interactions between fcategory
# and partner.status:
mod.moore.1 <- lm(conformity ~ fcategory*partner.status, data=Moore)
summary(mod.moore.1)

# Then train a model without interactions:
mod.moore.2 <- lm(conformity ~ fcategory + partner.status, data=Moore)
summary(mod.moore.2)

#############################
# EXERCISE 1
#   1) How many coefficients are in mod.moore.1, including intercept?
#   2) How many degrees of freedom (df) does the model have and how is that calculated?
#   3) Calculate the mean of each group from the coefficients. 
#############################
coef(mod.moore.1) 
summary(mod.moore.1)
# 1) 5
# 2) 39 DF : total number of data minus total number of parameters -> 45-6=39
ex1.para0 <- 8.9000
ex1.para1 <- -1.6500
ex1.para2 <- 3.7250
ex1.para3 <- 8.5000
ex1.para4 <- -1.4772
ex1.para5 <- -9.2678

ex1.para0.para3 <- ex1.para0 + ex1.para3
ex1.para0.beta1 <- ex1.para0 + ex1.beta1
ex1.para0.para2 <- ex1.para0 + ex1.para2
# ex1.para0.para3 = 17.4000  #this is partner status group
# ex1.para0.para1 = 7.2500   #this is Authoritarianism-medium group
# ex1.para0.para2 = 12.625   #this is Authoritarianism-high group

# 3) they match the conformity table generated earlier.

###########################
#  EXERCISE 2
#     1) How many coefficients are in mod.moore.2, including intercept?
#     2) How many degrees of freedom (df) does the model have?
#     3) Calculate the means (predictions) obtained for this model Do they match the
#         mean conformity table you generated earlier? Why not?
############################
coef(mod.moore.2) 
summary(mod.moore.2)
# 1) 3
# 2) 41 DF
ex2.b0 <- 10.1977
ex2.b1 <- -1.1760
ex2.b2 <- -0.0808
ex2.b3 <- 4.6066

ex2.b0.b3 <- ex2.b0 + ex2.b3
ex2.b0.b1 <- ex2.b0 + ex2.b1
ex2.b0.b2 <- ex2.b0 + ex2.b2
ex2.b0.b3 <- ex2.b0 + ex2.b3
ex2.b0.b1.b3 <- ex2.b0 + ex2.b1 + ex2.b3
ex2.b0.b3.b3 <- ex2.b0 + ex2.b3 + ex2.b3

# Let's make interaction plot with this data set. Your GSI can explain to you the
# syntax of this command.
with(Moore, {
  interaction.plot(fcategory, partner.status, conformity, type="b",
                   pch=c(1, 16), cex=2, ylim=range(conformity), leg.bty="o")
  points(jitter(as.numeric(fcategory), factor=0.5), conformity,
         pch=ifelse(partner.status == "low", "L", "H"))
})


#####################
# Now we’re going to look at the statistics of model parameters and residuals
######################

# We’re going to go back to the prestige model - in case you need to re-fit it,
# run this command:
prestige.mod.full <- lm(prestige ~ education*type + log2(income)*type, data=Prestige)
prestige.mod.noEd <- lm(prestige ~ log2(income)*type, data=Prestige)

 ############################
# EXERCISE 3
# 	For the prestige.mod.full (the ANOCOVA with interactions)
#          
# Calculate by hand (meaning with R):
# R2 and R2ajd to measures the goodness of fit of this model relative to
# the zeroth order model (the prediction for prestige given by its mean)
# You will use the equations given in the lecture and you
# should also use the objects of the model.  In particular:
#  prestige.mod.full$residual are the predictions-actual
#  prestige.mod.full$model$prestige are the values of prestige used.
# 
# Compare with the values given in the summary of the model.


# You can also check this wiki page:
#	https://en.wikipedia.org/wiki/Coefficient_of_determination#Definitions
#
#
############################
summary(prestige.mod.full)
sserror <- sum(prestige.mod.full$residual^2)

# Now compute the SStotal
mean.prestige <- mean(prestige.mod.full$model$prestige)
sstotal <- sum((prestige.mod.full$model$prestige - mean.prestige)^2)

rsquare <- (sstotal-sserror)/sstotal
dfmodel <- length(prestige.mod.full$coefficients)-1
dferror <- prestige.mod.full$df.residual
fvalue <- ((sstotal-sserror)/dfmodel)/(sserror/dferror)

# This will return the probability
pf(fvalue, dfmodel, dferror, lower.tail = FALSE)
# Also check your results with the sequential anova table using the
# anova() command.

anova(prestige.mod.full)



############################
# EXERCISE 4
# 	Compare the prestige.mod.full to prestige.mod.noEd
#          
# Calculate by hand (meaning with R):
# R2 and R2ajd that you would get to quantify the increase in goodness of
# fit of the full model relative to the model without education.
# 
summary(prestige.mod.full)
summary(prestige.mod.noEd)

# R2_full = 0.871
# R2adj_full = 0.8595
# R2_noEd = 0.8221
# R2adj_noEd = 0.8124
#because the higher the R-squared, the better the model fits the data. So the full model is overall better 
#than the model without education (both R2_full and R2adj_full are larger than their counterparts in the model without education)

