Yair Andrew Gross
12/07/2020

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
However, for use with this project, the output has been changed:

	1 - compressive strength > 40 MPa
	0 - compressive strength <= 40 MPa


Included files:

concrete_train.txt:
	Training data, normalized and formatted for use with the BPNN program.
	It includes 780 labeled samples.
	
concrete_test:
	Testing data, also normalized and properly formatted for use with the BPNN.
	Includes 250 labeled samples.
	Original dataset was shuffled randomly before being split into training and testing sets.
	
concrete_init:
	Initial (pre-trained) weights that I used for testing.
	Weights were chosen using Xavier initialization, which is generally considered 
	effective in networks using a sigmoid transfer function. More on that here:
	https://medium.com/@shiyan/xavier-initialization-and-batch-normalization-my-understanding-b5b91268c25c
	
