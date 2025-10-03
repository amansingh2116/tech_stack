# Transformers in PyTorch: Implementing a Shakespeare-Like Poetry Generator

Now that we've covered the basics of NLP and Transformer architecture, let's briefly outline what we'll be doing for the rest of the lesson. Our goal is to implement a Transformer model from scratch, focusing on generating Shakespeare-like poetry. We will train the model on the works of William Shakespeare, aiming to produce poetry that resembles his style.

## Objective
- Create a model capable of generating Shakespeare-like poetry.

## Training Data
- Works of William Shakespeare, a renowned English poet.

## Model Architecture
### Similarity to GPT Models
- Our model will have a similar architecture to the GPT models created by OpenAI.

### Differences from GPT Models
- **Model Size**: Our model will be much smaller, with significantly fewer parameters, making it more accessible and less resource-intensive to train.
- **Tokenizer Type**: We will use a character-level tokenizer instead of a subword tokenizer to simplify our implementation.
- **Focus on Understandability**: The model will prioritize clarity and educational value over performance.

## Implementation Details
- **Model Configuration**: Once the implementation is complete, we will be able to create an instance of the model and set various parameters, such as context window size.
- **Text Generation**: Using the trained model and a provided prompt, we can generate text that mimics Shakespeare's style, such as lines that could be spoken by characters like Romeo.

## PyTorch Refresh
Before we start working on the Transformer implementation, we'll have a quick demo to cover some essential PyTorch functions that we'll use.

The goal of this demo is to refresh your PyTorch knowledge. If you're already proficient with PyTorch, feel free to skip this section.

### Key PyTorch Functions
#### Creating Random Tensors
- `torch.rand`: Creates random tensors.
  - Example: `torch.rand(5)` creates a random vector with 5 elements.
  - Example: `torch.rand(5, 5)` creates a 5x5 random tensor.

#### Creating Tensors Filled with Ones
- `torch.ones`: Creates tensors filled with ones.
  - Example: `torch.ones(5)` creates a vector of size 5 filled with ones.
  - Example: `torch.ones(5, 5)` creates a 5x5 tensor filled with ones.

#### Creating a Sequence of Numbers
- `torch.arange`: Creates a tensor with a sequence of numbers.
  - Example: `torch.arange(10)` returns a sequence of numbers from 0 to 9.

#### Creating a Triangular Matrix
- `torch.tril`: Creates a lower triangular matrix.
  - Usage: First, create a tensor, then apply `torch.tril` to set zeros above the main diagonal.

#### Concatenating Tensors
- `torch.cat`: Concatenates multiple tensors.
  - Usage: Concatenate along rows by specifying `dim=0`.
    - Example: `torch.cat((tensor1, tensor2), dim=0)`
  - Usage: Concatenate along columns by specifying `dim=1`.
    - Example: `torch.cat((tensor1, tensor2), dim=1)`

#### Reshaping Tensors
- `torch.view`: Changes the shape of a tensor.
  - Example: `tensor.view(3, 4)` reshapes a vector into a 3x4 tensor.
  - Reverting Shape: Use view to convert a 2D tensor back into a vector.
    - Example: `tensor.view(12)` reshapes a 3x4 tensor into a vector of size 12.

These PyTorch functions are fundamental for manipulating tensors, which is a crucial skill in implementing and understanding neural network models like Transformers. Let's proceed to the implementation phase, where we will apply these functions in building our model.

## Preparing Data for a Transformer-Based Language Model
### Preparing Training Data for the Model
Before we start implementing our model, let's discuss how to prepare the training data.

This process involves several key steps to ensure our model can effectively learn to predict the next token in a sequence.

#### Key Steps in Data Preparation
1. **Implementing a Tokenizer**
   - Purpose: A tokenizer converts text into token IDs, which are numerical representations of the text.
   - We'll implement a tokenizer in PyTorch.

2. **Preparing the Training Dataset**
   - Goal: The model's goal is to predict the next token given part of an input dataset.
   - Example:
     - Given the phrase: "The core innovation of Transformers is the attention."
     - Input: "The" → Model predicts: "core"
     - Input: "The core" → Model predicts: "innovation"
     - Continue until the last input: "The core innovation of Transformers is the" → Model predicts: "attention"
   - Dataset Representation: Inputs and targets are part of the same phrase but are shifted by one position.
   - While the model sees token IDs during training, for clarity, we'll often refer to these as words.

### Training Process
- **Training Batches**: During each training iteration, we don't just use a single example. Instead, we use multiple random training examples to create a training batch.
- **Efficiency**: Using batches helps better utilize GPU resources, speeding up the training process.

In the next few videos, we will cover how to implement these steps in PyTorch, ensuring our model is well-prepared for training.

## Implementing a Tokenizer
In this demo, we will implement a tokenizer for our Transformer model.

This tokenizer will be character-based, meaning it will convert every character in an input string to a separate token.

### Setting Up the Environment
- **PyTorch Imports**: First, we add the necessary PyTorch imports.
```python
import torch
import torch.nn as nn
import torch.nn.functional as F
```
- **Device Setup**: We create a device variable assigned to "cuda" if a GPU is available. This allows us to move tensors and models to the GPU if available.
```python
# Use CUDA if available
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device: {device}")
```

### Loading the Dataset
- **Dataset Source**: We use a file called "tiny_shakespeare," which contains all of Shakespeare's plays combined into a single file.
- **Loading Text**: Using pathlib and the read_text method, we load the dataset into a text variable, which will be a long string containing all the Shakespeare plays.
```python
from pathlib import Path

text = Path('tiny-shakespeare.txt').read_text()
print(text[0:1000])
```

### Building the Tokenizer
#### Tokenizer Interface
- **Constructor**: Receives a vocabulary—a list of characters that the tokenizer can process.
- **Methods**:
  - `train_from_text`: Creates a tokenizer from the text.
  - `encode`: Converts a string into a list of token IDs.
  - `decode`: Converts a list of token IDs back into text.
  - `vocab_size`: Returns the size of the vocabulary.

```python
class CharTokenizer:
  def __init__(self, vocabulary):
    self.token_id_for_char = {char: token_id for token_id, char in enumerate(vocabulary)}
    self.char_for_token_id = {token_id: char for token_id, char in enumerate(vocabulary)}

  @staticmethod
  def train_from_text(text):
    vocabulary = set(text)
    return CharTokenizer(sorted(list(vocabulary)))

  def encode(self, text):
    token_ids = []
    for char in text:
      token_ids.append(self.token_id_for_char[char])
    return torch.tensor(token_ids, dtype=torch.long)

  def decode(self, token_ids):
    chars = []
    for token_id in token_ids.tolist():
      chars.append(self.char_for_token_id[token_id])
    return ''.join(chars)

  def vocabulary_size(self):
    return len(self.token_id_for_char)
```

#### Implementing the Tokenizer
- **train_from_text Method**:
  - Receives the text and extracts unique characters using the set method.
  - Converts these characters into a sorted list and passes them to the CharTokenizer constructor.
- **Constructor**:
  - **Mapping Creation**: Creates two maps—one for character-to-token ID and another for token ID-to-character.
  - **Process**: Iterates over the list of characters, assigning token IDs based on their position in the vocabulary.
- **encode Method**:
  - Iterates through each character in the input text, retrieves the corresponding token ID, and appends it to a list.
  - Converts the list of token IDs into a tensor using torch.tensor.
- **decode Method**:
  - Converts the tensor of token IDs into a list.
  - Iterates through the token IDs, retrieves the corresponding characters, and concatenates them into a string.
- **vocab_size Method**:
  - Returns the length of the vocabulary.

### Testing the Tokenizer
- **Creating an Instance**: We create an instance of our tokenizer and pass the entire training dataset to it.
```python
tokenizer = CharTokenizer.train_from_text(text)
```
- **Encoding and Decoding**:
  - Encode the string "Hello world" into a list of token IDs.
```python
print(tokenizer.encode("Hello world"))
```
  - Decode the token IDs back into the original string.
```python
print(tokenizer.decode(tokenizer.encode("Hello world")))
```
- **Vocabulary Size**: The vocabulary size is 65, indicating that our dataset contains 65 unique characters.
```python
tokenizer.vocabulary_size()
```
- **Character-to-Token Mapping**: Displays the mapping between characters and their corresponding token IDs.
```python
import pprint
pp = pprint.PrettyPrinter(depth=4)
pp.pprint(tokenizer.char_for_token_id)
pp.pprint(tokenizer.token_id_for_char)
```

With our tokenizer implemented, we can now start processing our dataset and proceed to build our model.

