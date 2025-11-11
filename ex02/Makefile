.PHONY: all clean fclean re f fclear c clear creat_dir

-include ./mk/source.mk

#############################################################################################
#																							#
#										// Variable											#
#																							#
#############################################################################################


# NAME				=		cpp
NAME				=		PmergeMe
CC					=		c++
INCLUDES			=		-I$(HEADERS_DIR)
CPPFLAGS			=		-Wall -Werror -Wextra -std=c++98 $(INCLUDES) -g3
CPPFLAGSS			=		-Weverything						 -Wno-padded -Wno-documentation-unknown-command -Wno-documentation -std=c++98 $(INCLUDES)
NPD					=		--no-print-directory
MAKE				:=		$(MAKE) -j $(NPD)
RM					=		rm -fr


#############################################################################################
#																							#
#										// OBJECT											#
#																							#
#############################################################################################


OBJS_DIR			:=		./.objs/
OBJS_FILES			:=		$(SRCS:.cpp=.o)
OBJS				:=		$(addprefix $(OBJS_DIR), $(OBJS_FILES))


DEPS_DIR			:=		./.deps/
DEPS_FILES			:=		$(OBJS_FILES:.o=.d)
DEPS				:=		$(addprefix $(DEPS_DIR), $(DEPS_FILES))


#############################################################################################
#																							#
#									// Rules Compilation									#
#																							#
#############################################################################################


all					:		$(NAME)


$(NAME)				:		$(OBJS)
		$(CC) $^ $(CPPFLAGS) -o $(NAME)



creat_dir 		:
		mkdir -p $(DEPS_DIR)
		mkdir -p $(OBJS_DIR)


$(OBJS_DIR)%.o : $(SRC_DIR)%.cpp Makefile | creat_dir
	$(CC) $(CPPFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@mv $(basename $@).d $(DEPS_DIR)

#############################################################################################
#																							#
#									// clean fclean re										#
#																							#
#############################################################################################


clean 				:
			$(RM) $(OBJS_DIR)
			$(RM) $(DEPS_DIR)


fclean 				:
			$(RM) $(NAME)
			$(RM) $(OBJS_DIR)
			$(RM) $(DEPS_DIR)


re 					:	 fclean all


#############################################################################################
#																							#
#										// Allias											#
#																							#
#############################################################################################


c					:	clear
clear				:	clean

f					:	fclean
fclear				:	fclean

-include $(DEPS)
