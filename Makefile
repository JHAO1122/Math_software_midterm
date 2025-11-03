CC = gcc # 使用gcc编译器
CFLAGS = -Wall -Wextra -g # 编译警告和调试
LDLIBS = -lncurses # 链接所需要的ncurses库

DOXYFILE = Doxyfile # doxygen配置文件
DOXYGEN = doxygen # doxygen命令

OPEN = xdg-open # 打开文件命令

TARGET = conway # 生成的可执行文件名
SRCS = main.c conway.c # 源文件
OBJS = $(SRCS:.c=.o) # 将.c文件编译成.o文件

.PHONY: all doc clean clean-doc clean-all # 定义伪目标
all: $(TARGET) # 生成可执行文件

# 链接目标文件生成可执行文件
$(TARGET):$(OBJS) 
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

# 生成文档并展现
doc: $(DOXYFILE) 
	@$(DOXYGEN) $(DOXYFILE) 
	@$(OPEN) html/index.html

$(DOXYFILE):
	@doxygen -g $@

# 清理目标文件和中间文件
clean:
	rm -f $(OBJS) $(TARGET)
clean-doc:
	rm -rf html latex
clean-all: clean clean-doc