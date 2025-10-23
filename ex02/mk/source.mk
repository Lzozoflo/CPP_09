
#############################################################################################
#																							#
#										// Directories										#
#																							#
#############################################################################################

# Directories
SRC_DIR				:=		./src/
HEADERS_DIR			:=		./inc/

# Sub Directories

# for a new DIR add a new :
# NEW_DIR			:=		new/


#############################################################################################
#																							#
#										// SOURCE											#
#																							#
#############################################################################################


HEADERS_D			:=		./incs/


HEADERS				:=		PmergeMe.hpp



SRC					:=		PmergeMe.cpp		\
							main.cpp


# for a new SRC add a new :
# SRC_NEW				:=



# Every now src_dir add a addprifix like that :
#	$(addprefix $(NEW_DIR), $(SRC_NEW))


SRCS				=		$(SRC)
