# Introduction to Transformer Neural Networks 🤖

In this lesson, we will dive deep into Transformer models, the cornerstone technology underpinning many AI products today, such as ChatGPT and GitHub Copilot.

Not only will we learn how these models work in great detail, but we will also build one from scratch using PyTorch.

## Why Learn Transformers?
Because **Transformer models** are one of the most revolutionary inventions of the last decade. They allow computers to do things that previously seemed unimaginable, such as:
* Writing human-like text
* Generating realistic-looking images
* In some cases, even planning and performing actions independently

By learning how these models work, you'll be equipped with the knowledge to use them to solve real-world problems.

### What You'll Learn
By the end of the lesson, you will:
* Understand the architecture and inner workings of Transformer models
* Learn how to use existing Transformer-based models in your projects

-----

## The AI Era
The recent advancements in AI have been so significant that some people have called it the **AI era**. So, what happened?

* **AI Origins:** The first AI models were created in the 1950s.
* **Important Leaps:**
    * **1990s:** Development of machine learning
    * **2000s:** Development of deep learning
    * **2010s:** AI gained widespread adoption

### Generative AI
In the 2020s, we witnessed the development of **generative AI**, which can generate text, create images, and other media. A pivotal moment occurred on November 30th, 2022, when OpenAI released **ChatGPT**.

### ChatGPT
**ChatGPT** is a chat interface that allows you to communicate with an AI model. You can ask it questions or request it to write something for you, like a tweet. You can then ask follow-up questions, and it can generate new responses, keeping track of the context of your conversation.
* **Rapid Growth:** ChatGPT quickly gained popularity, acquiring 100 million users in just two months.

### Generative AI Applications
Generative AI tools can:
* **Answer Questions:** Like ChatGPT, which can generate all kinds of text, from marketing copies and text summaries to computer programs.
* **Customer Service:** Handle customer queries automatically.
* **Improve Search:** Summarize search results, bringing the most important information from several sources.
* **Personal Assistants:** Devices that can take voice or text commands to perform actions.

### Expert Opinions
> "Generative AI has the potential to change the world." — **Bill Gates**
> "Generative AI is the most powerful tool for creativity ever created." — **Elon Musk**
> "Generative models possess the potential to revolutionize industries from music to fashion and gaming." — **Yann LeCun**

### Overview
In this learning path, we will:
* Cover the fundamentals of **NLP (Natural Language Processing)**, enabling computers to comprehend and manipulate human language.
* Learn about **Transformer models**, a type of deep learning model that powers tools like ChatGPT.
* Implement and train a Transformer model using **PyTorch**.
* Provide a brief overview of how to use Transformer models created by others.

We have a lot of exciting content ahead, so without any further ado, let's get started!

-----

## Introduction to ChatGPT
Let's first talk about what GPT is and get a very high-level overview of how it works. **GPT** stands for **Generative Pre-trained Transformer**.
* **Generative:** This model can generate text.
* **Pre-trained:** It was trained on large amounts of data.
* **Transformers:** The name of the network architecture used to create the GPT model. Network architecture refers to how different blocks of a neural network are arranged together.

### Transformers and Their Functionality
If you've seen other lessons in this series, you should already be familiar with feedforward networks and convolutional networks, commonly used for image classification. **Transformers** are another, more recently developed, network architecture created for processing text. They are used for tasks like:
* Translating from one language to another
* Text generation

### Core Mechanism: Text Generation
At the core of Transformers is the model's ability to generate the next word given some input text. For example, given the input "In a shocking turn of events," a GPT model might generate the next word as "it." This process can be repeated, adding each new word to the input to generate a meaningful output over time.
* **Terminology:** The input provided to a model is also called a "**prompt**," and we will use the terms "input" and "prompt" interchangeably.

### Learning from Training Data
During training, models learn a vast amount of information about the real world. For example, if given the prompt "The capital of France is," the model will likely return "Paris," indicating it has learned about cities, capitals, and more. GPT models, trained on large datasets, become proficient in a variety of tasks, even those they were not specifically trained for.

### Applications of GPT Models
GPT models can:
* Write poems, as shown in an example prompt about Transformers
* Generate code, such as a function to calculate a Fibonacci number
* Convert text into audio or generate images described by a prompt

### Generative AI
The field of AI that allows generating new data is called **generative AI**. There has been a proliferation of new generative AI models, often based on the Transformer architecture. These models can generate:
* Images
* Text
* Audio
* Videos

### Large Language Models (LLMs)
In this course, we will learn about **Large Language Models (LLMs)**, which are trained on massive amounts of data. These models can:
* Generate text
* Answer questions
* Perform other tasks

### Available Models and Providers
* **OpenAI's GPT Models**
    * Can understand text, images, and voice
    * Available for use via ChatGPT or API
    * Versions like GPT-4 and refinements like GPT-4 Turbo