## Datasets and Data Loaders
### Handling Datasets in PyTorch
Now that we have a tokenizer, let's look into how to handle datasets in PyTorch. PyTorch provides two primary classes for working with datasets:

- **Dataset**: A class for loading and processing data.
- **DataLoader**: A class for iterating over samples in a PyTorch dataset.

### Working with the Dataset Class
To define a dataset, we first need to define a new class that inherits from the Dataset class imported from torch.utils.data. Let's explore how to implement a dataset that stores a list of samples and allows us to perform arbitrary transformations on them.

#### Implementing a Dataset Class
To implement the dataset, we need to implement three methods:

- **Constructor (__init__())**: Receives parameters—data to store and a transform to apply.
- **__len__() Method**: Returns the number of elements in the dataset.
- **__getitem__() Method**: Returns an item from the provided position, passed as the index parameter.

In this example, our dataset receives a list of samples and a function to transform each sample. The implementation of the __len__() method returns the number of samples in the list. In the __getitem__() method, we retrieve a sample using the provided index, apply the transformation, and return the transformed result. This simple dataset can be expanded to include loading data from external storage, applying complex transformations, and more.

#### Example Usage
To use the dataset implementation:

- **Creating an Instance**: Suppose we have a dataset of images. We create an instance of the custom dataset class, passing a list of images and a function to transform each image (e.g., resizing).
- **Accessing Data**: Use the __len__() method to get the number of samples or __getitem__() to get a specific sample.
- **Iteration**: We can iterate over samples in our dataset.

### Using DataLoader for Mini-Batches
In training a model, we typically don't use a single sample per training iteration, as this approach (stochastic gradient descent) doesn't efficiently utilize resources and leads to fluctuating training losses. Using the whole dataset (batch gradient descent) is impractical due to high computational costs and memory requirements.

#### Mini-Batches
Instead, models are often trained using mini-batches, where each training iteration uses a small subset of samples. This approach, known as mini-batch gradient descent, balances efficiency and stability in training.

#### DataLoader
To iterate over mini-batches from our dataset, we use the DataLoader class:

- **Creating a Dataset Instance**: Provides access to our data.
- **Creating a DataLoader Instance**: Facilitates iteration over the training data in batches.

We don't need to implement a custom type to use DataLoader. Simply create an instance of DataLoader, pass the dataset, and specify the batch size. Iterating over the DataLoader instance yields batches of data, which can be used for model training.

By using DataLoader and Dataset, we can efficiently manage data loading and processing, enabling smooth training of our models with PyTorch.

## Implementing a Data Loader
In this exercise, your goal is to implement a Dataset class in PyTorch, which is used to handle and process the data for training a transformer model. You'll also use a DataLoader to load batches of data from this dataset. Follow the steps below to complete the implementation based on the provided starter code.

### Implementing the Dataset Class
We need to implement three key functions in our dataset class.

1. **Constructor (__init__())**
   - Purpose: Assigns data and block_size to instance variables.
   - Code:
```python
class TokenIdsDataset(Dataset):
    def __init__(self, data, block_size):
        self.data = data
        self.block_size = block_size
```

2. **__len__() Method**
   - Purpose: Returns the number of training examples in the dataset, calculated as the length of the data tensor minus the block size.
   - Reason: This is because every position in the data tensor can be the beginning of a training example, except for the last few positions.
   - Code:
```python
def __len__(self):
    return len(self.data) - self.block_size
```

3. **__getitem__() Method**
   - Purpose: Retrieves a training example from the dataset.
   - Process:
     - Input: Fetches block_size number of tokens starting from the provided position.
     - Target: Fetches tokens shifted by one position compared to the input.
     - Safety Check: An assert statement ensures there are enough token IDs to fill the block.
   - Code:
```python
def __getitem__(self, pos):
    assert pos < len(self.data) - self.block_size

    x = self.data[pos:pos + self.block_size]
    y = self.data[pos + 1:pos + 1 + self.block_size]
    return x, y
```

### Using the Dataset
#### Tokenizing Text and Creating Dataset
- **Tokenizing**: Use the encode method on the tokenizer to tokenize the entire text.
- **Creating Dataset**: Use the tokenized text to create the TokenIdsDataset.
- Code:
```python
tokenized_text = tokenizer.encode(text)
dataset = TokenIdsDataset(tokenized_text, block_size=64)
```

#### Fetching Data
- **Fetching Input and Target**: Retrieve input and target for the first position in the dataset.
- **Converting to Text**: Use the decode method to convert token IDs back to text for verification.
- Code:
```python
x, y = dataset[0]
print(tokenizer.decode(x))
```

### Using DataLoader and RandomSampler
#### Creating DataLoader
- **Purpose**: Facilitates iteration over mini-batches from the dataset.
- **Setup**:
  - RandomSampler: Used to randomly sample data points with replacement.
  - DataLoader: Batches the data into mini-batches for efficient training.
- Code:
```python
from torch.utils.data import DataLoader, RandomSampler

sampler = RandomSampler(dataset, replacement=True)
dataloader = DataLoader(dataset, batch_size=2, sampler=sampler)
```

#### Fetching Mini-Batches
- **Fetching a Mini-Batch**: Use iter() and next() to get the first mini-batch from the DataLoader.
- **Examining Data**: Check the shape and content of the mini-batch.
- Code:
```python
x, y = next(iter(dataloader))
print(x.shape)
print(tokenizer.decode(x[0]))
print(tokenizer.decode(y[0]))
```

This setup allows us to efficiently manage and process data, preparing it for training in a neural network.

## Embeddings and Positional Layers in a Transformer-Based Language Model
### Lesson
### Downloads
### Building the Transformer Model
Now we will start building our model. We'll go through it step-by-step, learning how each part is structured, and gradually build it using PyTorch.

#### Step 1: Processing Input
- **Tokenization**: The input text is tokenized, converting each word into a token ID.
- **Word Embeddings**: Each token ID is then converted into a corresponding word embedding. After this step, we have a matrix of embedding vectors, each representing a token in the input.

#### Key Points About Word Embeddings
- **Dependence on Token IDs**: The word embeddings are solely dependent on the token IDs; the same token ID always produces the same word embedding vector.
- **Training**: These embeddings are not pre-defined but are learned during the training of our model.

#### Creating Embeddings
- **Vocabulary Size**: Set to 10,000 (arbitrary choice).
- **Embedding Vector Size**: Set to 75.
- **nn.Embedding**: A PyTorch class used to create embeddings. It requires the vocabulary size and embedding vector size as inputs.

#### Usage
- **Token IDs**: We obtain token IDs using a tokenizer, but for now, we use arbitrary IDs for illustration.
- **Embedding Layer**: Pass these token IDs to the nn.Embedding instance, which returns a tensor with vectors of size 75 (the embedding size).

#### Adding Positional Encoding
Before feeding the embedding vectors into the model, we add positional encoding:

- **Purpose**: Injects positional information into the word embeddings, helping the model understand the relative order of input tokens.
- **Positional Encoding Matrix**: A fixed matrix added to the word embeddings. This matrix does not depend on the input and provides consistent positional information.

#### Positional Encoding in Models
- **Training**: In some models, including ours, the values in the positional encoding matrix are learned along with other model parameters.
- **Fixed Formula**: In other large language models (LLMs), positional encodings are defined using a fixed formula and remain unchanged during training.

This step ensures that the model can interpret the sequential nature of the input data, which is crucial for understanding context and meaning in sequences.

## Softmax Function
### Lesson
### Downloads
### Understanding the Softmax Function
Before diving into the Transformer architecture, it's crucial to understand the Softmax function, as it will be used in several places when we implement our model.

#### What is Softmax?
- **Logits**: The raw output values from a neural network layer, which can be any numerical values.
- **Purpose**: Sometimes, we need to convert these logits into a probability distribution.

#### Why Use Softmax?
To create a probability distribution from logits, two conditions must be met:

- **Range**: Every logit value must be converted into a value between 0 and 1.
- **Sum**: The sum of all resulting values must equal one.

#### How Does Softmax Work?
- **Exponentiation**:
  - For each logit value, we calculate \( e^{\text{logit}} \).
  - This ensures all output values are positive since raising \( e \) (a positive number) to any power yields a positive result.
- **Normalization**:
  - **Sum Calculation**: Compute the sum of all exponentiated values.
  - **Division**: Divide each exponentiated value by the sum to ensure that all outputs sum to one.

#### Mathematical Representation
\[ \text{softmax}(x_i) = \frac{\exp(x_i)}{\sum_j \exp(x_j)} \]
For every output value, calculate the exponent and divide it by the sum of all exponents. The result is a probability distribution, often visualized using a histogram.

The softmax function represented in mathematical notation.

