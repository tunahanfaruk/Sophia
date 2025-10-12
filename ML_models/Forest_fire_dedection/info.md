# Forest Fire Dedection Model  

### use of this model :  
dedecting that is there fire or not at forest  
  
### Dataset :   
[DATASET_LINK](https://www.kaggle.com/datasets/elmadafri/the-wildfire-dataset)  

### Model structure  
Whit pytorch  

----------------------------------------------------------------  
        Layer (type)               Output Shape         Param #  
================================================================  
 AdaptiveAvgPool2d-1          [-1, 3, 224, 224]               0  
            Conv2d-2         [-1, 64, 224, 224]           1,792  
       BatchNorm2d-3         [-1, 64, 224, 224]             128  
              ReLU-4         [-1, 64, 224, 224]               0  
         MaxPool2d-5         [-1, 64, 112, 112]               0  
            Conv2d-6        [-1, 128, 112, 112]          73,856  
       BatchNorm2d-7        [-1, 128, 112, 112]             256  
              ReLU-8        [-1, 128, 112, 112]               0  
         MaxPool2d-9          [-1, 128, 56, 56]               0  
           Conv2d-10          [-1, 256, 56, 56]         295,168  
      BatchNorm2d-11          [-1, 256, 56, 56]             512  
             ReLU-12          [-1, 256, 56, 56]               0  
        MaxPool2d-13          [-1, 256, 28, 28]               0  
           Conv2d-14          [-1, 512, 28, 28]       1,180,160  
      BatchNorm2d-15          [-1, 512, 28, 28]           1,024  
             ReLU-16          [-1, 512, 28, 28]               0  
        MaxPool2d-17          [-1, 512, 14, 14]               0  
           Conv2d-18          [-1, 512, 14, 14]       2,359,808  
      BatchNorm2d-19          [-1, 512, 14, 14]           1,024  
             ReLU-20          [-1, 512, 14, 14]               0  
        MaxPool2d-21            [-1, 512, 7, 7]               0  
          Flatten-22                [-1, 25088]               0  
           Linear-23                 [-1, 4096]     102,764,544  
             ReLU-24                 [-1, 4096]               0  
          Dropout-25                 [-1, 4096]               0  
           Linear-26                    [-1, 1]           4,097  
================================================================  
Total params: 106,682,369  
Trainable params: 106,682,369  
Non-trainable params: 0  
----------------------------------------------------------------  
Input size (MB): 0.57  
Forward/backward pass size (MB): 153.22  
Params size (MB): 406.96  
Estimated Total Size (MB): 560.75  
----------------------------------------------------------------  

### Train  
On Google Collab for 50 ephoch whit T4 GPU  
time for train 9 hour  

### Result  
Acuracy = %83 < x < %87   


