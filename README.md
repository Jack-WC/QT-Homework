# 
QT大作业更新日志：  

5.30修改内容：
1.新增player角色类，删除原有protagonist、2个timer，将jump，move等函数移动到类中  
2.新增地图文件，程序启动时从map1.dat文件中加载（请关闭shadow build否则会加载失败！！）  
3.优化了部分代码  
提示：QLabel直接用QPixmap加载图片即可  

6.5 更新内容（By Jack_WC）：   
1.优化了player类的结构，使用了枚举类型，重写了player的moveEvent函数，将更改主角朝向与移动分开  
2.优化了主角移动的手感，添加了左右移动时平滑的动画，并将INTERVAL修改为10，看起来更流畅  
3.解决了多个方向键同时按下人物移动的异常情况（同时按下左右键则人物向右移动）（其实尚未完全解决）  

现存问题：多按键同时按下之后，有时人物无法跳跃  