#### Properties of Softmax
- **Dominant Value Effect**: If one input value is significantly larger than the others, softmax assigns a high probability to this value, while the others receive probabilities close to zero.
- **Similarity Handling**: If multiple logits have similar values, softmax distributes probabilities more evenly among them.

## Calculating Attention
### Lesson
### Downloads
### Understanding the Attention Mechanism in Transformers
In this video, we will explore how the attention mechanism is implemented in Transformer models. The attention mechanism is crucial for refining the embedding vectors for each token using the context of other embedding vectors.

#### Overview of the Attention Block
- **Attention Block Function**: Computes attention scores and updates embedding values using these scores.
- **Components**: The attention block involves several steps, including calculating query, key, and value matrices and updating embedding vectors.

#### Step-by-Step Implementation
- **Query Matrix (Q)**
  - Calculation: Multiply the matrix of embedding vectors by another matrix \( W_Q \) to produce the query matrix (Q).
  - Notation: Represented as Q for simplicity, often visualized as an array of vectors.
- **Key Matrix (K)**
  - Calculation: Similar to Q, the key matrix (K) is obtained by multiplying the embedding vectors by matrix \( W_K \).
  - Concept: Queries can be seen as questions about other words, while keys provide answers.
- **Computing Attention Scores**
  - Similarity Check: Calculate the dot product between vectors in the Q and K matrices to determine the similarity.
  - Matrix Multiplication: Multiply the Q matrix by the transposed K matrix to get the attention scores.
- **Normalization with Softmax**
  - Purpose: Ensures all values are between 0 and 1 and sum to one.
  - Application: Apply the softmax function to each column of the resulting matrix.

#### Diagram of Operations
- **Steps Recap**:
  - Derive Q and K matrices from the input embeddings.
  - Compute attention scores via matrix multiplication and softmax.
  - Use these scores to update embedding vectors.
- **Value Matrix (V)**
  - Derivation: Similar to Q and K, the value matrix (V) is derived using another matrix \( W_V \).
  - Updating Embeddings: Multiply each vector in V by the corresponding attention scores to produce updated embeddings.

#### Final Diagram of the Attention Block
- **Complete Process**:
  - Compute Q, K, and V matrices.
  - Compute attention scores from Q and K.
  - Update embeddings using attention scores and V.

#### Multi-Head Attention
- **Purpose**: Multiple attention heads allow the model to learn different relationships between words in a sentence.
- **Process**: Each head performs similar calculations with different parameters, and the results are concatenated to form new embedding vectors.

#### Formula for Attention
From "Attention Is All You Need" Paper:
- **Components**: Uses Q, K, and V matrices.
- **Adjustment**: Includes a division by the square root of the dimension of the K matrix vector to prevent large attention scores.
- **Final Steps**: Apply softmax and multiply by V to compute the final output.

Understanding the attention mechanism is key to grasping how Transformer models process and generate text, enabling them to focus on relevant parts of the input sequence when making predictions.

## Masking
### Lesson
### Downloads
### Preventing Cheating in Transformer Training with Masked Multi-Head Attention
When training Transformer models, we convert parts of the training dataset into multiple training examples.

However, a problem arises because the model can "cheat" by looking ahead at the entire input when predicting the next word.

To prevent this, we need to modify the attention scores to ensure the model cannot access future tokens.

#### Solution: Masked Multi-Head Attention
To stop the model from "cheating," we implement a masking strategy:

- **Attention Matrix Adjustment**:
  - Problem: The model can see the next token while predicting it.
  - Solution: Update the attention matrix to mask out certain values.
- **Masking Strategy**:
  - Method: Assign all values below a certain diagonal to negative infinity.
  - Softmax Effect: The softmax function converts these negative infinity values to zeros, effectively ignoring them.
- **Implementation**:
  - Diagram Update: In our multi-head attention diagram, we add the masking step after matrix multiplication and before applying softmax.
  - Masked Multi-Head Attention: This approach is widely used in Transformer models, including GPT models.

By applying a triangular mask, we ensure that the model only considers current and previous tokens when making predictions, thus maintaining the integrity of the training process.

## Dropout Layer
### Lesson
### Downloads
### The Dropout Layer: An Overview
Before we start the implementation of our model, let's briefly revisit an important technique called the Dropout layer, which we will use throughout our implementation.

#### What is a Dropout Layer?
- **Function in Neural Networks**: In a feedforward neural network, each output from a previous layer is connected to all neurons in the next layer.
- **Purpose of Dropout**: The Dropout layer introduces randomness by setting a certain percentage of the inputs to zero during training. This percentage is usually specified as a hyperparameter.

#### How Dropout Works
- **Random Selection**: On each training iteration, different inputs are randomly selected and set to zero. This list of "disabled" inputs changes with each iteration.
- **Generalization**: By doing this, the model does not become overly reliant on specific features, which helps it generalize better to new, unseen data. This process reduces the risk of overfitting.

#### Training vs. Inference
- **During Training**: The Dropout layer is active, randomly disabling inputs to help generalization.
- **During Inference**: When the model is used for generating text or making predictions, the Dropout layer is disabled, ensuring that all features are fully utilized.

#### Implementation in PyTorch
- **Pre-built in PyTorch**: We do not need to implement the Dropout layer ourselves, as PyTorch provides a built-in implementation through the Dropout class.

The Dropout technique is a crucial component in training robust neural networks, especially when dealing with complex data and models. It ensures that the model does not overfit and can generalize well across different datasets.

## Implementing the Attention Block
### Lesson
### Downloads
### Building the Multi-Head Attention Block in PyTorch
In this video, we will build the multi-head attention block, a crucial component of the Transformer model, from scratch using PyTorch.

Download the Notebook(opens in a new tab)

#### Model Configuration
Before we start, we need to define a configuration for our model, containing hyperparameters that define its structure. This configuration is stored in a dictionary with the following parameters:

- **Vocabulary Size**: The number of unique token IDs supported by the tokenizer.
- **Context Size**: The maximum number of tokens the model can see at once.
- **Embedding Dimension**: The size of the embedding vectors.
- **Number of Heads**: The number of attention heads, each processing input independently.
- **Number of Layers**: The number of Transformer blocks in the model.
- **Dropout Rate**: The proportion of outputs set to zero in Dropout layers.
- **Use Bias**: A boolean indicating whether the linear transformations should include bias terms.

#### Configuration Dictionary
```python
config = {
  "vocabulary_size": tokenizer.vocabulary_size(),
  "context_size": 256,
  "embedding_dim": 768,
  "heads_num": 12,
  "layers_num": 10,
  "dropout_rate": 0.1,
  "use_bias": False,
}
config["head_size"] = config["embedding_dim"] // config["heads_num"]
```

#### Attention Head Implementation
To implement a single attention head, we define the AttentionHead class:

##### Attention Head Class
- **Constructor**:
  - Q, K, V Matrices: Used to convert input embedding vectors into Q, K, and V matrices.
  - Dropout Layer: For regularization.
  - Causal Attention Mask: Ensures the model cannot "cheat" by looking at future tokens.
- Code Implementation
```python
class AttentionHead(nn.Module):
  def __init__(self, config):
    super().__init__()
    self.Q_weights = nn.Linear(config["embedding_dim"], config["head_size"], config["use_bias"])
    self.K_weights = nn.Linear(config["embedding_dim"], config["head_size"], config["use_bias"])
    self.V_weights = nn.Linear(config["embedding_dim"], config["head_size"], config["use_bias"])
    self.dropout = nn.Dropout(config["dropout_rate"])
    casual_attention_mask = torch.tril(torch.ones(config["context_size"], config["context_size"]))
    self.register_buffer('casual_attention_mask', casual_attention_mask)

  def forward(self, input):
    batch_size, tokens_num, embedding_dim = input.shape
    Q = self.Q_weights(input)
    K = self.K_weights(input)
    V = self.V_weights(input)
    attention_scores = Q @ K.transpose(1, 2)
    attention_scores = attention_scores.masked_fill(
        self.casual_attention_mask[:tokens_num,:tokens_num] == 0,
        -torch.inf
    )
    attention_scores = attention_scores / ( K.shape[-1] ** 0.5 )
    attention_scores = torch.softmax(attention_scores, dim=-1)
    attention_scores = self.dropout(attention_scores)
    return attention_scores @ V
```

#### Testing the Attention Head
- **Input Tensor**: A random input tensor is used to check the implementation.
- **Output**: Verify that the output has the correct dimensions.
```python
input = torch.rand(8, config["context_size"], config["embedding_dim"])
ah = AttentionHead(config)
output = ah(input)
print(output.shape)  # Expected output: torch.Size([8, 256, 64])
```

