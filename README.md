## DICOM

### 概要
DICOM 是Digital Imaging and Communications in Medicine的英文缩写，即医学数字成像和通信标准。是ACR和NEMA为主制定的用于数字化医学影像传送、显示与存储的标准。
在DICOM标准协议中详细定义了影像及其相关信息的组成格式和交换方法，利用这个标准，人们可以在影像设备上建立一个接口来完成影像数据的输入/输出工作。

DICOM标准以计算机网络的工业化标准为基础，它能帮助更有效地在医学影像设备之间传输交换数字影像，这些设备不仅包括CT、MR、核医学和超声检查，而且还包括CR、胶片数字化系统、视频采集系统和HIS／RIS信息管理系统等。

### DICOM技术概要及特点

◆ 在应用层上通过服务和信息对象主要完成五个方面的功能：
◆ 传输和存储完整的对象（如图像、波形和文档）。
◆ 请求和返回所需对象。
◆ 完成特殊的工作（如在胶片上打印图像）。
◆ 工作流的管理（支持WORKLIST和状态信息）。
◆ 保证可视图像（如显示和打印之间）的质量和一致性。
◆ 参照软件工程面向对象的的方法。如采用实体－关联（E-R）模型、详细定义对象及其属性、服务对象对类（SOP）、消息交换以及工作流程等。
◆ 通过消息、服务、信息对象及一个良好的协商机制，独立于应用的网络技术（不受具体网络平台限制），可以点对点、点对多点、多点对点多种方式确保兼容的工作实体之间服务和信息对象能有效地通信。不仅能实现硬件资源的共享。而且不同于一般分布式对象或数据库管理只在低层自动存取单独的属性，而在病人、检查、结构化报告（SR）、工作流等高层管理上规范服务。是一个基于内容的医学图像通信标准。
◆ DICOM不规范应用系统的结构，也不规范具体的功能需求。例如，图像存储只定义传输和保存所必须的信息项目，而不说明图像如何被显示和作注解。
◆ DICOM目前16章内容每章讲述某一方面的规范，各章较为独立但又互有联系。这样便于修改扩充。只有将所有章节紧密联系起来才能勾画出标准的体系结构和整体内容。


DICOM服务类

证实（verification）服务类
存储（storage）服务类
查询／检索（query/retrieve）服务类
检查内容通知（study content notification）服务类
患者管理（patient management）服务类
检查管理（study management）服务类
结果管理（results management）服务类
打印管理（print management）服务类
媒质存储(media storage) 服务类
存储责权管理(storage commitment) 服务类
基本工作列表管理(basic worklist management) 服务类
队列管理(queue management) 服务类
灰度软拷贝表达状态存储（Grayscale Softcopy Presentation State Storage）服务类
结构化报告存储（Structured Reporting Storage）服务类

缩略语解释

HIS=医院信息系统
PACS=医学影像归档与传输系统
LIS=检验信息系统
RIS=放射信息系统
CIS=临床信息系统
HIS最大，是全医院的

PACS和RIS基本上是放射科（或者更准确地说是影像科室的）
LIS自然是检验科室的
CIS是以病人为中心的临床系统，包括以上全部和电子病历在内。

 

DICOM   的   4   个内容层次：  
  1.   Patient   (病人)  
  2.   Study   (检验)  
  3.   Series   (系列)  
  4.   Image   (图像) 

标准中涉及的基本概念和定义

