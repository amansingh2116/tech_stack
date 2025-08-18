''' Write a program in Python to calculate values of all sorts of
measures of central tendency, dispersion and shape of the
man-hours required for all combinations of Process,
Complexity and Domain of jobs (3 × 3 × 2 = 18 types) given
in the ManHour data.'''

import pandas as pd
data = pd.read_excel("C:\\Users\\91836\\OneDrive\\Desktop\\Notes\Prog (MB)\\ManHourData.xlsx",engine='openpyxl')
d1=data.loc[:,"Process"].unique()
d2=data.loc[:,"Complexity"].unique()
d3=data.loc[:,"Domain"].unique()
mean1,median1,mode1,stdv,skew1,kurt,pro,comp,dom= [],[],[],[],[],[],[],[],[]
for i in d1:
    for j in d2:
        for k in d3:
            ED1 = data.loc[(data["Process"]==i) & (data["Complexity"]==j) & (data["Domain"]==k)]
            mean1.append(ED1.loc[:,"ManHour"].mean())
            median1.append(ED1.loc[:,"ManHour"].median())
            mode1.append(ED1.loc[:,"ManHour"].mode())
            stdv.append(ED1.loc[:,"ManHour"].std())
            skew1.append(ED1.loc[:,"ManHour"].skew())
            kurt.append(ED1.loc[:,"ManHour"].kurtosis())
            pro.append(i)
            comp.append(j)
            dom.append(k)

table = pd.DataFrame({'Process':pro,'Complexity':comp,'Domain':dom,'mean':mean1,'median':median1,'mode':mode1,'standard deviation':stdv,'skewness':skew1,'kurtosis':kurt})
#table.to_excel('manhourdata.xlsx', index=False)
print(table)