# easy_game_server2
lib 
	autotest_lib
		包含的文件是用来做python版本的协议code，decode的基类，开发的目的也是为了做协议自动化测试。
	convert_excel_2_cvs
		包含的文件是用来把excel表格翻译成csv文件，以及把csv文件加载到内存的c++代码，根据excel文件的格式，自动生成表格的c++结构
	db_handle
		包含的文件是用来把sql建表语句，翻译成相关的c++结构，各种sql语句的自动填写，可以较大的简化mysql编写代码的劳动
	protocol_handle
		包含的文件是用来把h头文件定义的协议，翻译成相应的code，decode的代码，目前有c++，lua，python，java版本，可以做到一份定义，前后台通用，简化劳动

project 
	test
		configure
			演示如何操作convert_excel_2_cvs
		db
			演示如何操作db_handle
		protocol
			演示如何操作protocol_handle
		server_d
			演示在实际的项目里，如何综合应用上述工具生成的c++代码，可以看到协议的收发，数据库的操作，使用的都是自动生成的代码，减少了人犯错误的可能，因为这些代码毕竟都是非常枯燥的，该项目使用libevent简化网络层，并且参考协程的概念，将异步逻辑写在一个函数调用里，免去了异步代码调试的痛苦，所以可以说，在工具的帮助下，开发c++游戏后台劳动强度降低到了脚本语言的程度，可喜可贺。
