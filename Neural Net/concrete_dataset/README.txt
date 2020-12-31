Yair Andrew Gross
12/07/2020

--------------------------------------------------------------------------------

Concrete Compressive Strength Dataset:

This dataset models the compressive strength of concrete as a function of its components.
The original dataset, and accompanying data and references can be found here:
http://archive.ics.uci.edu/ml/datasets/Concrete+Compressive+Strength


There are eight input variables. The first seven are common concrete ingredients.
Each of these is given in units of [kg per m3 of mixture]. The last input variable
is the age of the micture, given in days (1~365). All input variables are listed below:

	Cement
	Blast Furnace Slag
	Fly Ash
	Water
	Superplasticizer
	Coarse Aggregate
	Fine Aggregate
	Age


The output variable of the original dataset is Concrete compressive strength (MPa).
However, for use with this project, the output variable has been changed from continuous
to binary such that:

	1 -> compressive strength > 40 MPa
	0 -> compressive strength <= 40 MPa

--------------------------------------------------------------------------------

Included files:

concrete_train.txt:
	Training data, normalized and formatted for use with the BPNN program.
	It includes 780 labeled samples.
	
concrete_test.txt:
	Testing data, also normalized and properly formatted for use with the BPNN.
	Includes 250 labeled samples.
	Original dataset was shuffled randomly before being split into training and testing sets.
	
concrete_init.txt:
	Initial weights that I used for testing.
	Weights were chosen using Xavier initialization, which is generally considered 
	effective in networks using a sigmoid or tanh transfer function. More on that here:
	https://medium.com/@shiyan/xavier-initialization-and-batch-normalization-my-understanding-b5b91268c25c
	
trained.5.100.txt:
	Network weights after training for 100 epochs with a learning rate of 0.5.
	Choices of learning rate and epoch number are explained below.
	
results.5.100.txt:
	Performance of the trained model above on the testing data.
	
--------------------------------------------------------------------------------	
	
Model and Training Parameters:

Hidden layer nodes (5):
	I chose to use 5 nodes in the hidden layer, in line with the general guideline of setting the number of nodes in
	the hidden layer in between the number of nodes in the input and output layers. This seemed to provide 
	relatively good performance, so I did not feel the need to change it.
	
Learning rate and number of epochs (0.5, 100):
	After trying several combinations of learning rates and numbers of epochs, I found that a learning rate
	of 0.5 with 100 epochs unexpectedly outperformed many of the other combinations, including one model
	that trained at a rate of 0.5 for 100 epochs and then 0.1 for another 100 epochs. There were other combinations,
	such as 0.1 learning rate for 500 epochs, which performed better, but the differences were too slight to be 
	worth the 5:1 difference in training time, in my opinion.
	