* **Google's Gemini Models**
    * Similar capabilities to GPT models
* **Stable Diffusion (Stability AI)**
    * Specializes in generating images from text prompts
* **Open-Source LLMs**
    * **Llama Models** (Meta)
    * **Mistral Models** (Mistral AI)

### Versioning in GPT Models
When we talk about a GPT model, we're not referring to a single model. OpenAI has trained various models with different versions. Even models with the same major version, like GPT-4, have been updated and refined over time. These refinements have names like GPT-4 Turbo. While some older versions, like GPT-2 and GPT-3, have been deprecated, other companies continue to develop and refine their models, such as Meta's Llama series.

-----

## Explore GPTs ✍️

### Explore Using Generative Pre-Trained Transformer Models
Udacity GPT is a chat interface powered by GPT models, integrated right here into the classroom. This tool allows you to ask questions about course content and receive responses. It leverages the capabilities of GPT models to provide explanations and answer your questions about the course.

In this exercise, you'll use Udacity GPT to explore the features and capabilities of GPT Models.

### How to Use "Udacity GPT"
1.  **Access the Interface:** Navigate to the Udacity GPT panel in the classroom. You will find a chat box where you can type your questions.
2.  **Ask Questions:** Enter your question or prompt into the chat box. Be as specific as possible to get the most accurate response.
3.  **Receive Responses:** The GPT model will process your query and provide a response. You can ask follow-up questions to dive deeper into the topic.
4.  **Iterate and Explore:** Use the chat to explore different aspects of the course content or get additional information on topics of interest.

### Example Prompts to Try
To help you get started, here are some example prompts related to GPT and Transformer models:
* **Understanding Basics:**
    * "What is a Transformer model in AI?"
    * "How do GPT models generate text?"
* **Exploring Applications:**
    * "What are some examples of generative AI applications?"
* **Technical Details:**
    * "Explain the architecture of a Transformer model."
* **Practical Usage:**
    * "How can I use GPT-3 for generating creative writing?"
    * "Can you provide an example of generating Python code using GPT?"
* **Comparing Models:**
    * "How does Stable Diffusion differ from other generative models?"

When you interact with the Udacity GPT, think about:
* **Generative Capabilities:** GPT models are designed to generate human-like text based on the input they receive. When you ask a question in "Udacity GPT," the model generates a response by predicting the next words in a sequence.
* **Understanding Prompts:** We talked about how the input given to a GPT model is known as a prompt. By experimenting with different prompts, you can experience how the specificity and clarity of a prompt can influence the quality and relevance of the response. This process, known as **prompt engineering**, is a crucial skill in effectively using GPT models.
* **Model Training and Knowledge:** GPT models are pre-trained on vast amounts of data, which enables them to provide knowledgeable responses across a wide range of topics. When you receive answers, you're experiencing firsthand how these models leverage their training data to provide informed responses.
* **Exploring Limitations:** While using Udacity GPT, you'll also encounter situations where the model's responses may not meet your expectations or may contain inaccuracies. This experience helps you appreciate the limitations of AI models, such as potential biases or knowledge gaps.

-----

## Natural Language Processing for Transformers 🗣️

### Introduction to NLP and Tokenization
Before we dive into how Transformer models work, we will cover the basics of **NLP**. NLP (Natural Language Processing) is a branch of AI that aims at understanding and communicating using human language. Transformers are part of the larger NLP field, and to understand how they work, we need some foundational knowledge in NLP.

### NLP for Transformers
In the next few videos, we will cover:
* **Tokenization:** The process of converting text into smaller parts that a machine learning model can process.
* **Embeddings:** A way to represent words in a text as multi-dimensional vectors.
* **Simpler Models:** An overview of some simpler models that preceded Transformers.

### Processing Text with AI Models
All machine learning models work with numbers, so we need to convert text into numbers first. This involves splitting the text into individual chunks, such as words, and converting each word into a number. This process is called **tokenization**, and the numbers are referred to as **token IDs**.
* **Token IDs Example:**
    * The word "welcome" might always be represented as number 11.
    * The word "course" might be represented as number 45.
These token IDs allow models to work with text data by processing these numeric representations instead of the words themselves.

### Creating a Vocabulary
To convert words into token IDs consistently, we need a **vocabulary**—a list of all distinct words from a large text collection. Each unique word gets a unique ID.
* **Vocabulary Creation Process:**
    1. **Text Collection:** Gather a large set of text (e.g., all Wikipedia articles).
    2. **Splitting:** Split the text into individual words.
    3. **Assigning IDs:** Each unique word receives a unique token ID.
This vocabulary is then used to convert new input text into a sequence of IDs.