#### Multi-Head Attention Implementation
To implement multi-head attention, we:

- Inherit from nn.Module.
- Create Multiple Heads: Instantiate multiple AttentionHead instances and store them in a ModuleList.
- Additional Linear Layer: Applies to each embedding vector.
- Dropout Layer: For regularization.

##### Multi-Head Attention Class
```python
class MultiHeadAttention(nn.Module):
  def __init__(self, config):
    super().__init__()
    heads_list = [AttentionHead(config) for _ in range(config["heads_num"])]
    self.heads = nn.ModuleList(heads_list)
    self.linear = nn.Linear(config["embedding_dim"], config["embedding_dim"])
    self.dropout = nn.Dropout(config["dropout_rate"])

  def forward(self, input):
    heads_outputs = [head(input) for head in self.heads]
    scores_change = torch.cat(heads_outputs, dim=-1)
    scores_change = self.linear(scores_change)
    return self.dropout(scores_change)
```

#### Testing Multi-Head Attention
- **Instantiate and Test**: Create an instance of MultiHeadAttention and pass the input tensor through it.
```python
mha = MultiHeadAttention(config)
output = mha(input)
print(output.shape)  # Expected output: torch.Size([8, 256, 768])
```

With the multi-head attention implemented, we can proceed to build the rest of our Transformer model.

## Transformers Block
### Lesson
### Downloads
### Implementing a Transformer Block
We covered how multi-head attention works in a Transformer.

Now, let's implement a Transformer block.

#### Overview of a Transformer Block
- **Input Processing**: Each input token is converted into an embedding vector and passed to the multi-head attention block.
- **Feedforward Network**: The output from the multi-head attention block is sent to a feedforward network layer.
- **Chaining**: A Transformer model consists of multiple such blocks chained together.

#### Feedforward Layer
- **Function**: Applied to each embedding vector individually.
- **Process**:
  - Linear Layer: Each embedding vector is passed to a linear layer with an output size four times larger than the input size.
  - Activation Function: The GELU activation function is applied to introduce nonlinearity.
  - Size Reduction: The output vector is then reduced to the original embedding size.
- **GELU Activation Function**
  - Comparison: GELU is similar to the ReLU activation function but has a smoother shape, which helps in achieving better training results.

#### Additional Components
- **Residual Connections**
  - Purpose: Helps with the vanishing gradient problem in deep networks.
  - Implementation: The input to a block is added to the block's output before passing it forward, improving training efficiency.
- **Layer Normalization and Dropout**
  - Layer Normalization: Scales the output so that the mean becomes zero and variance becomes one, leading to faster training.
  - Dropout Layer: Helps prevent overfitting by setting a portion of the output to zero during training.

#### Summary
Components of a Transformer Block:
- Multi-Head Attention
- Feedforward Network
- Layer Normalization
- Dropout
- Residual Connections

These elements work together to process and refine the input data, making Transformer models highly effective for various NLP tasks.

Now that we've covered the theoretical aspects, let's proceed to implement the Transformer block in our model.

## Implementing a Transformer Block
### Lesson
### Downloads
### Implementing a Transformer Block
We have already covered the multi-head attention block. Now, we need to implement the feedforward part of the Transformer block. Once both components are implemented, we can combine them to form a complete Transformer block.

#### Feedforward Block Implementation
To define a feedforward block, we create a new class inheriting from nn.Module.

##### Key Components
- **Linear Layers**: The first linear layer projects the input dimension to four times its size, followed by a GELU activation function and another linear layer that reduces the dimension back to the original size.
- **Dropout Layer**: Added to prevent overfitting.

##### Feedforward Block Code
```python
class FeedForward(nn.Module):
  def __init__(self, config):
    super().__init__()
    self.linear_layers = nn.Sequential(
        nn.Linear(config["embedding_dim"], config["embedding_dim"] * 4),
        nn.GELU(),
        nn.Linear(config["embedding_dim"] * 4, config["embedding_dim"]),
        nn.Dropout(config["dropout_rate"])
    )

  def forward(self, input):
    return self.linear_layers(input)
```

#### Testing the Feedforward Block
- **Instance Creation**: An instance of the feedforward block is created.
- **Input Testing**: A random input is passed through the block to check if the output dimensions are as expected.
```python
ff = FeedForward(config)
input = torch.rand(8, config["context_size"], config["embedding_dim"])
output = ff(input)
print(output.shape)  # Expected: torch.Size([8, 256, 768])
```

#### Transformer Block Implementation
With both the multi-head attention and feedforward blocks ready, we can now implement the Transformer block.

##### Transformer Block Components
- **Multi-Head Attention**: Uses the multi-head attention block.
- **Feedforward Block**: Incorporates the previously defined feedforward block.
- **Layer Normalization**: Two normalization layers are included to stabilize the training process.
- **Residual Connections**: Two residual connections are used to help with the vanishing gradient problem.

##### Transformer Block Code
```python
class Block(nn.Module):
  def __init__(self, config):
    super().__init__()
    self.multi_head = MultiHeadAttention(config)
    self.layer_norm_1 = nn.LayerNorm(config["embedding_dim"])
    self.feed_forward = FeedForward(config)
    self.layer_norm_2 = nn.LayerNorm(config["embedding_dim"])

  def forward(self, input):
    residual = input
    x = self.multi_head(self.layer_norm_1(input))
    x = x + residual

    residual = x
    x = self.feed_forward(self.layer_norm_2(x))
    return x + residual
```

#### Testing the Transformer Block
- **Instance Creation**: Create an instance of the Transformer block.
- **Input Testing**: A random input is passed through the block to verify the output dimensions.
```python
b = Block(config)
input = torch.rand(8, config["context_size"], config["embedding_dim"])
output = b(input)
print(output.shape)  # Expected: torch.Size([8, 256, 768])
```

This implementation completes the core components of our Transformer model, allowing us to handle complex tasks involving sequential data.

## Putting Everything Together
### Lesson
### Downloads
### Assembling the Transformer Model
Now that we have implemented a single block, let's look at how to assemble everything into a complete Transformer model. We'll walk through all the components of the model before implementing it in PyTorch.

#### Model Components Overview
- **Tokenization and Embedding**:
  - Input Splitting: The input is split into tokens, such as words, subwords, or characters.
  - Token ID Conversion: These tokens are converted into token IDs.
  - Embedding Vectors: Token IDs are converted into embedding vectors.
  - Positional Encoding: Positional encoding values are added to the embedding vectors, resulting in input vectors for the model.
- **Layer Processing**:
  - Layer Passing: The input vectors are passed through the layers of the model sequentially.
  - Shape Consistency: The output from each layer has the same shape as the input, but the values of embedding vectors evolve with each layer.
  - Batch Processing: During training, a batch of inputs is processed together to optimize resource usage.
- **Prediction and Output**:
  - Final Layer Output: After the final layer, the output consists of a series of embedding vectors.
  - Token Prediction:
    - Linear Layer: Converts each embedding vector into a new vector with prediction scores for each token in the vocabulary. A score, such as 0.39, indicates the model's confidence in generating a token with a specific ID.
    - Softmax Conversion: Converts the prediction scores into probabilities using the softmax function. This results in a probability distribution for each token, where the sum of probabilities for each position equals one.

By following this structure, we ensure that the Transformer model processes and generates data accurately, leveraging the power of multi-head attention and feedforward networks. This design allows the model to handle complex tasks like language modeling, translation, and more.

The next step is to implement this entire structure in PyTorch, integrating all the components into a cohesive model.

## Transformers Implementation
### Lesson
### Downloads
### Implementing the Transformer Model
Now that we have a single block, it's time to implement the entire Transformer model.

We will define a new class inheriting from nn.Module and use all the components we have previously defined.

#### Building Blocks of the Model
- **Token Embedding**
  - Purpose: Converts input token IDs into embedding vectors.
  - Implementation: Using nn.Embedding, which maps each token ID to its corresponding embedding vector.
  - Parameters:
    - Number of embedding vectors (vocabulary size).
    - Dimensionality of the embedding vectors.
- **Positional Encoding**
  - Purpose: Adds positional information to the embedding vectors, helping the model understand the order of tokens.
  - Implementation: Another nn.Embedding layer, but with the number of vectors equal to the context size (the maximum number of tokens in a sequence).
- **Transformer Blocks**
  - Creation: We create multiple Transformer blocks, each containing a multi-head attention layer and a feedforward layer.
  - Combination: These blocks are combined sequentially, allowing data to pass through each layer.
- **Final Layer Normalization and Linear Layer**
  - Layer Normalization: Normalizes the output from the last Transformer block.
  - Linear Layer: Converts the final output vectors into prediction scores for each token in the vocabulary, determining which token should be generated next.

