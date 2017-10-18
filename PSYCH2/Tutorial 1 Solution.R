# Tutorial 1 - Learning about loops, graphics and a little exercise on SEM

# Define a vector x (a one dimensional array that has 10 elemens)

x <- array(0,10)
t <- seq(1,10)

# Use a for loop to change the value of x. Here i is the "index" and it takes values from 1 to 10
for (i in 1:10) {
x[i] <- i*3
}

plot(t, x)

# We can generate 100 samples from a normal distribution with mean 100 and standard deviation 10

xSamp <- rnorm(100,mean=100, sd=10)
meanSamp <- mean(xSamp)

# Exercise 1. Check the values of xSamp, draw a histogram (hist function), show the mean on the histogram as a dashed vertical line (abline)

hist(xSamp)
abline(v=meanSamp, lty="dashed")

# Exercise 2. Write a loop to generate 100 samples from the same normal distribution (each of 100 data points) and save the sample mean in an array

sampMeans <- array(0,100)
for (i in 1:100) {
	sampMeans[i] <- mean(rnorm(100,mean=100, sd=10))
	}
	
# Exercise 3. On a new window (dev.new()). Display the distribution of sample mean in a histogram and show the mean of means as a vertical dashed line. Compare to the histogram of samples. 

hist(sampMeans)
abline(v=mean(sampMeans), lty='dashed')

# Exercise 4. Calculate the standard deviation (sd) of this DOSM. Does the number agree with the theoretical value?

sem <- sd(sampMeans)

# Exercise 5. Use the arrows command to draw an arrow showing the sem.

arrows(mean(sampMeans)-sem, 20, mean(sampMeans)+sem, 20, code=3)

# Exercise 6.  Using a new "for loop" calculate the sample mean for samples of 10,20,50,100,200,500,1000 sample size

sampN <- c(10,20,50,100,200,500,1000)
sampMeans <- array(0,7)

for (i in 1:7) {
	sampMeans[i] <- mean(rnorm(sampN[i],mean=100, sd=10))
	}


# Exercise 7. Now try doing this using the sapply syntax above. It's okay to rotely copy it at this point. Slowly learning to extend things is the way to go.

sampMeans[1:7] <- sapply(sampN,function(x) mean(rnorm(x,mean=100,sd=10)))

# Exercise 8. On a new plot, plot you sample mean as a function of sample size.
# Add three curves to your plot that correspond to the theoretical mean (solid line) and the range of 95% confidence for the sample mean (two dotted lines)

plot(sampN,sampMeans,xlim=c(-30, 1030), ylim=c(95.5, 105.5),type='b')
upMeans <- 100 + 2*(10/sqrt(sampN)) 
lowMeans <- 100 - 2*(10/sqrt(sampN))
abline(h=100)
lines(sampN,upMeans,lty='dashed')
lines(sampN,lowMeans,lty='dashed')


	