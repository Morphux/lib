################################### LICENSE ####################################
#                            Copyright 2016 Morphux                            #
#                                                                              #
#        Licensed under the Apache License, Version 2.0 (the "License");       #
#        you may not use this file except in compliance with the License.      #
#                  You may obtain a copy of the License at                     #
#                                                                              #
#                 http://www.apache.org/licenses/LICENSE-2.0                   #
#                                                                              #
#      Unless required by applicable law or agreed to in writing, software     #
#       distributed under the License is distributed on an "AS IS" BASIS,      #
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  #
#        See the License for the specific language governing permissions and   #
#                       limitations under the License.                         #
################################################################################

NAME =		libmorphux.a
CC =		gcc
AR =		ar
CFLAGS =	-Wall -Wextra -Werror -Wno-unused-result -I inc/ -std=c99 -g -O3
ARFLAGS =	-cq
SRCS =		$(wildcard src/*.c)
OBJS =		$(SRCS:%.c=%.o)

OSTYPE =	$(shell uname)
ifeq ($(OSTYPE), Linux)
COVFLAGS =	"-Wall -Wextra -Wno-unused-result -I inc/ -std=c99 -g -O0 -coverage -lgcov"
elif ($(OSTYPE), Darwin)
COVFLAGS =	"-Wall -Wextra -Wno-unused-result -I inc/ -std=c99 -g -O0 -coverage"
endif

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

check: all
	make -C tests check

doc:
	doxygen docs/doxyfile

coverage:
	$(MAKE) fclean all $(COVFLAGS)
	$(MAKE) fclean all $(COVFLAGS)
	endif
	make -C tests coverage check
	gcov -o src/ $(SRCS)

clean:
	rm -f $(OBJS)
	rm -f *.gcov
	rm -f src/*.gcno
	rm -f src/*.gcda

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all
