# 
从零开始的QT大作业更新日志：

5.30 update log（By Jack_WC）： 
1.新增player角色类，删除原有protagonist、2个timer，将jump，move等函数移动到类中
2.新增地图文件，程序启动时从map1.dat文件中加载（请关闭shadow build否则会加载失败！！）
3.优化了部分代码
提示：QLabel直接用QPixmap加载图片即可

6.5 update log（By Jack_WC）：
1.优化了player类的结构，使用了枚举类型，重写了player的moveEvent函数，将更改主角朝向与移动分开
2.优化了主角移动的手感，添加了左右移动时平滑的动画，并将INTERVAL修改为10，看起来更流畅
3.解决了多个方向键同时按下人物移动的异常情况（同时按下左右键则人物向右移动）(已经解决)

6.17 update log：
1.增加左右移动的动作差分，为此，改变角色图片命名方式为" type(0/1)+towards(left/right)+step(0-5).png"，同时修改原player的getPixmap()函数
2.尝试增加片头动画（可点击右下角跳过）与开始界面（仅示意，后续再讨论修改），但qt播放视频需要另外的解码器，故另附K-Lite安装包
3.尝试给人物增加血条，撞到怪物减血，血为零或者掉出界面自动退出
4.修复了按左右键无法跳跃的bug
5.修复了动画间隔过长导致显示错误的bug
6.修复了开局随机游走的bug

6.25 update log:
1.将mainwindow的两个timer与全部player移动的有关函数都整合到player类里
2.新增mainframe主界面，mainwindow变为原来关卡的窗口
3.将键盘事件转移到MainFrame主界面

6.27 update log:
1.新增HpBar血条类
2.完成一个特殊关卡

6.29 update log:
1.完成其余两个特殊关卡制作
2.添加选择关卡界面