#### Model Implementation in PyTorch
##### DemoGPT Class
```python
class DemoGPT(nn.Module):
  def __init__(self, config):
    super().__init__()
    self.token_embedding_layer = nn.Embedding(config["vocabulary_size"], config["embedding_dim"])
    self.positional_embedding_layer = nn.Embedding(config["context_size"], config["embedding_dim"])
    blocks = [Block(config) for _ in range(config["layers_num"])]
    self.layers = nn.Sequential(*blocks)
    self.layer_norm = nn.LayerNorm(config["embedding_dim"])
    self.unembedding = nn.Linear(config["embedding_dim"], config["vocabulary_size"], bias=False)

  def forward(self, token_ids):
    batch_size, tokens_num = token_ids.shape
    x = self.token_embedding_layer(token_ids)
    sequence = torch.arange(tokens_num, device=device)
    x = x + self.positional_embedding_layer(sequence)
    x = self.layers(x)
    x = self.layer_norm(x)
    x = self.unembedding(x)
    return x
```

#### Testing the Model
- **Initialization**: The model is initialized with the given configuration and moved to the GPU if available.
- **Input Handling**: A test phrase is encoded using the tokenizer and passed to the model. The unsqueeze method is used to add an extra dimension for batch processing.
```python
model = DemoGPT(config).to(device)
output = model(tokenizer.encode("Hi").unsqueeze(dim=0).to(device))
print(output.shape)  # Expected: torch.Size([1, 2, 65])
```

#### Text Generation Functions
##### generate Function
- **Purpose**: Generates text sequences using the model.
- **Process**:
  - Initializes output with prompt IDs.
  - Iteratively generates tokens using the model, sampling the next token based on the softmax probabilities.
```python
def generate(model, prompt_ids, max_tokens):
    output_ids = prompt_ids
    for _ in range(max_tokens):
      if output_ids.shape[1] >= config["context_size"]:
        break
      with torch.no_grad():
        logits = model(output_ids)
      logits = logits[:, -1, :]
      probs = F.softmax(logits, dim=-1)
      next_token_id = torch.multinomial(probs, num_samples=1)
      output_ids = torch.cat([output_ids, next_token_id], dim=-1)
    return output_ids
```

##### generate_with_prompt Function
- **Purpose**: A wrapper for the generate function.
- **Functionality**: Takes a prompt string, encodes it into token IDs, passes it to the generate function, and decodes the output into a string.
```python
def generate_with_prompt(model, tokenizer, prompt, max_tokens=100):
  model.eval()
  prompt = tokenizer.encode(prompt).unsqueeze(dim=0).to(device)
  return tokenizer.decode(generate(model, prompt, max_tokens=max_tokens)[0])
```

#### Example Usage
Testing the generate_with_prompt function:
```python
generate_with_prompt(model, tokenizer, "First Citizen:\n")
# Output: "First Citizen:\nDc?SlGAOau$r'QE'us3:nSfYjnkJpFkLVEc$GovIKqlQHxRa\nA;MWyCrmtZkMp?jCiqNPWFutrO $YcaR:rb!BdGtPyvE$-PVVsE"
```

The generated output is currently gibberish because the model is not trained yet. Training the model is the next step.

## Training the Model
### Lesson
### Downloads
### Training the Demo GPT Model
Once we have defined the demo GPT model, the next step is to train it. The training process for this model is similar to training other neural network models. Here’s a breakdown of the training workflow:

#### Training Workflow
1. **Data Loading**
   - Data Loader: In each iteration, we use a data loader to load a batch of inputs and targets.
   - Inputs: Tensor of token IDs representing the input text.
   - Targets: Tensor of token IDs representing the expected output.
2. **Model Prediction**
   - Forward Pass: The batch of inputs is passed through the model, which generates predictions.
   - Predictions: The model outputs logits, which are raw prediction scores for each token in the vocabulary.
3. **Loss Calculation**
   - Loss Function: We calculate the loss by comparing the model's predictions with the actual targets.
   - Purpose: The loss function quantifies how far the model's predictions are from the actual values.
4. **Backpropagation**
   - Gradient Calculation: With the calculated loss, we perform backpropagation to compute the gradients of the loss with respect to the model parameters.
5. **Parameter Update**
   - Optimizer: Using the optimizer, we update the model's parameters to minimize the loss.
   - Iteration Completion: This completes a single iteration of training.
6. **Repeating the Process**
   - Epochs: The training process is repeated for many iterations and epochs, using different batches of data to improve the model's performance.

By following this workflow, the model learns to generate more accurate text outputs over time. Each batch of data helps the model fine-tune its weights and biases, gradually improving its predictions.

## Training the Model with PyTorch
### Lesson
### Downloads
### Training the GPT Model: Implementation and Progress
In previous demos, we've built our model step by step. Now, it's time to implement the training code and train our model to generate text.

This demo involves implementing the standard PyTorch model training loop, with some specifics for our language model.

#### Training Setup
##### Hyperparameters
- **Batch Size**: Set to 64, meaning each training step processes 64 sequences at a time.
- **Iterations**: Training runs for 5,000 iterations.
- **Evaluation Frequency**: Evaluate the model every 100 iterations by generating text.
- **Learning Rate**: Controls how much to adjust model parameters during each training step.

##### Data Preparation
- **Tokenization**: The text data is tokenized and converted into token IDs. The encode method returns a one-dimensional tensor where every element is a token ID, and we put the tensor on the selected device, which will be a GPU if available.
```python
tokenized_text = tokenizer.encode(text).to(device)
```
- **Dataset and Data Loader**:
  - Dataset: Created using the tokenized text.
  - Random Sampler: Randomly selects training examples, specifying the number of examples based on training iterations and batch size.
  - Data Loader: Iterates over selected training examples using the specified batch size and random sampler.
```python
dataset = TokenIdsDataset(tokenized_text, block_size=64)
sampler = RandomSampler(dataset, replacement=True, num_samples=train_iterations * batch_size)
data_loader = DataLoader(dataset, batch_size=batch_size, sampler=sampler)
```

##### Optimizer
- **AdamW Optimizer**: Used to update model parameters during training, known for better training results. The learning rate is set based on our chosen hyperparameter.
```python
optimizer = torch.optim.AdamW(model.parameters(), lr=learning_rate)
```

#### Training Loop
- **Mini-Batch Iteration**: Iterate over mini-batches using the data loader.
- **Training Mode**: The model is switched to training mode for each iteration.
- **Forward Pass**: The input from each mini-batch is passed through the model, returning logits.
- **Loss Calculation**:
  - Logits and Targets Reshaping: Necessary to fit the shape expected by the cross-entropy function.
  - Cross-Entropy Loss: Calculates the loss for the step, comparing model predictions to the actual targets.
- **Backpropagation**: Compute gradients based on the loss.
- **Parameter Update**: The optimizer updates model parameters.
- **Gradient Reset**: Before the next step, gradients are reset to avoid accumulation.
```python
for step_num, sample in enumerate(data_loader):
    model.train()
    input, targets = sample
    input, targets = input.to(device), targets.to(device)
    logits = model(input)

    logits_view = logits.view(batch_size * config["context_size"], config["vocabulary_size"])
    targets_view = targets.view(batch_size * config["context_size"])

    loss = F.cross_entropy(logits_view, targets_view)
    loss.backward()
    optimizer.step()
    optimizer.zero_grad(set_to_none=True)

    if step_num % evaluation_interval == 0:
        print(f"Step {step_num}. Loss {loss.item():.3f}")
        print("Demo GPT:\n" + generate_with_prompt(model, tokenizer, "\n"))
```

#### Evaluation and Progress Monitoring
- **Text Generation**: Every 100 iterations, the model generates text from a simple prompt (e.g., a newline character) to evaluate training progress.
- **Loss Tracking**: The decreasing loss indicates that the model is learning to generate more accurate text.

#### Training Progress
- **Initial Outputs**: Early in training, the model generates random text.
- **Gradual Improvement**: As training progresses, the model starts generating text that resembles the training data, including character names and dialogues.
- **Further Training**: Continued training leads to more coherent text generation, eventually resembling Shakespearean style.

By following this training process, the model learns to generate text similar to the input data. The more iterations we train it, the better it becomes at generating coherent and stylistically accurate text.

## Exercise: Calculate Validation Loss
### Lesson
### Downloads
In this exercise, you will learn how to calculate the validation loss for a neural network model using PyTorch. Implementing validation loss is crucial for evaluating the model's performance on unseen data, which helps prevent overfitting and ensures the model generalizes well to new data.

#### Overview
These are the steps for calculating the validation loss:

