破冰饭分值计算程序

分两步进行：

1. check_input_answer

用法：check_input_answer ./answer1

输入：参数answer1，即答案数据

输出：程序有返回值 
      -1：表示参数错误
       0：答案数据格式正确
   大于0：表示答案数据格式不正确

说明：该程序需要一个参数，该参数是要被计算的答案数据

2. cal_score

用法：cal_score data_number_distance answer1 output

输入：1. data_number_distance 员工之间的距离
      2. answer1              要计算的答案数据
      3. output               输出文件名

输出：分值

说明：只有通过check_input_answer，格式正确的数据才被计算


数据文件说明：

1. data_number_distance, 这个文件是用于计算分值，不能随意更改，后果严重

2. answer*,是用来做测试用的答案数据 

特别注意：

输入数据格式，每行数据最后必须有换行符，不能出现任何空格