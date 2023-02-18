#
# 'make'        编译可执行文件 'main'
# 'make clean'  删除所有 .o 和可执行文件
#

# 定义使用的 C 编译器
CC = gcc

# 定义编译时的任何标志
CFLAGS	:= #-Wall -Wextra -g

# 除了 /usr/lib 之外，还定义库路径
# 如果我想包含不在 /usr/lib 中的库，我会使用 -Lpath 指定它们的路径，例如：
LFLAGS = -pthread

# 定义客户端和服务端的源目录
CLIENT_SRC	:= client/src
SERVER_SRC	:= server/src
# 定义客户端和服务端的包含目录
CLIENT_INC 	:= client/inc
SERVER_INC 	:= server/inc
# 定义客户端和服务端的 lib 目录
CLIENT_LIB	:= client/lib
SERVER_LIB	:= server/lib
# 定义客户端和服务端的 bin 目录
CLIENT_BIN  := bin
SERVER_BIN  := bin
# 定义客户端和服务端的 obj 目录
CLIENT_OBJ  := client/obj
SERVER_OBJ  := server/obj

# 定义可执行文件名
CLIENT_MAIN	:= client
SERVER_MAIN	:= server

FIXPATH = $1
RM = rm -f
MD	:= mkdir -p 

# 查找文件目录
CLIENT_SOURCEDIRS	:= $(shell find $(CLIENT_SRC) -type d)
SERVER_SOURCEDIRS	:= $(shell find $(SERVER_SRC) -type d)
CLIENT_INCLUDEDIRS	:= $(shell find $(CLIENT_INC) -type d)
SERVER_INCLUDEDIRS	:= $(shell find $(SERVER_INC) -type d)
CLIENT_LIBDIRS		:= $(shell find $(CLIENT_LIB) -type d)
SERVER_LIBDIRS		:= $(shell find $(SERVER_LIB) -type d)
CLIENT_BINDIRS		:= $(shell find $(CLIENT_BIN) -type d)
SERVER_BINDIRS		:= $(shell find $(SERVER_BIN) -type d)

# 创建必要的文件夹
create-dirs:
	if [ ! -d "$(CLIENT_SRC)" ]; then $(MD) $(CLIENT_SRC); fi
	if [ ! -d "$(CLIENT_INC)" ]; then $(MD) $(CLIENT_INC); fi
	if [ ! -d "$(CLIENT_BIN)" ]; then $(MD) $(CLIENT_BIN); fi
	if [ ! -d "$(CLIENT_OBJ)" ]; then $(MD) $(CLIENT_OBJ); fi
	if [ ! -d "$(CLIENT_LIB)" ]; then $(MD) $(CLIENT_LIB); fi
	if [ ! -d "$(SERVER_SRC)" ]; then $(MD) $(SERVER_SRC); fi
	if [ ! -d "$(SERVER_INC)" ]; then $(MD) $(SERVER_INC); fi
	if [ ! -d "$(SERVER_BIN)" ]; then $(MD) $(SERVER_BIN); fi
	if [ ! -d "$(SERVER_OBJ)" ]; then $(MD) $(SERVER_OBJ); fi
	if [ ! -d "$(SERVER_LIB)" ]; then $(MD) $(SERVER_LIB); fi

# 定义客户端和服务端的任何包含头文件的目录（除了 /usr/inc）
CLIENT_INCLUDES	:= $(patsubst %,-I%, $(CLIENT_INCLUDEDIRS:%/=%))
SERVER_INCLUDES	:= $(patsubst %,-I%, $(SERVER_INCLUDEDIRS:%/=%))
# 定义客户端和服务端的 C 库
CLIENT_LIBS	    := $(patsubst %,-L%, $(CLIENT_LIBDIRS:%/=%))
SERVER_LIBS	    := $(patsubst %,-L%, $(SERVER_LIBDIRS:%/=%))
# 定义客户端和服务端的 C 源文件
CLIENT_SOURCES	:= $(wildcard $(patsubst %,%/*.c, $(CLIENT_SOURCEDIRS)))
SERVER_SOURCES	:= $(wildcard $(patsubst %,%/*.c, $(SERVER_SOURCEDIRS)))
# 定义客户端和服务端的 C 对象文件
CLIENT_OBJECTS	:= $(CLIENT_SOURCES:.c=.o)
SERVER_OBJECTS	:= $(SERVER_SOURCES:.c=.o)
# 定义客户端和服务端的 bin 目录中的 C 对象文件
CLIENT_OBJECTS_INOBJ  := $(CLIENT_OBJECTS:$(CLIENT_SRC)/%.o=$(CLIENT_OBJ)/%.o)
SERVER_OBJECTS_INOBJ  := $(SERVER_OBJECTS:$(SERVER_SRC)/%.o=$(SERVER_OBJ)/%.o)

# 定义客户端和服务端的可执行文件名
CLIENT_MAIN	:= client
SERVER_MAIN	:= server
# 定义客户端和服务端的可执行文件的路径
CLIENT_BINMAIN	:= $(CLIENT_BIN)/$(CLIENT_MAIN)
SERVER_BINMAIN	:= $(SERVER_BIN)/$(SERVER_MAIN)

# 定义默认目标
.DEFAULT_GOAL := all

# 定义 all 目标
all: create-dirs client server
	@echo Executing 'all' complete!

# 定义 client 目标
client: $(CLIENT_OBJECTS_INOBJ)
	$(CC) $(CFLAGS) $(CLIENT_INCLUDES) -o $(CLIENT_BINMAIN) $(CLIENT_OBJECTS_INOBJ) $(LFLAGS) $(CLIENT_LIBS)

# 定义 server 目标
server: $(SERVER_OBJECTS_INOBJ)
	$(CC) $(CFLAGS) $(SERVER_INCLUDES) -o $(SERVER_BINMAIN) $(SERVER_OBJECTS_INOBJ) $(LFLAGS) $(SERVER_LIBS)

# 定义客户端和服务端的.o文件的目标
$(CLIENT_OBJ)/%.o: $(CLIENT_SRC)/%.c
	$(CC) $(CFLAGS) $(CLIENT_INCLUDES) -c $< -o $@
$(SERVER_OBJ)/%.o: $(SERVER_SRC)/%.c
	$(CC) $(CFLAGS) $(SERVER_INCLUDES) -c $< -o $@

# 定义 clean 目标
clean:
	$(RM) $(CLIENT_OBJECTS_INOBJ)
	$(RM) $(CLIENT_BINMAIN)
	$(RM) $(SERVER_OBJECTS_INOBJ)
	$(RM) $(SERVER_BINMAIN)