- **Split the Dataset**: Separate the data into training and validation datasets to evaluate the model's performance during training.
- **Create a Validation Dataset and DataLoader**: Prepare the data for evaluation.
- **Calculate Validation Loss**: Implement the logic to compute the validation loss, which provides insight into how well the model performs on the validation dataset.
- **Update the Training Loop**: Integrate validation loss calculation into the training loop and visualize training and validation loss over time.

The starter code provided includes the essential components of a PyTorch model, including data tokenization, model definition, and a basic training loop. Your task is to complete the implementation, focusing on the validation aspect of the model's training process.

#### Starter Code
The provided code initializes the model, tokenizer, and datasets. Here's an overview:

- **Model Initialization**: The DemoGPT class defines the architecture of a simple GPT-like model using PyTorch.
- **Data Tokenization**: The CharTokenizer class tokenizes text data, converting it into token IDs that the model can process.
- **DataLoader Setup**: The training and validation data loaders are prepared to handle batches of data during training and validation.

#### Splitting the Dataset
To do this, we first need to split our dataset into training and validation datasets. We tokenize the input text just as we did before and then calculate how many tokens we want to use for training. Given this ratio, we take this number of tokens as training data and use the rest as validation data. Having training and validation data, we then create a validation dataset and a validation data loader.
```python
tokenized_text = tokenizer.encode(text).to(device)
train_count = int(train_split * len(tokenized_text))
train_data, validation_data = tokenized_text[:train_count], tokenized_text[train_count:]
train_dataset = TokenIdsDataset(train_data, config["context_size"])
validation_dataset = TokenIdsDataset(validation_data, config["context_size"])
```

#### Validation Loss Calculation
Next, we implement a function to calculate the validation loss. First, we switch our model from training mode into evaluation mode to run our model for inference, which, for example, deactivates the Dropout layers we've added to our model. Keep in mind that we switch our model back to training mode at the beginning of every training iteration.
```python
@torch.no_grad()
def calculate_validation_loss(model, batches_num):
    model.eval()
    total_loss = 0
```

We then create an iterator from our validation dataset and run a loop for the specified number of batches. For every batch, we perform similar steps to those in training: we first get the inputs and targets, pass these inputs to the model to get logits, and then reshape logits and targets to calculate the validation loss using the cross-entropy function. After this, we add the loss to the total validation loss for every iteration. When the loop is finished, we compute the average loss by dividing the total loss by the number of batches we processed, and then we return the average loss.
```python
    validation_iter = iter(validation_dataloader)

    for _ in range(batches_num):
        input, targets = next(validation_iter)
        logits = model(input)

        logits_view = logits.view(batch_size * config["context_size"], config["vocabulary_size"])
        targets_view = targets.view(batch_size * config["context_size"])

        loss = F.cross_entropy(logits_view, targets_view)

        total_loss += loss.item()

    average_loss = total_loss / batches_num

    return average_loss
```

#### Plotting Training and Validation Loss
Finally, we update our code to draw a chart of training and validation losses. We append the training loss and training step to two arrays, using the item method to convert a tensor to a number for every training step. We do the same for the validation loss. The reason we need to store the step number with loss values is that we calculate training loss on every step and validation loss only every ten steps, and we need to preserve step numbers for Matplotlib to correctly plot these charts and align values accurately.
```python
plot_output = widgets.Output()
display(plot_output)

def update_plot(train_losses, train_steps, validation_losses, validation_steps):
    with plot_output:
        clear_output(wait=True)
        plt.figure(figsize=(7, 5))
        plt.plot(train_steps, train_losses, label='Training Loss')
        plt.plot(validation_steps, validation_losses, label='Validation Loss')
        plt.title('Training and Validation Loss')
        plt.xlabel('epoch')
        plt.legend(loc='center left')
        plt.grid(True)
        plt.show()
```

If we now run our model, and I'll rerun this notebook, as you can see, we've got our training and validation loss chart. If we wait for a few dozen iterations, we will see two lines on the chart, one for the training loss and another for the validation loss.

#### Training and Validation Loss Calculation Step Summary
- **Splitting the Dataset**
  - To calculate validation loss, split the dataset into training and validation datasets.
  - Tokenize the input text and determine the number of tokens for training based on the desired ratio.
  - The rest of the tokens are used for validation.
  - Create datasets and data loaders for both training and validation data.
- **Validation Loss Calculation Function**
  - Switch the model to evaluation mode to deactivate Dropout layers.
  - Use an iterator to process batches from the validation dataset.
  - For each batch:
    - Extract inputs and targets.
    - Pass inputs through the model to obtain logits.
    - Reshape logits and targets to calculate loss using the cross-entropy function.
  - Aggregate the loss to compute the total validation loss.
  - Average the total loss by the number of processed batches to obtain the validation loss.
- **Plotting Training and Validation Loss**
  - Store training and validation losses along with the corresponding steps.
  - Use Matplotlib to plot the losses, ensuring step numbers align with loss values.

Now let's take a look at how we can calculate validation loss for our model during training. To do this, we first need to split our dataset into training and validation datasets. We tokenize the input text just as we did before and then calculate how many tokens we want to use for training. Given this ratio, we take this number of tokens as training data and use the rest as validation data. Having training and validation data, we then create a validation dataset and a validation data loader.

Next, we implement a function to calculate the validation loss. First, we switch our model from training mode into evaluation mode to run our model for inference, which, for example, deactivates the Dropout layers we've added to our model. Keep in mind that we switch our model back to training mode at the beginning of every training iteration.

We then create an iterator from our validation dataset and run a loop for the specified number of batches. For every batch, we perform similar steps to those in training: we first get the inputs and targets, pass these inputs to the model to get logits, and then reshape logits and targets to calculate the validation loss using the cross-entropy function. After this, we add the loss to the total validation loss for every iteration. When the loop is finished, we compute the average loss by dividing the total loss by the number of batches we processed, and then we return the average loss.

Finally, we update our code to draw a chart of training and validation losses. We append the training loss and training step to two arrays, using the item method to convert a tensor to a number for every training step. We do the same for the validation loss. The reason we need to store the step number with loss values is that we calculate training loss on every step and validation loss only every ten steps, and we need to preserve step numbers for Matplotlib to correctly plot these charts and align values accurately.

If we now run our model, and I'll rerun this notebook, as you can see, we've got our training and validation loss chart. If we wait for a few dozen iterations, we will see two lines on the chart, one for the training loss and another for the validation loss.

## Limitations and Scaling
### Lesson
### Downloads
### Comparing Our Model to OpenAI's GPT Series
Let's compare our model to some models created by OpenAI.

The very first model released by OpenAI was called GPT-1. It had 120 million parameters, 12 layers, and was trained on 4.5 GB of data.
Their next model, called GPT-2, was a scaled-up version of GPT-1. It had the same architecture but around 10 times more parameters, four times more layers, and was trained on 10 times more data.
They then scaled up this architecture again and created the GPT-3 model, which became the foundation for the GPT product. This model had even more layers, more parameters, and was trained on even more data.
We don't know much about their most recent models, but it is rumored that they are based on a mixture of different models with even more parameters.

#### Model Scaling and Capabilities
One trend you can see is that the bigger the model is, the more capable it usually becomes, and there are already some models with one trillion parameters. However, scaling models is not the only thing needed to achieve capabilities like those of products such as ChatGPT. If we train a model that can simply predict the next word, it will only be able to generate text but won't be able to answer questions like ChatGPT. This limitation does not depend on the amount of training data used or the model size.

#### Example of Model Limitations
To give you an example, I've sent the following prompt to one of the older versions of GPT-3, which was trained to generate text instead of answering questions. As you can see, instead of answering the question, it started generating text related to the question. After being trained on a larger text corpus, it can only generate text that could surround a text that looks like the provided prompt. In contrast, if you send this question to ChatGPT, it would return an answer like 'Paris' and possibly provide some additional information.

#### Training ChatGPT to Answer Questions
So, how did OpenAI train a model that can answer questions? Let's take a high-level overview. They first trained a GPT model similar to what we've built but bigger and using much more data. Then, they used a dataset of questions and answers. With this dataset, they updated the weights of the trained GPT model to create a model that can answer questions. This new model, produced as a result of this process, was called GPT-3.5 and was used by the first version of ChatGPT. This process of taking a model trained for one task and modifying its weights to work for a different task is called fine-tuning, and it is used not just for LLMs but for other deep learning models as well.

#### Fine-Tuning Process
To fine-tune a model to perform question answering, OpenAI went through the following steps:

- They collected a dataset with different prompts and questions.
- They had humans answer these questions and organized the human-provided answers into a dataset.
- This dataset was then used to fine-tune the GPT-3 model to train it to answer questions.