### Handling Unknown Words
If our vocabulary doesn't cover all possible words (due to size limitations or unseen words during vocabulary creation), unknown words can be replaced with a special token representing an unknown word.

### Tokenization Methods
* **Word-Level Tokenization:**
    * Splitting text into words.
    * Each word receives a token ID.
    * **Pros:** More meaningful tokens.
    * **Cons:** Larger vocabulary, difficulty handling unknown words.
* **Character-Level Tokenization:**
    * Splitting text into individual characters.
    * Each character receives a token ID.
    * **Pros:** Can handle new words easily.
    * **Cons:** Less meaningful individual tokens.
* **Subword Tokenization:**
    * Combining full words and word chunks.
    * Helps with handling unknown words by breaking them into known subwords.
    * Example: The word "quantum" might be split into "quan" and "tum."
    * **Tools and Libraries:** The **TikToken** Library is a library used by GPT models to tokenize input sentences, especially useful for subword tokenization.

By understanding these fundamental concepts, you'll be better equipped to grasp how Transformer models, like GPT, process and generate human-like text.

-----

## Simple NLP Models
Once we have tokenized text, we can start building machine learning models using it. We'll start with simpler models to understand their limitations, which will help us better appreciate the advantages of more sophisticated models.

### The Bag of Words Model
* **How It Works:** The Bag of Words model uses a binary vector as an input. Each value in the vector is either one or zero, created from input token IDs.
* **Steps Involved:**
    1. **Tokenization:** Start with an input sentence, split it into individual tokens, convert to lowercase, and remove stop words (like "a," "the").
    2. **Creating Input Vectors:** The input vector will have as many elements as there are unique words in the vocabulary. For each token in the sentence, set the value at its corresponding ID position in the vector to one.
* **Limitations of the Bag of Words Model:**
    * Ignores Word Order
    * Ignores Grammatical Structure
    * Limited Semantic Meaning
    * Struggles with Unseen Words

### Word Embeddings
A more advanced method of representing tokens is using **embedding vectors**.
* **What Are Embedding Vectors?** Each word is represented as a smaller multi-dimensional vector, where the model learns these vectors during the training process.
* **Properties of Embedding Vectors:**
    * **Semantic Similarity:** Words with similar meanings are represented by similar vectors. "Laptop" and "computer" will be close to each other in the embedding space.
    * **Computing Similarity:** The **dot product** between two vectors can indicate their similarity.
    * **Semantic Relationships:** Embedding vectors can reveal analogies, like the famous `vector('King') - vector('Man') + vector('Woman') ≈ vector('Queen')`.

### RNNs and Their Limitations
**Recurrent Neural Networks (RNNs)** were designed specifically for processing sequential data like text.
* **How RNNs Work:** Data is processed one token at a time. The network maintains a **hidden state**, which retains information about previous tokens, allowing it to use context when processing subsequent tokens.
* **Challenges with RNNs:**
    * **Difficulty Accessing Previous States:** RNNs struggle to retain information from tokens seen long ago.
    * **Vanishing Gradient Problem:** In deep networks, gradients can become very small, slowing down training and making it difficult to capture dependencies over long sequences.

The next major advancement in NLP came with the Transformer architecture, which uses the attention mechanism to handle the challenges RNNs face.

-----

## How Transformer-Based Language Models Work ✨

The **Transformer architecture** is the core innovation behind the generative AI boom. It enables large language models (LLMs) to process, understand, and generate text.

### Overview of Transformer Model Functionality
1.  **Tokenization and Embeddings:** The input prompt is split into tokens, each converted into a token ID and then into an embedding vector.
2.  **Attention Mechanism:** Embedding vectors are refined in the attention block. The **attention mechanism** updates an embedding vector based on the context provided by other words in the input. The process of interaction between embedding vectors is called attention, which uses attention scores to show the relationships between input tokens.
3.  **Transformer Block:** Comprises an attention block followed by a feedforward network. Multiple Transformer blocks (layers) are chained together, with the output from one layer becoming the input for the next.
4.  **Output and Softmax:** The final layer provides a probability distribution for the next token to generate, using the **softmax function**.

### Benefits of Transformers
* **Parallel Processing:** Transformers can process the entire input prompt simultaneously, unlike RNNs.
* **Efficiency with Long Texts:** Better handling of longer texts.
* **Ease of Training:** More straightforward training compared to RNN models.
* **Performance:** Superior performance on real-world tasks.

### Concept of Context Window
The **context window** is the maximum number of tokens a model can handle at once, including both the input prompt and the output generated so far. The size of the context window varies by model:
* Smaller models may handle around 2,000 tokens.
* Larger models, like recent Gemini models, can handle over 1.5 million tokens.
A single word may be split into multiple tokens. For example, in GPT models, it typically takes four tokens to represent three words.
