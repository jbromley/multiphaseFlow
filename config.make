# add custom variables to this file

# OF_ROOT allows to move projects outside apps/* just set this variable to the
# absoulte path to the OF root folder

OF_ROOT = /home/jbromley/Applications/of_preRelease_v007_linux64


# USER_CFLAGS allows to pass custom flags to the compiler
# for example search paths like:
# USER_CFLAGS = -I src/objects

# USER_LDFLAGS = 
USER_CFLAGS = -pg


# USER_LDFLAGS allows to pass custom flags to the linker
# for example libraries like:
# USER_LD_FLAGS = libs/libawesomelib.a

# USER_LDFLAGS = 
USER_LDFLAGS = -pg


# use this to add system libraries for example:
# USER_LIBS = -lpango
 
USER_LIBS =


# change this to add different compiler optimizations to your project

# USER_COMPILER_OPTIMIZATION = -march=native -mtune=native -Os
USER_COMPILER_OPTIMIZATION = -march=native -mtune=native -g


EXCLUDE_FROM_SOURCE="bin,.xcodeproj,obj,.git"