DICOM标准涉及到医学图像、数据通信、管理信息系统等领域，在标准中又采用了面向对象的描述方法和E-R (Entity-Relation)模型，从而引入了大量的各专业方面的术语，给标准的阅读和理解带来困难。下面简要地将标准中涉及的常用的技术词汇和缩略语给予解释。
1. 实体(Entity): 表示一个或一类有相同特性个体的应用对象。在计算机系统分析中，凡是可以区别并被人们识别的事、物、概念等，都可以被抽象为实体。实体一般具有若干特征，称为属性。如: 患者是一个实体，具有姓名、性别、年龄等属性。图像也是一个实体，它有图像尺寸、图像数据等属性。
2. 联系(Relation): 表示实体之间的相互关系。如患者实体与分析实体之间存在着引用联系，打印机实体和胶片实体之间存在着打印的联系。
3. E-R模型: 描述现实世界的一种信息模型。通过定义实体以及实体间的联系，表现系统的需求和功能。通常以E-R图的方式表示。在DICOM中，用方框表示实体，菱形表示联系，用带箭头或不带箭头的线段将实体(方框)与联系(菱形)连接表示它们之间存在联系。这是面向对象的分析方法所采用的主要表示方法，是对客观世界的一种抽象。
4. 对象(Object): 外部世界事物在计算机内部的表示，是事物属性值和处理方法的集合。对象具有封装和继承的特征。封装是指对象将属性和方法集合在一起，一般情况下只提供给自己和派生对象使用。继承是指当一个对象是由另一个对象(父对象)派生出时，它就自动具有父对象所具有的属性和方法。面向对象的方法就是以对象技术为中心，分析系统中各种信息之间的关系，抽象出系统各层次的对象模型，给出准确的系统描述，并在计算机系统中给予实现。应用面向对象的方法，可以提高开发效率，实现软件复用。
5. 信息对象定义(Information Ob-ject Definition，IOD): 信息实体的抽象，是DICOM命令的作用受体。
6. 服务(Service): 某对象为其它对象或程序提供的功能。当要求使用此功能时称申请服务，申请服务的对象称服务用户，而能完成该功能的对象是服务的提供者。
7. 服务对象对(Service Object Pair，SOP): DICOM信息传递的基本功能单位。包括一个信息对象和一组DICOM消息服务元素。
8. 协议: 计算机网络中为保证能正确地传输数据而必须共同遵守的通信规则和格式。
9. ISO-OSI: 国际标准化组织(ISO)所定义的开放系统互联(OSI)的七层网络参考模型。作为一个严格的网络模型，对于计算机网络的研究和发展起了重要的作用，但是由于种种原因在实际中并未得到广泛的普及使用。DICOM标准在制定时，OSI正是发展的高潮，因此也作为DICOM中主要的网络参考模型。
10. TCP/IP: 是传输控制协议/互联网协议，它首先在UNIX系统中使用，随后成为计算机网络中不同种类计算机之间通信的主要通信协议，是互联网的基础。

 

应用

毫无疑问，DICOM是医学图像信息系统领域中的核心，它主要涉及到信息系统中最主要也是最困难的医学图像的存储和通信，可直接应用在放射学信息系统(RIS)和图像存档与通信系统(PACS)中。DICOM也是研究和开发具有网络连接功能，实现信息资源共享的新型医疗仪器的技术基础。医疗仪器在朝着自动化、智能化发展的同时，也在向着具有通信能力的遥控遥测和信息远程获取的网络功能发展，医疗仪器既是医疗信息系统中的信息源，又是系统中的信息使用者，是信息系统中的一个主要环节，网络化的医疗仪器对医学信息系统的重要性是不言而喻的。
DICOM标准的另一个特点是它定义在网络通信协议的最上层，不涉及到具体的硬件实现而直接应用网络协议，因此与网络技术的发展保持相对独立，可以随着网络性能的提高而使DICOM系统的性能立即得到改善。DICOM尽管提供了OSI的网络模型，但现在实际上网络绝大部分都是在TCP/IP协议下构成的，网络硬件采用的形式可以多种多样，如100M的双绞线100Base-T，光纤FDDI，综合业务数字网ISDN，T1线路等，还有速度较低的10兆网10Base-T和电话线路。只要设备具有支持TCP/IP协议的网络接口，在软件的支持下，就可以做到像PC机一样实现“即插即用”，非常方便地加入到医学信息系统的网络中。在这样的意义下，用DICOM实现的医疗信息系统，无论是RIS还是PACS，都具有类似的结构，如图2所示:
在采用DICOM标准的信息网络系统中，所有DICOM设备之间都可以按照DICOM的网络上层协议进行互相连接和操作。临床医生可以在办公室查看B超设备的图像和结果，可以在CT机上调用核磁共振图像进行图像的叠加融合，也可以通过网络调用存储在其他医院的图像结果。无论是本院、本地还是相距很远的外地，DICOM设备都可以通过网络相互联系，交换信息。
由于提供了统一的存储格式和通信方式，普及DICOM标准，可以简化医疗信息系统设计，避免许多重复性的工作，加快信息系统的开发速度。对于实现无纸化、无胶片化的医院和远程医疗系统的实施将会起极其重要的作用。




[概念扫盲](https://zhuanlan.zhihu.com/p/74966427)