#### Further Refinement with Reward Models
After this, they went through a different process. Using prompts, they sampled several outputs from the model to generate multiple answers for the same question. Then, people ranked these answers against each other. Using these ranking results, OpenAI created another dataset. This dataset of ranked answers was used to train another model called the reward model, which can calculate how good an answer to a prompt is. Finally, using the reward model, they fine-tuned the GPT-3 model to give answers that are more closely aligned with a reward policy.

#### Conclusion
As you can see, training a model that can answer questions is a complicated process, and the datasets used for this are not shared by OpenAI and are much harder to collect.

### Comparing Models: Our Model vs. OpenAI's GPT Series
- **GPT-1**:
  - Parameters: 120 million
  - Layers: 12
  - Training Data: 4.5 GB
- **GPT-2**:
  - Parameters: Approximately 10 times more than GPT-1
  - Layers: Four times more than GPT-1
  - Training Data: 10 times more than GPT-1
- **GPT-3**:
  - Parameters: Significantly more than GPT-2
  - Layers: Increased from GPT-2
  - Training Data: Substantially larger than GPT-2
- **Recent OpenAI Models**:
  - Rumored to be based on a mixture of different models
  - Even more parameters than GPT-3

#### The Relationship Between Model Size and Capability
- Larger models tend to be more capable.
- Some models have reached up to one trillion parameters.
- However, simply scaling up models isn't enough to achieve capabilities like those of ChatGPT.

#### Limitations of Larger Models
- **Predictive Capability**: Models trained to predict the next word can only generate text, not answer questions.
- **Example**: An older GPT-3 version, trained to generate text, responded to prompts by generating related text rather than direct answers.

#### How ChatGPT Was Trained
- **Initial Training**:
  - A GPT model was trained similar to our model but on a larger scale.
- **Fine-Tuning for Question Answering**:
  - Dataset Creation: A dataset of questions and answers was compiled.
  - Human Input: Humans answered these questions, creating a comprehensive dataset.
  - Fine-Tuning Process: The GPT-3 model's weights were adjusted using this dataset to specialize in answering questions.
- **Post-Training Adjustments**:
  - Generating Answers: The model generated multiple answers for prompts.
  - Ranking Answers: Humans ranked these answers, creating a new dataset.
  - Reward Model Training: This ranked dataset was used to train a reward model that evaluates the quality of answers.
  - Final Fine-Tuning: The GPT-3 model was fine-tuned again using the reward model to align its responses with the desired quality.

## Other Model Architectures
### Lesson
### Downloads
### Transformer Architectures: An Overview
We have implemented a particular architecture for large language models called the decoder-only architecture.

There are other architectures, and now we'll briefly cover what they are and how they differ from each other.

#### Origin of Transformers
Transformers were initially introduced in a paper called "Attention Is All You Need." This paper described an architecture more complex than what we implemented. This architecture was created for a different purpose: instead of generating text, the authors focused on translating text from one language to another.

#### Key Components of Transformer Architecture
- **Decoder Component**: The right part of the architecture, similar to our model, includes:
  - Embedding layer
  - Positional encoding
  - Masked multi-head attention (using a triangular mask to modify attention scores)
  - Feedforward layer with residual connections
  - Nx Repeated Blocks: This block is repeated multiple times, similar to our model.
- **Encoder Component**: The left part, absent in our model, was used to encode information about an input text for translation. The encoder uses multi-head attention (without masking) and processes the entire input.
- **Interaction Between Encoder and Decoder**:
  - The encoder processes the input text, and its final layer's output is passed to the decoder layers.
  - The decoder generates the next token based on the encoded input and its partially generated output.

#### Example: Translation from English to French
- **Tokenization**: The English text is tokenized and converted into token IDs.
- **Encoding**: Token IDs are passed to the encoder to build a representation of the phrase.
- **Decoding**:
  - The process starts with a "start of the sequence" token sent to the decoder.
  - The decoder reads its input and the encoder's output to produce the next token ID of the translated phrase.
  - This process repeats, generating more tokens until an "end of sequence" token is produced.
  - The final token IDs are converted into a human-readable sentence.

#### Different Network Architectures Using Encoders and Decoders
- **Decoder-only models**:
  - Only include the decoder part, without an encoder.
  - Suitable for text generation tasks.
  - Examples: GPT and LLaMA.
- **Encoder-decoder models**:
  - Include both encoder and decoder blocks.
  - Ideal for tasks like translating text into another language.
  - Examples: BERT and T5.
- **Encoder-only models**:
  - Lack a decoder, using only the encoder to process inputs.
  - Useful for text classification tasks like sentiment analysis or spam detection.
  - Example: BERT.

## Using Pre-Trained Transformer Models
### Lesson
### Downloads
### Leveraging Existing Large Language Models
So far, we have been looking into how to create a large language model from scratch. Now let's explore how to use existing large language models and adapt them to various tasks in your applications.

While it is important to understand how large language models work under the hood, it is unlikely you will need to create one from scratch for your applications. Training an LLM from scratch is challenging for several reasons:

- **Data and Resources**: Training these models requires huge amounts of training data and a lot of computational resources.
- **Cost**: These models are very expensive to train. For example, the cost of training the GPT-4 model was more than $100 million.
- **Expertise**: Developing new models requires a specialized skill set, especially if you aim to implement a state-of-the-art model.

#### Hugging Face: A Resource for Pre-Trained Models
Fortunately, instead of creating a model from scratch, we can use existing models created by companies and researchers from all around the world. To do this, we will use the Hugging Face(opens in a new tab) library, which is one of the most popular NLP libraries for Python. At the moment of this recording, it has a whopping 27,000 stars on GitHub. It also has a huge community contributing to the project, developing new large language models, and improving its features.

Hugging Face simplifies building applications using LLMs but is not limited to this. It also provides tools for developing new LLMs. Hugging Face is a collection of multiple components that work together. It provides an API that allows us to build applications using LLMs. We can access a large collection of pre-trained models that we can use in our applications. It also provides access to datasets for different purposes that we can use to train our models or improve existing models. Finally, it provides the Spaces project, which allows us to quickly create machine learning demos and applications.

#### API and Capabilities
Hugging Face provides a set of flexible and powerful APIs that we can use to build our AI applications. Using their API, we can do things like access existing models for a variety of tasks such as text generation, text summarization, and so on. We can train new models or fine-tune existing models from their library of models. Fine-tuning is a process that allows us to take an existing model and update its weights to make it better for a specific task for which the model wasn't originally trained. We can also process text for LLMs, for example, by tokenizing text using an existing tokenizer or creating our own tokenizer. Finally, we can deploy our LLMs.

#### Beyond Text: Images and Audio
Hugging Face is not limited to working with just text; it also includes APIs to work with images and audio.

#### Comparing Hugging Face and OpenAI
You might be wondering how Hugging Face is different from OpenAI. Both provide models and allow us to build applications using them, but they are very different companies. Hugging Face is an open-source product; we can run models from Hugging Face locally on our laptops or on servers that we control. Hugging Face models are also free to use. On the other hand, OpenAI, despite the name, provides closed-source models. They only allow us to access their models via their API, and these models run on servers that OpenAI operates. Additionally, we need to pay to access advanced OpenAI models.

## Hugging Face Library
### Lesson
### Downloads
### Using Existing LLMs with Hugging Face
Let's take a look at how we can use existing LLMs with Hugging Face.

When it comes to using Hugging Face models, we have two options:

- **High-Level API**: This is accessible using the pipeline function and is user-friendly.
- **Low-Level API**: This offers more flexibility and control over the model's usage.

Since this is a beginner-friendly lesson, we will focus just on using the high-level API, but keep in mind that Hugging Face API has much more to offer.

#### Text Generation with Hugging Face
To use a large language model with Hugging Face:

- **Import the Pipeline Function**: Import the pipeline function from the Transformers package.
- **Specify the Task**: Call the pipeline function and provide the name of the task, such as "text-generation." This function returns another function that we can use to perform the selected task.
- **Provide a Prompt**: For text generation, specify a prompt that will be used to generate the text.

To generate text using this prompt:

- Call the generator function returned by the pipeline call.
- Provide parameters such as the prompt, the maximum length of the output, and the number of sequences to generate.

#### Hugging Face's Versatility
Hugging Face supports a wide range of NLP-related tasks, including:

- Text Generation: As described above.
- Question Answering: Finding answers to questions based on a given context.
- Text Summarization: Summarizing large pieces of text.
- Translation: Translating text between different languages.
- Text Classification: Classifying text into categories.

In addition to NLP tasks, Hugging Face also supports:

- Audio Tasks: Such as audio classification and text-to-speech conversion.
- Image and Video Tasks: Including image classification, video classification, and image segmentation.

#### Example: Image Classification with Hugging Face
Here's how to perform image classification using Hugging Face:

- **Specify the Task**: Use the pipeline function, specifying the task as "image-classification."
- **Pass an Image**: Provide an image file or an image URL for classification.
- **Interpret the Output**: The output is a list with each element containing a label and an associated probability, indicating what the model thinks the image represents. For example, it might classify an image as likely being a cat.

### Using Hugging Face High-Level API for Pre-Trained LLMs
In this demo, we will use the Hugging Face high-level API to utilize some pre-trained large language models.

We'll see how to summarize text, generate new text, classify text samples, and more.

#### Text Summarization
First, to use the high-level API from Hugging Face, we need to import the pipeline function from the transformers library. Let's see how we can summarize some text. To do this, we first need to create a pipeline and specify the summarization task. When we create it, this function will return a summarizer that we can then use to summarize our text.
```python
from transformers import pipeline

# Load the summarization pipeline
summarizer = pipeline("summarization")

# Text to be summarized
text = """
The Hub is home to over 5,000 datasets in more than 100 languages that can be used for a broad range of tasks across NLP, Computer Vision, and Audio. The Hub makes it simple to find, download, and upload datasets.
Datasets are accompanied by extensive documentation in the form of Dataset Cards and Dataset Preview to let you explore the data directly in your browser.
While many datasets are public, organizations and individuals can create private datasets to comply with licensing or privacy issues. You can learn more about Datasets here on Hugging Face Hub documentation.

The 🤗 datasets library allows you to programmatically interact with the datasets, so you can easily use datasets from the Hub in your projects.
With a single line of code, you can access the datasets; even if they are so large they don’t fit in your computer, you can use streaming to efficiently access the data.
"""

summary = summarizer(text, max_length=130, min_length=30)
print(summary[0]['summary_text'])
```

#### Text Generation
Next, let's see how we can generate some text. The process here is very similar. We create a pipeline, provide a prompt that will be used as a starting point for the model to generate follow-up text, and we can also provide additional parameters like max_length and the number of sequences to return.
```python
# Load the text generation pipeline
generator = pipeline("text-generation")

# Define the prompt for the text generation
prompt = "Scientists from University of California, Berkeley has announced that"

# Generate text based on the prompt
generated_text = generator(prompt, max_length=100, num_return_sequences=1)
print(generated_text[0]['generated_text'])
```

#### Zero-Shot Classification
Another thing we will try is to classify text using so-called zero-shot classification. In this context, "shot" means how many examples we provide in a prompt for our model to understand what it should do. "Zero-shot" means we don't provide any example.
```python
classifier = pipeline("zero-shot-classification", model="facebook/bart-large-mnli")

# Text to classify
text = "Transformers support framework interoperability between PyTorch, TensorFlow, and JAX. This provides the flexibility to use a different framework at each stage of a model’s life; train a model in three lines of code in one framework, and load it for inference in another."

labels = ["technology", "biology", "space", "transport"]

results = classifier(text, candidate_labels=labels, hypothesis_template="This text is about {}.")
for label, score in zip(results['labels'], results['scores']):
  print(f"{label} -> {score}")
```

#### Image Captioning
Hugging Face is not limited to working just with text; we can also use it with images. For example, if we have an image, we can create a captioning model that will write a text caption for this image, describing what is in the image.
```python
from IPython.display import Image, display

# Replace the URL below with the URL of your image
image_url = 'https://huggingface.co/datasets/Narsil/image_dummy/raw/main/parrots.png'

# Display the image in the notebook
display(Image(url=image_url))

captioner = pipeline(model="ydshieh/vit-gpt2-coco-en")

result = captioner(image_url)
print(result)
```

## Text Generation Options
### Lesson
### Downloads
### Text Generation Parameters
Now we will talk about how we can affect text generation results using various generation parameters that are available in Hugging Face and other libraries.

To avoid some possible confusion, there are two types of parameters:

- model parameters, which are set during model training, and
- generation parameters, which can affect the result of text generation when we use a model after it is trained.

#### Maximum Number of Tokens
We have already seen one parameter, which is the maximum number of tokens the text generation process should return. In Hugging Face, this is called the max_length parameter. As you can imagine, the higher this parameter is, the longer the output the text generation process will produce. However, one gotcha is that it defines a maximum number of tokens, and text generation can return an output that is shorter than this value. During the text generation process, a model can emit a special "end of sequence" token that will stop the generation process even before it reaches the specified limit.

#### Greedy Decoding
One simple option for generating text is to select the token with the highest probability every time a new token is generated. This approach, called "greedy decoding," picks the word with the highest probability and adds it to the input, repeating the process. However, this can lead to boring and repetitive results.

#### Multinomial Sampling
To avoid repetitive results, we can introduce randomness by picking less probable tokens. This method, known as "multinomial sampling," uses the output of the softmax layer as a probability distribution to randomly select tokens. The higher the probability of a token, the more likely it will be selected. This approach provides a more varied and interesting output.

#### Beam Search
Beam search is an algorithm used to generate multiple sequences at the same time, evaluating them to find the best result. Instead of generating a single sequence, beam search keeps "n" best sequences at each step, generating new sequences from these and repeating the process. This method helps in finding more optimal sequences by considering multiple possible outputs simultaneously.

#### Top-K Sampling
The top_k parameter specifies the number of tokens with the highest probability to consider when selecting the next token. For example, setting top_k to 3 means selecting the next token from the top three most probable tokens. Higher top_k values can lead to more creative outputs but may also produce less coherent text.

#### Top-P (Nucleus) Sampling
The top_p parameter specifies the cumulative probability of the most probable tokens to consider when selecting the next token. This method ensures that only tokens that collectively meet a certain probability threshold are considered, allowing for dynamic adjustment of the number of tokens based on their probabilities.

#### Temperature
The temperature parameter adjusts the probability distribution returned by the softmax layer. Lowering the temperature increases the chances of selecting tokens with higher logits, making the output more deterministic. Increasing the temperature flattens the probability distribution, allowing for more diverse token selection.

#### Using Parameters with Hugging Face
In Hugging Face, these parameters can be set when using the generator function. For example, do_sample enables multinomial sampling, and num_beams specifies the number of sequences in beam search. Parameters like top_k, top_p, and temperature control the randomness and creativity of the generated output, allowing for fine-tuning the behavior of the language model according to specific requirements.

### Text Generation with Temperature and Top-K Sampling
```python
# Step 0 - Install transformers if not already
# !pip install transformers

from transformers import pipeline

# Step 1 - Set up text generation pipeline
prompt = "During the latest presentation OpenAI"
model_name = "openai-community/gpt2-large"

text_generator = pipeline(
    task="text-generation",
    model=model_name,
    device=0  # Use GPU if available
)

# Step 2 - Generate text with default settings (greedy search)
default_output = text_generator(prompt, max_length=100, num_return_sequences=1)
print("Greedy search output:\n", default_output[0]['generated_text'])

# Step 3 - Sampling (introduces randomness)
sampled_output = text_generator(prompt, max_length=100, do_sample=True, num_return_sequences=1)
print("\nSampling output:\n", sampled_output[0]['generated_text'])

# Step 4 - Beam search
for num_beams in [1, 2, 4, 8]:
    beam_output = text_generator(
        prompt,
        max_length=100,
        do_sample=False,
        num_beams=num_beams,
        num_return_sequences=1
    )
    print(f"\nBeam search output (num_beams={num_beams}):\n", beam_output[0]['generated_text'])

# Step 5 - Beam search with multinomial sampling
for num_beams in [2, 4, 8]:
    beam_sample_output = text_generator(
        prompt,
        max_length=100,
        do_sample=True,
        num_beams=num_beams,
        num_return_sequences=1
    )
    print(f"\nBeam search + sampling output (num_beams={num_beams}):\n", beam_sample_output[0]['generated_text'])

# Step 6 - Top-k sampling
for top_k in [1, 10, 50, 100, 500]:
    topk_output = text_generator(
        prompt,
        max_length=100,
        do_sample=True,
        top_k=top_k,
        num_return_sequences=1
    )
    print(f"\nTop-k sampling output (top_k={top_k}):\n", topk_output[0]['generated_text'])

# Step 7 - Temperature sampling
for temperature in [0.1, 0.7, 1.0, 1.5, 3.0]:
    temp_output = text_generator(
        prompt,
        max_length=100,
        do_sample=True,
        temperature=temperature,
        num_return_sequences=1
    )
    print(f"\nTemperature output (temperature={temperature}):\n", temp_output[0]['generated_text'])
```
