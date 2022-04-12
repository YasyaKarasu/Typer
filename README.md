# Typer

这是程序设计基础课程的一项小作业，作业要求如下：

做一个简单的“打一字”练习工具，充分结合图形专题和文件专题的内容。 

- 屏幕上方出现菜单含“设置”，“关于”两个类别。“设置”含有“开始”、“暂停”、“加速”、 “减速”、“退出”选项。 “关于”含有“帮助”和“排行榜”选项。可考虑加快捷键。 
- 屏幕下方出现“开始”、“暂停”、“加速”、“减速”、“退出”按钮。
- 中间区域分三个区域，分别是计分区，字母出现区和输入区。开始练习时，字母出现区 顶部随机出现一个字母，让其下落。若在未落到底部前，用户输入的字母若有和下落字母相 同，则计分，字母不再下落，字母出现区和输入区刷新，顶部出现新字母，开始新字母的练 习。若字母到底部没有击中过，则字母出现区和输入区刷新，顶部出现新字母，开始新字母 的练习。在新字母练习未开始前，输入区显示所有输入的字母。
- 游戏开始，每过 10 秒，字母区边框换一种颜色。
- 每次退出练习时，将本次练习的分数、练习时长、练习日期写入排行榜文件。并显示“排 行榜”，本次加亮。
- 选择 “排行榜” 菜单项时，显示所有练习的记录，要求按分数由高到低排序，同分时 还需考虑时长

此项目利用libgraphics和simpleGUI库实现了以上要求。

TODO : 编写Makefile