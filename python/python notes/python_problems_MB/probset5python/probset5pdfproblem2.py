'''Salary expenditure as percentage of total expenditure for states & UTs from 2007-08 to 2013-14'''
import pandas as pd
data = pd.read_excel("C:\\Users\\91836\\OneDrive\\Desktop\\Notes\\Prog (MB)\\datafile.xlsx",engine='openpyxl')
col = data.columns
# Remove rows by index (replace 'index_to_remove' with the actual index you want to remove).
dfd =data.drop([11,29,32,33])
d1=dfd.loc[:,col[1]]
print(data)
# d2=data.loc[:,"Complexity"].unique()
# d3=data.loc[:,"Domain"].unique()
# mean1,median1,mode1,stdv,skew1,kurt,pro,comp,dom= [],[],[],[],[],[],[],[],[]
# for i in d1:
#     for j in d2:
#         for k in d3:
#             ED1 = data.loc[(data["Process"]==i) & (data["Complexity"]==j) & (data["Domain"]==k)]
#             mean1.append(ED1.loc[:,"ManHour"].mean())
#             median1.append(ED1.loc[:,"ManHour"].median())
#             mode1.append(ED1.loc[:,"ManHour"].mode())
#             stdv.append(ED1.loc[:,"ManHour"].std())
#             skew1.append(ED1.loc[:,"ManHour"].skew())
#             kurt.append(ED1.loc[:,"ManHour"].kurtosis())
#             pro.append(i)
#             comp.append(j)
#             dom.append(k)

# table = pd.DataFrame({'Process':pro,'Complexity':comp,'Domain':dom,'mean':mean1,'median':median1,'mode':mode1,'standard deviation':stdv,'skewness':skew1,'kurtosis':kurt})
# table.to_excel('manhourdata.xlsx', index=False)